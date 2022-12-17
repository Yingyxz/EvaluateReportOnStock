#include "Utility.h"
#include <stdio.h>
#include <string> 
#include <string.h>
#include <iostream>
#include <sstream> 
#include <vector>
#include <locale>
#include <iomanip>
#include <map>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;


namespace fre {

	Vector operator*(const Matrix& C, const Vector& V)
	    {
	        int d = (int)C.size();
	        Vector W(d);
	        for (int j = 0; j < d; j++)
	        { 
	            W[j] = 0.0;
	            for (int l = 0; l < d; l++) W[j] = W[j] + C[j][l] * V[l];
	        }
	        return W;
	    }
	    
	Matrix operator-(const Matrix& V, const Vector& W){
	    int d = (int)V.size();
        int m = (int)W.size();
	    Matrix U (d, Vector(m, 0));
	    for (int i = 0; i < d; i++) {
            for (int j = 0; j < m; j++){
                U[i][j] = V[i][j] - W[j];
            }
        }
	    return U;
	}
	
	Matrix operator*(const Matrix& M, const Matrix& W)
	{
	    int d = (int)M.size();
        int m = (int)M[0].size();
	    Matrix U (d, Vector(m, 0));
	    for (int i = 0; i < d; i++) {
            for (int j = 0; j < m; j++){
                U[i][j] = M[i][j] * W[i][j];
            }
        }
	    return U;
	}
	
	Vector operator+(const Vector& V, const Vector& W)
	{
	    int d = (int)V.size();
	    Vector U(d);
	    for (int j = 0; j < d; j++) U[j] = V[j] + W[j];
	    return U;
	}
	
	Vector operator+(const double& a, const Vector& V)
	{
	    int d = (int)V.size();
	    Vector U(d);
	    for (int j = 0; j < d; j++) U[j] = a + V[j];
	    return U;
	}
	
	Vector operator*(const Vector& V, const double& a)
	{
	    int d = (int)V.size();
	    Vector U(d);
	    for (int j = 0; j < d; j++) U[j] = a * V[j];
	    return U;
	}
	
	Vector operator*(const Vector& V, const Vector& W)
	{
	    int d = (int)V.size();
	    Vector U(d);
	    for (int j = 0; j < d; j++) U[j] = V[j] * W[j];
	    return U;
	}
	
	Vector exp(const Vector& V)
	{
	    int d = (int)V.size();
	    Vector U(d);
	    for (int j = 0; j < d; j++) U[j] = std::exp(V[j]);
	    return U;
	}
	
	Vector operator/(const Vector& V, const double& a)
	{
		int d = (int)V.size();
	    Vector U(d);
	    for (int j = 0; j < d; j++) U[j] = V[j] / a;
	    return U;
	}
	
	double operator^(const Vector& V, const Vector& W)
	{
	    double sum = 0.0;
	    int d = (int)V.size();
	    for (int j = 0; j < d; j++) sum = sum + V[j] * W[j];
	    return sum;
	}
	
	// overload cout for vector, cout every element in the vector
	ostream& operator<<(ostream& out, Vector& V)
	{
		int count = 0;
	    for (Vector::iterator itr = V.begin(); itr != V.end(); itr++)
	    {
	    	out<<fixed<<setprecision(3);
	    	out <<setiosflags(ios::left)<<setw(10)<< *itr;
	    	count = count + 1;
	    	if (count % 11 == 0)
	    	{
	    		cout<<endl;
	    	}
	    }
	    out << endl;
	    return out;
	}
	
	ostream& operator<<(ostream& out, Matrix& W)
	{
	    for (Matrix::iterator itr = W.begin(); itr != W.end(); itr++)
	        out << *itr;    // Use ostream & operator<<(ostream & out, Vector & V)
	    out << endl;
	    return out;
	}
	
	int write_data(void* ptr, int size, int nmemb, FILE* stream)
	{
		size_t written;
		written = fwrite(ptr, size, nmemb, stream);
		return written;
	}
	void* myrealloc(void* ptr, size_t size)
	{
		if (ptr)
			return realloc(ptr, size);
		else
			return malloc(size);
	}
	int write_data2(void* ptr, size_t size, size_t nmemb, void* data) {
		size_t realsize = size * nmemb;
		struct MemoryStruct* mem = (struct MemoryStruct*)data;
		mem->memory = (char*)myrealloc(mem->memory, mem->size + realsize + 1);
		if (mem->memory) {
			memcpy(&(mem->memory[mem->size]), ptr, realsize);
			mem->size += realsize;
			mem->memory[mem->size] = 0;
		}
		return realsize;
	
	}
	
	
	
	vector<string> split(string text, char delim) {
		string line;
		vector<string> vec;
		stringstream ss(text);
		while (std::getline(ss, line, delim)) {
			vec.push_back(line);
		}
		return vec;
	}
	
	string& stringCapitalize(string& str) {
	    transform(str.begin(), str.end(), str.begin(), ::toupper);
	    return str;
	}
	
	string converTime(string date) {
	    vector<string> dmy = split(date, '-');
	    map<string, string> monthMap = {{"JAN", "01"}, {"FEB", "02"}, {"MAR", "03"}, {"APR", "04"}, {"MAY", "05"}, {"JUN", "06"}, {"JUL", "07"}, {"AUG", "08"}, {"SEP", "09"}, {"OCT", "10"}, {"NOV", "11"}, {"DEC", "12"}};
	    string day = dmy[0].size() == 1 ? "0"+dmy[0] : dmy[0];
	    string month = monthMap[stringCapitalize(dmy[1])];
	    string year = "20"+dmy[2];
	    return year + "-" + month + "-" + day;
	}
	
	
	// Invoked in main()
	bool cmp(pair<string, double> a, pair<string, double> b) {
        return a.second < b.second;
    }

    vector<string> sort(map<string, double> M) {
        vector<pair<string, double> > A;
        
        for (auto& it : M) {
            A.push_back(it);
        }
        
        sort(A.begin(), A.end(), cmp);
        vector<string> res;
        
        for (auto& it : A) {
            res.push_back(it.first);
        }
        
        return res;
    }
    
    vector<string> slice(vector<string>& list, int X, int Y) {
        auto start = list.begin() + X;
        auto end = list.begin() + Y + 1;
     
        vector<string> res(Y - X + 1);
        copy(start, end, res.begin());

        return res;
    }
}