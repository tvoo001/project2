#include "classifier.h"

Classifier::Classifier() // Train Part of Classifier Class
{
    double temp;
    ifstream fs("large-test-dataset.txt");
    int i = 0;
    int k = 0;
    if(fs.is_open())
    {
        while (fs >> temp)
        {
            data[i][k] = temp;
            k++;
            if (k == 40)
            {
                i++;
                k = 0;
            }
        }
    }
    fs.close();
}

Classifier::Classifier(vector<int> selectedFeatures, int r, int c, string fname)
{
    int ex = 0;
    double temp;
    ifstream fs(fname);
    int i = 0;
    int k = 0;

    if(fs.is_open())
    {
        while (fs >> temp)
        {
            if (featureChecker(selectedFeatures, k))
            {
                data[i][k] = temp;
                largeData[i][k] = temp;
            }
            else
            {
                data[i][k] = 0;
                largeData[i][k] = 0;
            }
            k++;
            counter++;
            // cout << "Temp = " << largeData[i][k] << "  ";
            if (k == c)
            {
                i++;
                k = 0;
                // cout << endl;
            }
            if (i == 1000)
            {
                fs.close();
            }
        }
    }
    fs.close();
}

bool Classifier::featureChecker(vector<int> selectedFeatures, int k)
{
    for(int i = 0; i < selectedFeatures.size(); i++)
    {
        if (k == 0)
        {
            return true;
        }
        if (selectedFeatures.at(i) == k)
        {
            return true;
        }
    }
    return false;
}

bool Classifier::KNN(vector<int> temp, int k)
{
    for(int i = 0; i < temp.size(); i++)
    {
        if (temp.at(i) == k)
        {
            return false;
        }
    }
    return true;
}

int Classifier::countLabels(vector<int> temp)
{
    int class1 = 0;
    int column = 0;
    for(int i = 0; i < temp.size(); i++)
    {
        column = temp.at(i);
        if (largeData[column][0] == 1)
        {
            class1++;
        }
    }
    if (class1 >= 2)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

void Classifier::makeSet(vector<int> comb, int r, int c, string dataset)
{
    int ex = 0;
    double temp;
    ifstream fs(dataset);
    int i = 0;
    int k = 0;

    if(fs.is_open())
    {
        while (fs >> temp)
        {
            if (featureChecker(comb, k))
            {
                data[i][k] = temp;
                largeData[i][k] = temp;
            }
            else
            {
                data[i][k] = 0;
                largeData[i][k] = 0;
            }
            k++;
            counter++;
            if (k == c)
            {
                i++;
                k = 0;
            }
            if (i == 1000)
            {
                fs.close();
            }
        }
    }
    fs.close();
    // double mean = 0;
    // double largeMean = 0; 
    // double standard = 0;
    // double lStandard = 0;
    // double score = 0;
    // double lscore = 0;
    // for (int k = 1; k < c; k++)
    // {
    //     if (featureChecker(comb, k))
    //     {
    //         for (int i = 0; i < r; i++)
    //             {
    //                 mean = mean + data[i][k];
    //                 largeMean = largeMean + largeData[i][k];
    //             }
    //         mean = mean / 100;
    //         largeMean = largeMean / 1000;
    //         for (int i = 0; i < r; i++)
    //             {
    //                 standard = standard + pow((data[i][k] - mean), 2);
    //                 lStandard = lStandard + pow((largeData[i][k] - largeMean), 2);
    //             }
    //         standard = sqrt((standard/99));
    //         lStandard = sqrt((lStandard/999));
    //         for (int i = 0; i < r; i++)
    //             {
    //                 score = (data[i][k] - mean)/ standard;
    //                 lscore = (largeData[i][k] - largeMean) / lStandard;
    //                 data[i][k] = score;
    //                 largeData[i][k] = lscore;
    //             }
    //     }
    // }
    

}
double Classifier::test(string file, vector<int> currentSet, int featureToAdd) // Classifier Test Part
{
    makeSet(currentSet, 100, 11, file);
    vector<int> temp;
    double distance = 9999999999;
    double accuracy = -9999;
    double correctCount = 0;
    for (int i = 0; i < 100; i++)
    {
        temp.clear();
        temp.push_back(i);
        double nearest_neighbor_distance = 99999999;
        int nearest_neighbor_location = 99999999;
        double nearest_neighbor_label = -99999;
        for (int m = 0; m < 7; m++)
        {
            for (int k = 0; k < 100; k++)
            {
                distance = 0;
                if (KNN(temp, k))
                {
                    for (int j = 1; j < 12; j++)
                    {
                        distance = distance + (pow((data[i][j] - data[k][j]),2));
                    }
                    distance = sqrt(distance);
                    if (distance < nearest_neighbor_distance)
                    {
                        nearest_neighbor_distance = distance;
                        nearest_neighbor_location = k;
                        nearest_neighbor_label = data[k][0];
                        temp.push_back(k);
                    }
                }
            }
            nearest_neighbor_label = countLabels(temp);
        }
            if (nearest_neighbor_label == data[i][0])
            {
                correctCount++;
            }
    }
    accuracy = correctCount / 100.0;
    // cout << endl << endl;
    // for (int i = 0; i < 100; i++) 
    // {
    //     for(int k = 0; k < 11; k++)
    //     {
    //         cout << "Temp = " << data[i][k] << " ";
    //     }
    //     cout << endl;
    // }
    return accuracy;
}

double Classifier::largeTest(string file, vector<int> currentSet, int featureToAdd) // Classifier Test Part
{
    currentSet.push_back(featureToAdd);
    makeSet(currentSet, 1000, 41, file);
    vector<int> temp;
    double distance = 9999999999;
    double accuracy = -9999;
    double correctCount = 0;
    for (int i = 0; i < 1000; i++)
    {
        temp.clear();
        temp.push_back(i);
        double nearest_neighbor_distance = 99999999;
        int nearest_neighbor_location = 99999999;
        double nearest_neighbor_label = -99999;
        for (int m = 0; m < 3; m++)
        {
            for (int k = 0; k < 1000; k++)
            {
                distance = 0;
                if (KNN(temp, k))
                {
                    for (int j = 1; j < 42; j++)
                    {
                        distance = distance + (pow((largeData[i][j] - largeData[k][j]),2));
                    }
                    distance = sqrt(distance);
                    if (distance < nearest_neighbor_distance)
                    {
                        nearest_neighbor_distance = distance;
                        nearest_neighbor_location = k;
                        nearest_neighbor_label = largeData[k][0];
                        temp.push_back(k);
                    }
                }
            }
            nearest_neighbor_label = countLabels(temp);
        }
            if (nearest_neighbor_label == data[i][0])
            {
                correctCount++;
            }
    }
    accuracy = correctCount / 1000.0;
    return accuracy;
}