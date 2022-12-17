#pragma once

#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "Stock.h"
#include "Utility.h"
#include <algorithm>
using namespace std;
using namespace fre;

namespace fre {
    typedef map<string, Stock> stockGroup;

    
    stockGroup shuffle(stockGroup group){
        stockGroup group_re;
        vector<string> key_V;
        for (map<string, Stock>::iterator itr = group.begin(); itr != group.end(); itr++)
        {
            key_V.push_back(itr->first);
        }
        random_shuffle(key_V.begin(), key_V.end());
        
        for (int i=0; i<80; i++)
        {
            group_re[key_V[i]] = group[key_V[i]];//test
        }
        return group_re;
    }
    
    vector<double> calcAAR(stockGroup group, int N){
        vector<double> AAR_t(2*N,0);
        
        for (map<string, Stock>::iterator itr = group.begin(); itr != group.end(); itr++)
        {
            AAR_t = AAR_t + itr->second.getAR();
        }
        AAR_t = AAR_t / 80 * 100;
        return AAR_t;
    }
    
    vector<double> calcCAAR(stockGroup group, int N){
        vector<double> arr_t = calcAAR(group, N);
        vector<double> CAAR(2*N,0);
        double sum = 0.0;
        for (int i = 0; i < 2*N; i++ )
        {
            sum += arr_t[i];
            CAAR[i] = sum;
        }
        return CAAR;
    }
  
    Matrix calculation(stockGroup group, int N){
        Vector AARAcc (2*N, 0);
        Vector CAARAcc (2*N, 0);
        Matrix atmp (40, Vector(2*N, 0));
        Matrix ctmp (40, Vector(2*N, 0));
        Vector AARstd (2*N, 0);
        Vector CAARstd (2*N, 0);
        for (int i = 0; i < 40; i++){
            stockGroup group1 = shuffle(group);
            Vector AAR = calcAAR(group1, N);
            Vector CAAR = calcCAAR(group1, N);
            atmp[i] = AAR;
            ctmp[i] = CAAR;
            AARAcc = AARAcc + AAR;
            CAARAcc = CAARAcc + CAAR;
        }
        Vector AARAvg = AARAcc / 40;
        Vector CAARAvg = CAARAcc / 40;

        atmp = atmp - AARAvg;
        atmp = atmp * atmp;
        ctmp = ctmp - CAARAvg;
        ctmp = ctmp * ctmp;
        for(int i = 0; i < 2*N; i++){
            for (int j = 0; j < 40; j++){
                AARstd[i] += (atmp[j][i] / 40);
                CAARstd[i] += (ctmp[j][i] / 40);
            }
        }
        for(int i = 0; i < 2*N; i++){
            AARstd[i] = sqrt(AARstd[i]);
            CAARstd[i] = sqrt(CAARstd[i]);
        }
        
        Matrix Ret(4);
        Ret[0] = AARAvg;
        Ret[1] = AARstd;
        Ret[2] = CAARAvg;
        Ret[3] = CAARstd;
        return Ret;
    }
    
    void Result(stockGroup beat, stockGroup miss, stockGroup meet, int N, vector<Matrix> &calc){
        Matrix v0 = calculation(beat, N);
        Matrix v1 = calculation(miss, N);
        Matrix v2 = calculation(meet, N);
        calc[0] = v0;
        calc[1] = v1;
        calc[2] = v2;
    }
    
}
