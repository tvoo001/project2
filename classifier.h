#ifndef __CLASSIFIER_H__
#define __CLASSIFIER_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <set>
using namespace std;

class Classifier
{
    public:
    int counter = 0;
    Classifier();
    Classifier(vector<int> selectedFeatures, int r, int c, string fname);
    void makeSet(vector<int> comb, int r, int k, string dataset);
    double data[100][11];
    double largeData[1000][40];
    bool KNN(vector<int> temp, int k);
    int countLabels(vector<int> temp);
    double test(string file, vector<int> currentSet, int featureToAdd);
    double largeTest(string file, vector<int> currentSet, int featureToAdd);
    bool featureChecker(vector<int> selectedFeatures, int k);
    friend class Algorithm;
};
#endif