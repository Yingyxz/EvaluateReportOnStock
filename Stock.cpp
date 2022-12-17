#include <string>
#include <vector>
#include <iomanip>
#include <iostream> 
#include "Stock.h"
#include "Transaction.h"
#include "Utility.h"


using namespace std;
using namespace fre;

namespace fre {
    void Stock::addTransaction(const Transaction& aTrans) {
        transaction.push_back(aTrans);
    }

    const string Stock::getTicker(void) const {
        return ticker;
    }

    const vector<Transaction>& Stock::getTransactions(void) const {
        return transaction;
    }

    const vector<Transaction>& Stock::getValidTransactions(void) const {
        return valid_transaction;
    }

    const vector<double>& Stock::getAR(void) const {
        return AR;
    }

    void Stock::setAnnouncementDate(string date) {
        announcement_date = converTime(date);
    }
    
    void Stock::setPeriodEnding(string periodEnding) {
        period_ending = periodEnding;
    }

    bool Stock::findDay0(const string& annDate) {
        for (vector<Transaction>::iterator itr = transaction.begin(); itr != transaction.end(); itr++) {
            if (itr->getDate() == annDate) {
                itr_day0 = itr;
                return true;
            }
        }
        return false;
    }

    bool Stock::computeUsedData(int N, const string& annDate) {
        // Get 2N+1 days of historical prices for r Russell 3000 stocks and ETF ticker IWV 你可以按自己需求更改
        valid = false;
        if (findDay0(annDate)) {
            if (itr_day0 - transaction.begin() < N || transaction.end() - itr_day0 - 1 < N) {
                return false;
            }
            else {
                valid_transaction.clear();
                for (auto itr2 = itr_day0 - N; itr2 <= itr_day0 + N; itr2++) {
                    valid_transaction.push_back(*itr2);
                }
                valid = true;
                return true;
            }
        }
        return false;
    }

    void Stock::computeAR(int N, Stock& benchmark) {
        //Calculate the daily returns， 你可以按自己需求更改
        
        // assume Benchmark has all the date in stk.validTrades
        // compute cumulative daily return at the same time

        if (benchmark.computeUsedData(N, announcement_date)) {
            const vector<Transaction> validT_BM = benchmark.getValidTransactions();
            if (valid_transaction.size() != validT_BM.size())
                cerr << "size of benchmark's historical data does not match the size of " << ticker << "'s data" << endl;

            AR.clear();
            double init_close = valid_transaction[0].getAdjusted_close();
            valid_transaction[0].setcTotal_daily_ret(0.0);
            
            for (int i = 1; i < (int)validT_BM.size(); i++) {
                // if (valid_transaction[i].getAdjusted_close() <= 0) { cout << ticker << endl; }
                // cumulative daily return
                valid_transaction[i].setcTotal_daily_ret((valid_transaction[i].getAdjusted_close() / init_close - 1));

                double ret = (valid_transaction[i].getAdjusted_close() / valid_transaction[i - 1].getAdjusted_close() -1);
                valid_transaction[i].set_daily_ret(ret);
                double ret_BM = (validT_BM[i].getAdjusted_close() / validT_BM[i - 1].getAdjusted_close() -1);
                AR.push_back(ret - ret_BM);
;            }
        }
        else {
            // error msg
            cerr << "size of benchmark's historical data is not enough" << endl;
        }

    }

    void Stock::printValidTransaction()const {
        string line(13 + 10 * 5 + 15+17, '_');
        cout << setw(13) << "Date" << "|";
        cout << setw(10) << "Open" << "|";
        cout << setw(10) << "Hige" << "|";
        cout << setw(10) << "Low" << "|";
        cout << setw(10) << "Close" << "|";
        cout << setw(10) << "Adj. Close" << "|";
        cout << setw(15) << "Cum. Daily Ret" << "|";
        cout << setw(15) << "Volume" << endl;
        cout << line << endl;
        for (int i = 0; i < (int)valid_transaction.size(); i++) {
            cout << valid_transaction[i];
        }
    }
    void Stock::printTransactions()const {
        string line(13 + 10 * 5 + 15, '_');
        cout << setw(13) << "Date" << "|";
        cout << setw(10) << "Open" << "|";
        cout << setw(10) << "Hige" << "|";
        cout << setw(10) << "Low" << "|";
        cout << setw(10) << "Close" << "|";
        cout << setw(10) << "Adj. Close" << "|";
        cout << setw(15) << "Volume" << endl;
        cout << line << endl;
        for (int i = 0; i < (int)transaction.size(); i++) {
            cout << transaction[i];
        }
    }

    void Stock::printInfo() const {
        cout<<setiosflags(ios::left);
        cout << setprecision(2);
        cout << "Stock Info " << endl;
        cout << setw(40) << "Ticker: " << ticker << endl;
        if (ticker != "IWV") {
            cout << setw(40) << "Earning Announcement Date: " << announcement_date << endl;
            cout << setw(40) << "Earning Period Endings: " << period_ending << endl;
            cout << setw(40) << "Earning Estimate: " << fixed<<setprecision(3)<<estimated_earnings << endl;
            cout << setw(40) << "Reported Earning per Share: " << fixed<<setprecision(3)<< reported_earnings << endl;
            cout << setw(40) << "Earning Suprise: " << fixed<<setprecision(3)<< surprise << endl;
            cout << setw(40) << "Earning Supring Percentage: " << fixed<<setprecision(3)<<surprise_pct << endl;
            cout << setw(40) << "Group: " << group << endl;
            if(valid)
            {
                cout << setw(40) << "No Enough Daily Price Data: " << "False" << endl;
            }
            else
            {
                cout<< setw(40) << "No Enough Daily Price Data: " << "True" << endl;
            }
            cout<<endl;
            cout<<endl;
            
        }

    }

}
