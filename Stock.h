#pragma once

#include <string>
#include <vector>
#include <iomanip>
#include "Transaction.h"

using namespace std;
using namespace fre;

namespace fre {
    class Stock {
    private:
        string ticker;
        string announcement_date;
        string period_ending;
        double estimated_earnings;
        double reported_earnings;
        double surprise;
        double surprise_pct;
        string group;

        vector<Transaction> transaction;
        vector<Transaction> valid_transaction;
        vector<double> AR;
        vector<Transaction>::iterator itr_day0;
        bool valid = false;

        bool findDay0(const string& annDate);


    public:
        Stock() : ticker("") {
            transaction.clear();
        }
        Stock(string ticker_) : ticker(ticker_) {
            transaction.clear();
        }
        Stock(const Stock& stock) {
            ticker = stock.ticker;
            announcement_date = stock.announcement_date;
            period_ending = stock.period_ending;
            estimated_earnings = stock.estimated_earnings;
            reported_earnings = stock.reported_earnings;
            surprise = stock.surprise;
            surprise_pct = stock.surprise_pct;
            group = stock.group;

            transaction = stock.transaction;
            valid_transaction = stock.valid_transaction;
            AR = stock.AR;
            valid = stock.valid;
            itr_day0 = stock.itr_day0;
        }
        ~Stock() {}

        void addTransaction(const Transaction& transaction);

        bool computeUsedData(int N, const string& annDate);
        void computeAR(int N, Stock& benchmark);
        
        // setter
        void setAnnouncementDate(string date);
        void setPeriodEnding(string periodEnding);
        void setEstimatedEarnings(double estimated_earnings_) { estimated_earnings = estimated_earnings_; }
        void setReportedEarnings(double reported_earnings_) { reported_earnings = reported_earnings_; }
        void setSuprise(double suprise_) { surprise = suprise_; }
        void setSuprisePct(double surprise_pct_) { surprise_pct = surprise_pct_; }
        void setGroup(string group_) { group = group_; }

        // getter
        const string getTicker(void) const;
        const string getAnnouncementDate(void) const { return announcement_date; };
        const vector<Transaction>& getTransactions(void) const;
        const vector<Transaction>& getValidTransactions(void) const;
        const vector<double>& getAR(void) const;
        void printValidTransaction()const;
        void printTransactions()const;
        void printInfo() const;
        void printValidTransactionDate()
        {
            for (int i = 0; i<(int)valid_transaction.size();i++)
            {cout<<setiosflags(ios::left)<<setw(12)<< valid_transaction[i].getDate() ;
                if ((i+1) % 10 == 0){
                    cout << endl;
                }
            }
            cout << endl;
        }
        void printValidTransactionDailyPrice()
        {
            for (int i = 0; i<(int)valid_transaction.size();i++)
            {cout<<setiosflags(ios::left)<<setw(10)<< valid_transaction[i].getAdjusted_close() ;
                if ((i+1) % 10 == 0){
                    cout << endl;
                }
            }
            cout << endl;
        }
        
        void printValidTransactionDailyReturn()
        {
            for (int i = 1; i<(int)valid_transaction.size();i++)
            {cout<<setiosflags(ios::left)<<setw(10)<< valid_transaction[i].getDailyRet();
                if ((i) % 10 == 0){
                    cout << endl;
                }
            }
            cout << endl;
            
        }
        
        void printValidTransactionCumulativeDailyReturn()
        {
            for (int i = 1; i<(int)valid_transaction.size();i++)
            {cout<<setiosflags(ios::left)<<setw(10)<< valid_transaction[i].getcumDailyRet() ;
                if ((i) % 10 == 0){
                    cout << endl;
                }
            }
            cout << endl;
            
        }
        
        void printValidTransactionAR()
        {
            for (int i = 0; i<(int)valid_transaction.size()-1;i++)
            {cout<<setiosflags(ios::left)<<setw(10)<< AR[i] ;
                if ((i+1) % 10 == 0){
                    cout << endl;
                }
            }
            cout << endl;
        }
    };
}


