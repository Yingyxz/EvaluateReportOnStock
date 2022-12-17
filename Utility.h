#pragma once
#include <stdio.h>
#include <string> 
#include <iostream>
#include <sstream> 
#include <vector>
#include <locale>
#include <iomanip>
#include <cmath>
#include <map>
#include "curl/curl.h"
using namespace std;

namespace fre {
	
	typedef vector<double> Vector;
	typedef vector<Vector> Matrix;
	// overload operators as independent functions
	Vector operator*(const Matrix& C, const Vector& V);
	Vector operator*(const Vector& V, const double& a);
	Vector operator*(const Vector& V, const Vector& W);
	Vector operator+(const double& a, const Vector& V);
	Vector operator+(const Vector& V, const Vector& W);  // referece to const for V and W, V + W -> U, V and W do not change
	Vector exp(const Vector& V);
	Vector operator/(const Vector& V, const double& a);
	Matrix operator-(const Matrix& V, const Vector& W);
	Matrix operator*(const Matrix& M, const Matrix& W);
	
	
	double operator^(const Vector& V, const Vector& W); // scalar operator
	ostream& operator<<(ostream& out, Vector& V);	// Overload cout for Vector
	ostream& operator<<(ostream& out, Matrix& W);	// Overload cout for Matrix
	
	struct MemoryStruct {
		char* memory;
		size_t size;
	};
	
	// Helper functions
	
	//Invoked in ReadData()
	int write_data(void* ptr, int size, int nmemb, FILE* stream);
	void* myrealloc(void* ptr, size_t size);
	int write_data2(void* ptr, size_t size, size_t nmemb, void* data);
	vector<string> split(string text, char delim);
	
	//Invoked in ReadData()
	string& stringCapitalize(string& str);
	string converTime(string date);
	
	//Invoked in main()
	bool cmp(pair<string, double> a, pair<string, double> b);
	vector<string> sort(map<string, double> M);
	vector<string> slice(vector<string>& list, int X, int Y);
}



