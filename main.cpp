#include "ReadData.h"
#include "Stock.h"
#include "Transaction.h"
#include "Utility.h"
#include "Calculation.h"
#include "gnuplot_CAAR.h"

#include <map>
#include <vector>
#include <string>

#include <vector>
#include <time.h>
#include <cmath>
#include <iomanip>
#include <thread>

#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 3

/*
In ReadData.cpp, we have defined global variables:

const char* cIWV3000SymbolFile = "Russell_3000_component_stocks.csv";
const string config_file = "conFig_file.csv";
const string annoucement_file = "Russell3000EarningsAnnouncements.csv";
*/

using namespace std;
using namespace fre;

int main() {
    int N = 0;
    string selected_symbol;
    bool quit = false;
    int choice = 0;
    string selected_group;
    
    //Create getting-date object.
	ReadData readData;
	
	// Get data and create their objects.
    map<string, vector<string>> data_csv;
    map<string, string> data_curl;
	Stock IWV;
	map<string, Stock> stocks;

	// Create objects.
	map<string, Stock> valid_stocks;
	map<string, double> surprisePct_map;

	
	//Three groups
    map<string, Stock> beat;
    map<string, Stock> miss;
    map<string, Stock> meet;
     
    //int size_oStk;
    vector<string> orderedStocks;
    vector<Matrix> calc;
    
    
    do {
        cout<<"1 - Enter N to retrieve 2N+1 days of historical price data for all stocks"<<endl;
        cout<<"2 - Pull information for one stock from one group."<<endl;
        cout<<"3 - Show AAR, AAR-STD, CAAR, and CAAR-STD for one group"<<endl;
        cout<<"4 - Plot Avg CAAR for 3 groups"<<endl;
        cout<<"5 - Plot STD CAAR for 3 groups"<<endl;
        cout<<"6 - Plot Avg AAR for 3 groups"<<endl;
        cout<<"7 - Plot STD AAR for 3 groups"<<endl;
        cout<<"8 - Exit."<<endl;
    
        cout << "Enter your choice and press return: ";
        cin>>choice;
        
        switch (choice)
        {
            case 1:{
                cout << "Enter N (N must be between 60 and 90): ";
                cin >> N;
                if (N == 0) {
                    return 0;
                } else if (N < 60 || N>90) {
                    cout << "Invalid value N: 60 <= N <= 90 " << endl;;
                } 
                calc.resize(3);//trying to resize the dimension of calc
 
                for (int i=0;i<3;i++)
                {
                    calc[i].resize(4);
                     
                    for (int j=0;j<4;j++)
                    {
                        calc[i][j].resize(2*N);
                    }
                }
                
                //Load data.
            	readData.loadTickerList();// 2583 rows
            	readData.loadDataCsv(); // 2183 rows
                
                // Muti-Tread Part, Load Curl data
                vector<string> tickerList = readData.getTicker_list();
                int size = tickerList.size();
                int length = size/NUM_THREADS;
            	vector<string> ticker_list01, ticker_list02, ticker_list03;
            	ticker_list01 = slice(tickerList, 0, length);
            	ticker_list02 = slice(tickerList, length + 1, 2 * length);
            	ticker_list03 = slice(tickerList, 2*length + 1, size - 1);
                
                thread task01(&ReadData::loadDataCurl, &readData, ticker_list01);
                thread task02(&ReadData::loadDataCurl, &readData, ticker_list02);
                thread task03(&ReadData::loadDataCurl, &readData, ticker_list03);
                
                task01.join();
                task02.join();
                task03.join();
                
                // Muti-Tread Part Done
            
            	readData.storeStocks();
            	
            	data_csv = readData.getData_csv();
                data_curl = readData.getData_curl();
            	IWV = readData.getIWV();
            	stocks = readData.getStocks();
                
                //  Compute daily return
                for (map<string, Stock>::iterator itr = stocks.begin(); itr != stocks.end(); itr++) {
                    if (itr->second.computeUsedData(N,itr->second.getAnnouncementDate())) {
                        itr->second.computeAR(N, IWV);
                        valid_stocks[itr->second.getTicker()] = itr->second;
                    }
                }
                
                //Combine csv info and curl info.
                for (map<string, Stock>::iterator itr = valid_stocks.begin(); itr != valid_stocks.end(); itr++) {
                    string ticker = itr->first;
                    string surprisePct = data_csv[ticker][5];
                    if (!surprisePct.empty() && surprisePct[surprisePct.length() - 1] == '\r') {
                        surprisePct.erase(surprisePct.size() - 1);
                    }
                    surprisePct_map[ticker] = stod(surprisePct);
    
                    itr->second.setEstimatedEarnings(stod(data_csv[ticker][2]));
                    itr->second.setReportedEarnings(stod(data_csv[ticker][3]));
                    itr->second.setSuprise(stof(data_csv[ticker][4]));
                    itr->second.setSuprisePct(stof(data_csv[ticker][5]));
                }
    
                // Sort by surprice and group
                orderedStocks = sort(surprisePct_map);
                
                // Generate 3 groups data
                miss.clear();
                meet.clear();
                beat.clear();
                for (int i = 0; i < (int)orderedStocks.size(); i++) {
                if (i < (int)orderedStocks.size()/3) {
                        valid_stocks[orderedStocks[i]].setGroup("miss");
                        miss[orderedStocks[i]] = valid_stocks[orderedStocks[i]];
                    } else if (i >= (int)orderedStocks.size()/3 && i < 2*(int)orderedStocks.size()/3) {
                        valid_stocks[orderedStocks[i]].setGroup("meet");
                        meet[orderedStocks[i]] = valid_stocks[orderedStocks[i]];
                    } else {
                        valid_stocks[orderedStocks[i]].setGroup("beat");
                        beat[orderedStocks[i]] = valid_stocks[orderedStocks[i]];
                    }
                }
        
               
                Result(beat, miss, meet, N, calc);
        
            // for (int i = 0; i < 3; i++){
            //     if (i == 0) {
            //         cout << "beat" << endl;
            //     }
            //     if (i == 1) {
            //         cout << "miss" << endl;
            //     }
            //     if (i == 2) {
            //         cout << "meet" << endl;
            //     }
            //     cout << "ARRAvg " << calc[i][0] << endl;
            //     cout << "ARRstd " << calc[i][1] << endl;
            //     cout << "CAARAvg " << calc[i][2] << endl;
            //     cout << "CAARstd " << calc[i][3] << endl;
            //     cout << endl;
            // }
                break;
            }
                
    
	//Add other left variables into valid_stocks
                
    
            case 2:
                cout << "Enter Symbol for Detailed Information: ";
                cin >> selected_symbol;
                cout << "Ticker: " << selected_symbol << endl;
                valid_stocks[selected_symbol].printInfo();
                cout << "Stock Daily Price Dates:" << endl;
                valid_stocks[selected_symbol].printValidTransactionDate();
                cout<<endl;
                cout << "Stock Daily Price: " << endl;
                valid_stocks[selected_symbol].printValidTransactionDailyPrice();
                cout<<endl;
                cout << "Stock Daily Returns:" << endl;
                valid_stocks[selected_symbol].printValidTransactionDailyReturn();
                cout<<endl;
                cout << "Stock Cumulative Daily Returns:" << endl;
                valid_stocks[selected_symbol].printValidTransactionCumulativeDailyReturn();
                cout<<endl;
                cout << "Stock Abnormal Daily Returns:" << endl;
                valid_stocks[selected_symbol].printValidTransactionAR();
                cout<<endl;
                break;
            case 3:
                cout << "Enter Group (Beat, Meet, Miss) for Detailed Information: ";
                cin >> selected_group;
                if (selected_group == "Beat") {
                    cout << "Avg AARs for Group " << selected_group << endl;
                    cout << calc[0][0] << endl;
                    cout << endl;
                    cout << "Std AARs for Group " << selected_group << endl;
                    cout << calc[0][1] << endl;
                    cout << endl;
                    cout << "Avg CAARs for Group " << selected_group << endl;
                    cout << calc[0][2] << endl;
                    cout << endl;
                    cout << "Std CAARs for Group " << selected_group << endl;
                    cout << calc[0][3] << endl;
                    cout << endl;
                 }
                else if (selected_group == "Meet") {
                    cout << "Avg AARs for Group " << selected_group << endl;
                    cout << calc[2][0] << endl;
                    cout << endl;
                    cout << "Std AARs for Group " << selected_group << endl;
                    cout << calc[2][1] << endl;
                    cout << endl;
                    cout << "Avg CAARs for Group " << selected_group << endl;
                    cout << calc[2][2] << endl;
                    cout << endl;
                    cout << "Std CAARs for Group " << selected_group << endl;
                    cout << calc[2][3] << endl;
                    cout << endl;
                 }
                 else if (selected_group == "Miss") {
                    cout << "Avg AARs for Group " << selected_group << endl;
                    cout << calc[1][0] << endl;
                    cout << endl;
                    cout << "Std AARs for Group " << selected_group << endl;
                    cout << calc[1][1] << endl;
                    cout << endl;
                    cout << "Avg CAARs for Group " << selected_group << endl;
                    cout << calc[1][2] << endl;
                    cout << endl;
                    cout << "Std CAARs for Group " << selected_group << endl;
                    cout << calc[1][3] << endl;
                    cout << endl;
                 }
                break;
            
            case 4:
                plotResults1(calc[0][2],calc[1][2],calc[2][2],2*N);
                break;
            
            case 5:
                plotResults2(calc[0][3],calc[1][3],calc[2][3],2*N);
                break;
            
            case 6:
                plotResults3(calc[0][0],calc[1][0],calc[2][0],2*N);
                break;
            
            case 7:
                plotResults4(calc[0][1],calc[1][1],calc[2][1],2*N);
                break;
                
            case 8:
                quit = true;
                cout<<"Quit Program"<<endl;
                break;
                
            default:
                cout << "Invalid input, Try Again"<<endl;
                break;
                
        }
        
    } while (!quit);
        
 
    
 	return 0;
}


