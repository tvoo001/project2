#include "algorithm.h"

Algorithm::Algorithm()
{
    localHighestAccuracy = 0;
    globalHighestAccuracy = 0;
    globalFeatures = "";
    accuracy = 0;
    trait = 0;
    listFeatures = "";
    letter = 'o';
}
string Algorithm::numberConvert(int trial)
{
    string temp;
    temp = to_string(trial);
    return temp;
}
double Algorithm::forwardSearch(int i)
{
    features.clear();
    string current;
    globalHighestAccuracy = calculateAccuracy(features);
    cout << "Using no features and leave one out evaluation, I get an accuracy of " << globalHighestAccuracy * 100 << "%" << endl << endl;
    cout << "Beginning search." << endl << endl;

    int temp = 1;
    if (features.empty())
    {
        for (int l = 1; l < i + 1; l++)
        {
            features.push_back(l);
            accuracy = calculateAccuracy(features);
            if (localHighestAccuracy < accuracy)
            {
                localHighestAccuracy = accuracy;
                trait = l;
                current = numberConvert(trait);
                letter = trait;
            }
            cout << "Using feature(s) {" << temp << "} "<< "accuracy is " << accuracy * 100  << '%' << endl;
            temp++;
            features.pop_back();
        }
        features.push_back(trait);
        listFeatures = current;
        letter = trait;
        if (localHighestAccuracy > globalHighestAccuracy)
        {
            globalFeatures = listFeatures;
            globalHighestAccuracy = localHighestAccuracy;
        }
        cout << endl <<"Feature Set {" << listFeatures << "}, which has an accuracy of " << localHighestAccuracy * 100 << "%" << endl << endl;
    }
    while(features.size() < i)
    {
        temp = 1;
        listFeatures.push_back(',');
        localHighestAccuracy = 0;
        for (int l = 1; l < i + 1; l++)
        {
            if (checkList(temp))
            {  
                features.push_back(l);
                accuracy = calculateAccuracy(features);
                if (localHighestAccuracy < accuracy)
                {
                    localHighestAccuracy = accuracy;
                    trait = l;
                    current = numberConvert(trait);
                }
                cout << "Using feature(s) {" << listFeatures << temp << "} "<< "accuracy is " << accuracy * 100  << '%' << endl;
                features.pop_back();
            }
            temp++;
        }
        features.push_back(trait);
        listFeatures = listFeatures + current;
        if (localHighestAccuracy > globalHighestAccuracy)
        {
            globalFeatures = listFeatures;
            globalHighestAccuracy = localHighestAccuracy;
        }
        cout << endl << "Feature Set {" << listFeatures << "}, which has an accuracy of " << localHighestAccuracy * 100 << "%" << endl << endl;
    }
    cout << "The best feature subset is {" << globalFeatures << "}, which has an accuracy of " << globalHighestAccuracy  * 100 << "%" << endl;
    return accuracy;
}

double Algorithm::backwardSearch(int i)
{
    string placeholder;
    string current;
    int temp = 1;
    for (int m = 1; m <= i; m++)
    {
        string feat = numberConvert(m);
        listFeatures = listFeatures + feat;
        listFeatures = listFeatures + ',';
        globalFeatures = globalFeatures + feat;
        globalFeatures = globalFeatures + ',';
        features.push_back(m);
    }
    listFeatures.pop_back();
    globalFeatures.pop_back();
    globalHighestAccuracy = calculateAccuracy(features);
    cout << "Using all features {" << listFeatures <<"} and leave one out evaluation, I get an accuracy of " << globalHighestAccuracy * 100 << "%" << endl << endl;
    cout << "Beginning search." << endl << endl;
    while(features.size() > 0)
    {
        temp = 1;
        localHighestAccuracy = 0;
        for (int l = 0; l < i; l++)
        {
            if (!checkList(temp))
            {   
                features.erase(features.begin());
                accuracy = calculateAccuracy(features);
                if (localHighestAccuracy < accuracy)
                {
                    localHighestAccuracy = accuracy;
                    current = numberConvert(temp);
                    trait = temp;
                }
                placeholder = removeLetter(temp);
                features.emplace_back(temp);
                cout << "Using feature(s) {" << placeholder << "} "<< "accuracy is " << accuracy  * 100 << '%' << endl;
            }
            temp++;
        }
        listFeatures = removeLetter(trait);
        if (localHighestAccuracy > globalHighestAccuracy)
        {
            globalFeatures = listFeatures;
            globalHighestAccuracy = localHighestAccuracy;
        }
        cout << endl << "Feature Set {" << listFeatures << "}, which has an accuracy of " << localHighestAccuracy * 100<< "%" << endl << endl;
        removeFeature(trait);  
        if (features.size() == 1)
        {
            cout << "Using no features and leave one out evaluation, I get an accuracy of " << calculateAccuracy(features) << "%" << endl << endl;
            cout << "The best feature subset is {" << globalFeatures << "}, which has an accuracy of " << globalHighestAccuracy * 100<< "%" << endl;
        }
    }
    return accuracy;
}

bool Algorithm::checkList(int trial)
{
    bool checker = true;
    for(int i = 0; i < features.size(); i++)
    {
        if(features.at(i) == trial)
        {
            checker = false;
        }
    }
    return checker;
}

string Algorithm::removeLetter(int item)
{
    int place;
    int value;
    string temp = "";
    for(int i = 0; i < features.size(); i++)
    {
        if (features.at(i) == item)
        {
            item = i;
            value = features.at(i);
        }
    }
    for(int i = 0; i < features.size(); i++)
    {
        if (value != features.at(i))
        {
            temp = temp + numberConvert(features.at(i));
            temp = temp + ',';
        }
    }
    temp.pop_back();
    return temp;
}

void Algorithm::removeFeature(int trait)
{
    for (int i = 0; i < features.size(); i++)
    {
        if (features.at(i) == trait)
        {
            features.erase(features.begin() + i);
        }
    }
}

double Algorithm::calculateAccuracy(vector<int> selectedFeatures)
{
    // vector<int> selectedFeature {};
    // for(int i = 0; i < selectedFeatures.size(); i++)
    // {
    //     selectedFeature.push_back(selectedFeatures.at(i));
    // }
    Classifier temp = Classifier(selectedFeatures, 1000, 41, "large-test-dataset-90.txt");
    accuracy = temp.largeTest("large-test-dataset-90.txt", selectedFeatures, 0);
    return accuracy;
}
