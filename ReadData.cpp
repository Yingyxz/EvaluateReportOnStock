#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <thread>
#include "curl/curl.h"
#include "ReadData.h"
#include "Stock.h" 
#include "Utility.h"

using namespace std;
using namespace fre;
const char* cIWV3000SymbolFile = "Russell_3000_component_stocks.csv";
const string config_file = "conFig_file.csv";
const string annoucement_file = "Russell3000EarningsAnnouncements.csv";

namespace fre {
	void ReadData::loadConfig() {

        map<string, string> configMap;
        ifstream fin;
        fin.open(config_file, ios::in);
        string line, name, value;
        while (!fin.eof()) {
            getline(fin, line);
            stringstream sin(line);
            getline(sin, name, ':');
            getline(sin, value);
            configMap.insert(pair<string, string>(name, value));
        }

        api_token = configMap["api_token"];
        if (!api_token.empty() && api_token[api_token.length() - 1] == '\r') {
            api_token.erase(api_token.size() - 1);
        }
        url_common = configMap["url_common"];
        if (!url_common.empty() && url_common[url_common.length() - 1] == '\r') {
            url_common.erase(url_common.size() - 1);
        }
        start_date = configMap["start_date"];
        if (!start_date.empty() && start_date[start_date.length() - 1] == '\r') {
            start_date.erase(start_date.size() - 1);
        }
        end_date = configMap["end_date"];
        if (!end_date.empty() && end_date[end_date.length() - 1] == '\r') {
            end_date.erase(end_date.size() - 1);
        }


	}

    void ReadData::loadTickerList() {
    
        ifstream fin;
        fin.open(cIWV3000SymbolFile, ios::in);
        string line, name, symbol;
        ticker_list.push_back("IWV");
        while (!fin.eof())
        {
            getline(fin, line);
            if(fin.fail()){
                break;
            }
            stringstream sin(line);
            getline(sin, symbol, ',');
            getline(sin, name);
            ticker_list.push_back(symbol);
        }
        
    }
    void ReadData::loadDataCsv() {
        ifstream fin;
        fin.open(annoucement_file, ios::in);
        string line, ticker, date, periodEnding, estimate, reported, surprise, surprisePct;
        getline(fin, line);
        while (!fin.eof()) {
            vector<string> factors;
            getline(fin, line);
            stringstream sin(line);
            getline(sin, ticker, ',');
            getline(sin, date, ',');
            factors.push_back(date);
            getline(sin, periodEnding, ',');
            factors.push_back(periodEnding);
            getline(sin, estimate, ',');
            factors.push_back(estimate);
            getline(sin, reported, ',');
            factors.push_back(reported);
            getline(sin, surprise, ',');
            factors.push_back(surprise);
            getline(sin, surprisePct);
            factors.push_back(surprisePct);
            if (ticker.empty()) {
                continue;
            }
            
            data_csv[ticker] = factors;
        }
    }

    int ReadData::loadDataCurl(vector<string> ticker_list_) {

        // file pointer to create file that store the data 
        // FILE* fp;
        // const char resultfilename[FILENAME_MAX] = "Results.txt";
        // declaration of an object CURL 
        CURL* handle;
        CURLcode result;
        // set up the program environment that libcurl needs 
        curl_global_init(CURL_GLOBAL_ALL);
        // curl_easy_init() returns a CURL easy handle 
        handle = curl_easy_init();

        // if everything's all right with the easy handle... 
        if (handle)
        {
            // string url_common = "https://eodhistoricaldata.com/api/eod/";
            // string start_date = "2022-02-01";
            // string end_date = "2022-12-09";
            // string api_token = "637d669b050096.23435820";
            // You must replace this API token with yours
            
            vector<string>::iterator itr = ticker_list_.begin();
            // int count = 0;
            
            for (; itr != ticker_list_.end(); itr++)
            {
                // count++;
                // if(count > (int)ticker_list_.size()){
                //     break;
                // }
                struct MemoryStruct data;
                data.memory = NULL;
                data.size = 0;
                string symbol = *itr;
                string url_request = url_common + symbol + ".US?" + "from=" + start_date + "&to=" + end_date + "&api_token=" + api_token + "&period=d";
                curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());

                //adding a user agent
                curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko / 20100101Firefox / 74.0");
                curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
                curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
                // fp = fopen(resultfilename, "ab");
                // fprintf(fp, "%s\n", symbol.c_str());
                // curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
                // curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);

                // result = curl_easy_perform(handle);
;
                // fprintf(fp, "%c", '\n');
                // fclose(fp);
                // // check for errors 
                // if (result != CURLE_OK) {
                //     fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(result));
                //     return -1;
                // }

                curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
                curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
                
                result = curl_easy_perform(handle);
                // Store all the data for each ticker
                
                if (result != CURLE_OK)
                {
                    // if errors have occurred, tell what is wrong with result
                    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
                    return 1;
                }
                // string data_str = data.memory;
                data_curl[symbol] = data.memory;
                
                //cout << count;
                //printf("\b");
                //cout << '\b';
                // stringstream sData;
                // sData.str(data.memory);
                // string sValue, sDate;
                // double dValue = 0;
                // string line;
                // 
                // cout << symbol << endl;;
                // 
                // while (getline(sData, line)) {
                //     size_t found = line.find('-');
                //     if (found != std::string::npos)
                //     {
                //         cout << line << endl;
                //         sDate = line.substr(0, line.find_first_of(','));
                //         line.erase(line.find_last_of(','));
                //         sValue = line.substr(line.find_last_of(',') + 1);
                //         dValue = strtod(sValue.c_str(), NULL);
                //         cout << sDate << " " << std::fixed << ::setprecision(6) << dValue << endl;
                //     }
                // }
                


                
                free(data.memory);
                data.size = 0;
                
                // //debug
                // if(count == 10){
                //      break;
                //  }
                
            }
        }
        else
        {
            fprintf(stderr, "Curl init failed!\n");
            return -1;
        }
        // cleanup since you've used curl_easy_init
        curl_easy_cleanup(handle);
        // release resources acquired by curl_global_init() 
        curl_global_cleanup();
        return 0;
    }
    
    // void ReadData::loadDataCurl_thread() {
        
    // }
    
    void ReadData::storeStocks() {

        for (string str : ticker_list) {
            
            Stock stock(str);

            vector<string> dailyData = split(data_curl[str], '\n'); // daily

            int count = 0;
            for (string data : dailyData) {
                if (count == 0) {
                    count++;
                    continue;
                }

                
                vector<string> fields = split(data, ',');
                
                if (fields.size() == 1) {
                    continue;
                }
                

                string date = fields[0];
                double open = stod(fields[1]);
                double high = stod(fields[2]);
                double low = stod(fields[3]);
                double close = stod(fields[4]);
                double adjClose = stod(fields[5]);
                int volume = stoi(fields[6]);
                Transaction trans(date, open, high, low, close, adjClose, volume);
                stock.addTransaction(trans);
                
            }
            
            if (str == "IWV") {
                stock.setAnnouncementDate(data_csv["A"][0]);
                IWV = stock;
            }
            
            if(data_csv.find(str) == data_csv.end()){
                continue;
            }
            
            if (str != "IWV" ) {
                stock.setAnnouncementDate(data_csv[str][0]);
                stock.setPeriodEnding(data_csv[str][1]);
                stock.setEstimatedEarnings(stof(data_csv[str][2]));
                stock.setReportedEarnings(stof(data_csv[str][3]));
                stock.setSuprise(stof(data_csv[str][4]));
                stock.setSuprisePct(stof(data_csv[str][5]));
            }

            Stocks[str] = stock;

        }
    }

}


