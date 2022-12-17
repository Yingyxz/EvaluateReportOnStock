#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include "Stock.h"

using namespace std;

namespace fre {
	class ReadData {
	private:
		string api_token;
		string start_date;
		string end_date;
		string url_common;

		vector<string> ticker_list;
		map<string, vector<string>> data_csv;
		map<string, string> data_curl;
		Stock IWV;
		map<string, Stock> Stocks;
	public:
		ReadData() {
			loadConfig();
		}
		~ReadData(){}

		void loadConfig();
		void loadTickerList();
		void loadDataCsv();
		int loadDataCurl(vector<string> ticker_list_);
		void storeStocks();
		
		// Getter
		vector<string> getTicker_list() { return ticker_list; }
		map<string, vector<string>> getData_csv() { return data_csv; }
		map<string, string> getData_curl(){ return data_curl; }
		Stock getIWV(){ return IWV; }
		map<string, Stock> getStocks() { return Stocks; }

		
	};



}
