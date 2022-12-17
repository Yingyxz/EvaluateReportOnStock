#pragma once

#include <iostream>
#include <string>
using namespace std;

namespace fre {
	class Transaction {

	private:
        string date;
        double open;
        double high;
        double low;
        double close;
        double adj_close;
        double total_daily_ret;
        double daily_ret;
        int volume;


    public:
        Transaction(string date_, double open_, double high_, double low_, double close_, double adj_close_, int volume_) :
            date(date_), open(open_), high(high_), low(low_), close(close_), adj_close(adj_close_), total_daily_ret(0.0),daily_ret(0.0),volume(volume_) {}
        ~Transaction() {}

        // getter
        double getOpen() const;
        double getHigh() const;
        double getLow() const;
        double getClose() const;
        int getVolume() const;
        string getDate() const;
        double getAdjusted_close() const;
        double getcumDailyRet() const { return total_daily_ret; }
        double getDailyRet() const {return daily_ret;}

        // setter
        void setcTotal_daily_ret(double total_daily_ret_) { total_daily_ret = total_daily_ret_; }
        void set_daily_ret(double daily_ret_){daily_ret = daily_ret_;}

        friend ostream& operator<<(ostream& out, const Transaction& trade); // Overload cout for trade
	};
}
