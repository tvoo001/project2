#include <iostream>
#include <string>
#include "algorithm.h"
#include "classifier.h"

using namespace std;

int main ()
{
    Algorithm state;
    // vector<int> selectedFeatures {3,5,7};
    // Classifier temp = Classifier(selectedFeatures, 100, 10, "small-test-dataset.txt");
    // cout << "Accuracay = " << temp.test("small-test-dataset.txt", selectedFeatures, 0) << endl;
    // vector<int> selectedFeatures {1,15,27};
    // Classifier temp = Classifier(selectedFeatures, 1000, 41, "large-test-dataset.txt");
    // cout << "Accuracay = " << temp.largeTest("large-test-dataset.txt", selectedFeatures, 0) << endl;
    // state.forwardSearch(10);
    // state.backwardSearch(10);
    // vector<int> selectedFeatures {6,20,38};
    // Classifier temp = Classifier(selectedFeatures, 1000, 40, "large-test-dataset-90.txt");
    // cout << "Accuracay = " << temp.largeTest("large-test-dataset-90.txt", selectedFeatures, 0) << endl;
    state.forwardSearch(40);
    return 0;
}