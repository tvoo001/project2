#ifndef __ALGORITHM_H__
#define __ALOGRITHM_H__

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>
#include "classifier.h"
#include <bitset>

using namespace std;

class Algorithm
{
    public:
        Algorithm();
        vector<int> features;
        int trait;
        string listFeatures;
        string globalFeatures;
        double accuracy;
        char letter;
        double localHighestAccuracy;
        double globalHighestAccuracy;
        double forwardSearch(int i);
        double backwardSearch(int i);
        string removeLetter(int item);
        void removeFeature(int trait);
        bool checkList(int trial);
        double calculateAccuracy(vector<int> selectedFeatures);
        string numberConvert(int trail);
    friend class Classifier;
};
#endif 