#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;
using namespace fre;
void plotResults1(vector<double> beat, vector<double> miss, vector<double> meet, int dataSize)
{
    FILE *gnuplotPipe,*tempDataFile;
    const char *tempDataFileName1 = "Beat";
    const char *tempDataFileName2 = "Miss";
    const char *tempDataFileName3 = "Meet";
    
    double x1,y1, x2, y2,x3,y3;
    int i;
    const char *title = "Avg CAAR for 3 Groups";
    const char *yLabel ="Avg CAAR(%)";
    gnuplotPipe = popen("gnuplot -persist", "w");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title '%s'\n", title);
    fprintf(gnuplotPipe, "set arrow from 0,graph(0,0) to 0,graph(1,1) nohead lc rgb 'red'\n");
    fprintf(gnuplotPipe, "set xlabel 'Announcement Date'\nset ylabel '%s'\n", yLabel);
    if (gnuplotPipe) {
        fprintf(gnuplotPipe,"plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines \n",tempDataFileName1, tempDataFileName2, tempDataFileName3);
        fflush(gnuplotPipe);
        tempDataFile = fopen(tempDataFileName1,"w");
        for (i=0; i < dataSize; i++) {
            x1 = i-(dataSize/2);
            y1 = beat[i];
            fprintf(tempDataFile,"%lf %lf\n",x1,y1);
        }
        fclose(tempDataFile);
        tempDataFile = fopen(tempDataFileName2,"w");
        for (i=0; i < dataSize; i++) {
            x2 = i-(dataSize/2);
            y2 = miss[i];
            fprintf(tempDataFile,"%lf %lf\n",x2,y2);
        }
        fclose(tempDataFile);
        tempDataFile = fopen(tempDataFileName3,"w");
        for (i=0; i < dataSize; i++) {
            x3 = i-(dataSize/2);
            y3 = meet[i];
            fprintf(tempDataFile,"%lf %lf\n",x3,y3);
        }
        fclose(tempDataFile);
        printf("press enter to continue...");
        getchar();
        // remove(tempDataFileName1);
        // remove(tempDataFileName2);
        // remove(tempDataFileName3);
        fprintf(gnuplotPipe,"exit \n");
    } else {        
        printf("gnuplot not found...");    
    }
} 

void plotResults2(vector<double> beat, vector<double> miss, vector<double> meet, int dataSize)
{
    FILE *gnuplotPipe,*tempDataFile;
    const char *tempDataFileName1 = "Beat";
    const char *tempDataFileName2 = "Miss";
    const char *tempDataFileName3 = "Meet";
    
    double x1,y1, x2, y2,x3,y3;
    int i;
    const char *title = "Std CAAR for 3 Groups";
    const char *yLabel = "Std CAAR(%)";
    gnuplotPipe = popen("gnuplot -persist", "w");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title '%s'\n", title);
    fprintf(gnuplotPipe, "set arrow from 0,graph(0,0) to 0,graph(1,1) nohead lc rgb 'red'\n");
    fprintf(gnuplotPipe, "set xlabel 'Announcement Date'\nset ylabel '%s'\n", yLabel);
    if (gnuplotPipe) {
        fprintf(gnuplotPipe,"plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines \n",tempDataFileName1, tempDataFileName2, tempDataFileName3);
        fflush(gnuplotPipe);
        tempDataFile = fopen(tempDataFileName1,"w");
        for (i=0; i < dataSize; i++) {
            x1 = i-(dataSize/2);
            y1 = beat[i];
            fprintf(tempDataFile,"%lf %lf\n",x1,y1);
        }
        fclose(tempDataFile);
        tempDataFile = fopen(tempDataFileName2,"w");
        for (i=0; i < dataSize; i++) {
            x2 = i-(dataSize/2);
            y2 = miss[i];
            fprintf(tempDataFile,"%lf %lf\n",x2,y2);
        }
        fclose(tempDataFile);
        tempDataFile = fopen(tempDataFileName3,"w");
        for (i=0; i < dataSize; i++) {
            x3 = i-(dataSize/2);
            y3 = meet[i];
            fprintf(tempDataFile,"%lf %lf\n",x3,y3);
        }
        fclose(tempDataFile);
        printf("press enter to continue...");
        getchar();
        // remove(tempDataFileName1);
        // remove(tempDataFileName2);
        // remove(tempDataFileName3);
        fprintf(gnuplotPipe,"exit \n");
    } else {        
        printf("gnuplot not found...");    
    }
} 

void plotResults3(vector<double> beat, vector<double> miss, vector<double> meet, int dataSize)
{
    FILE *gnuplotPipe,*tempDataFile;
    const char *tempDataFileName1 = "Beat";
    const char *tempDataFileName2 = "Miss";
    const char *tempDataFileName3 = "Meet";
    
    double x1,y1, x2, y2,x3,y3;
    int i;
    const char *title = "Avg AAR for 3 Groups";
    const char *yLabel = "Avg AAR(%)";
    gnuplotPipe = popen("gnuplot -persist", "w");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title '%s'\n", title);
    fprintf(gnuplotPipe, "set arrow from 0,graph(0,0) to 0,graph(1,1) nohead lc rgb 'red'\n");
    fprintf(gnuplotPipe, "set xlabel 'Announcement Date'\nset ylabel '%s'\n", yLabel);
    if (gnuplotPipe) {
        fprintf(gnuplotPipe,"plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines \n",tempDataFileName1, tempDataFileName2, tempDataFileName3);
        fflush(gnuplotPipe);
        tempDataFile = fopen(tempDataFileName1,"w");
        for (i=0; i < dataSize; i++) {
            x1 = i-(dataSize/2);
            y1 = beat[i];
            fprintf(tempDataFile,"%lf %lf\n",x1,y1);
        }
        fclose(tempDataFile);
        tempDataFile = fopen(tempDataFileName2,"w");
        for (i=0; i < dataSize; i++) {
            x2 = i-(dataSize/2);
            y2 = miss[i];
            fprintf(tempDataFile,"%lf %lf\n",x2,y2);
        }
        fclose(tempDataFile);
        tempDataFile = fopen(tempDataFileName3,"w");
        for (i=0; i < dataSize; i++) {
            x3 = i-(dataSize/2);
            y3 = meet[i];
            fprintf(tempDataFile,"%lf %lf\n",x3,y3);
        }
        fclose(tempDataFile);
        printf("press enter to continue...");
        getchar();
        // remove(tempDataFileName1);
        // remove(tempDataFileName2);
        // remove(tempDataFileName3);
        fprintf(gnuplotPipe,"exit \n");
    } else {        
        printf("gnuplot not found...");    
    }
} 

void plotResults4(vector<double> beat, vector<double> miss, vector<double> meet, int dataSize)
{
    FILE *gnuplotPipe,*tempDataFile;
    const char *tempDataFileName1 = "Beat";
    const char *tempDataFileName2 = "Miss";
    const char *tempDataFileName3 = "Meet";
    
    double x1,y1, x2, y2,x3,y3;
    int i;
    const char *title = "Std AAR for 3 Groups";
    const char *yLabel = "Std AAR(%)";
    gnuplotPipe = popen("gnuplot -persist", "w");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title '%s'\n", title);
    fprintf(gnuplotPipe, "set arrow from 0,graph(0,0) to 0,graph(1,1) nohead lc rgb 'red'\n");
    fprintf(gnuplotPipe, "set xlabel 'Announcement Date'\nset ylabel '%s'\n", yLabel);
    if (gnuplotPipe) {
        fprintf(gnuplotPipe,"plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines \n",tempDataFileName1, tempDataFileName2, tempDataFileName3);
        fflush(gnuplotPipe);
        tempDataFile = fopen(tempDataFileName1,"w");
        for (i=0; i < dataSize; i++) {
            x1 = i-(dataSize/2);
            y1 = beat[i];
            fprintf(tempDataFile,"%lf %lf\n",x1,y1);
        }
        fclose(tempDataFile);
        tempDataFile = fopen(tempDataFileName2,"w");
        for (i=0; i < dataSize; i++) {
            x2 = i-(dataSize/2);
            y2 = miss[i];
            fprintf(tempDataFile,"%lf %lf\n",x2,y2);
        }
        fclose(tempDataFile);
        tempDataFile = fopen(tempDataFileName3,"w");
        for (i=0; i < dataSize; i++) {
            x3 = i-(dataSize/2);
            y3 = meet[i];
            fprintf(tempDataFile,"%lf %lf\n",x3,y3);
        }
        fclose(tempDataFile);
        printf("press enter to continue...");
        getchar();
        // remove(tempDataFileName1);
        // remove(tempDataFileName2);
        // remove(tempDataFileName3);
        fprintf(gnuplotPipe,"exit \n");
    } else {        
        printf("gnuplot not found...");    
    }
} 