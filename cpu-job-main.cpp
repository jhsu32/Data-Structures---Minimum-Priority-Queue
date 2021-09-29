/**
 * Use this main() file to test functions in cpu-job.h
 */
#include "cpu-job.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<CPU_Job> vec; //vector of CPU_Jobs
    string filename = "InputFiles/SetSize10.txt";

    cout << "Reading SetSize10.txt" << endl;
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cout << "Error opening " << filename << endl;
        return 0;
    }
    
    CPU_Job job;
    while (ifs >> job) {
        vec.push_back(job); //pushes one job at a time into vector
    }

    cout << "Outputting jobs" << endl;
    for (auto x : vec) {
        cout << x << endl; //outputs one job at a time from the vector
    }
}