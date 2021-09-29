/**
 * This file requires no modification
 * File used to test all functions in all MPQ implementations.
 * Does the MPQ operation on the input data (look at InputFiles/) and outputs to OutputFiles/.
 * Job simulation: The list of jobs after the MPQ operations are printed. This is done for all the MPQ implementation.
 * Time simulation: The running time of each MPQ implementation for a particular input size is printed.
 */

#include "BinaryHeapMPQ.h"
#include "cpu-job.h"
#include "UnsortedMPQ.h"
#include "SortedMPQ.h"
#include <cctype>
#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using namespace std;
using namespace chrono;

/*
 * Function declarations
 */
bool run_sim(string input_file, string output_file);    // Simulation of jobs running on a CPU
bool time_sim(string input_file, string output_file);   // Timing simulation of jobs running on a CPU

char prompt_yes_no();   // Helper prompt

/*
 * Main driver for simulations
 */
int main() {
	char input_yn;

	// Run simulations
	cout << "----------------------------------------" << endl;
	cout << "          CPU Job Simulations" << endl;
	cout << "----------------------------------------" << endl;
    
    // Prompt for additional input files
    char yes_no = 'y';
    while (yes_no != 'n') {
        // Run another simulations
        if (yes_no == 'y') {
            // Prompt for simulation type
            int option = 0;
            while (option < 1 || option > 2) {
                cout << endl;
                cout << "\t1. Job simulation" << endl;
                cout << "\t2. Timing simulation" << endl;
                cout << "Enter option: ";
                if(!(cin >> option)){
                    cout << "Invalid option" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else if (option < 1 || option > 2 || cin.fail()) {
                    cout << "Invalid option" << endl;
                    cin.clear();
                  }
            }

            // Get filenames    
            string input_file;
            string output_file;
            cout << endl;
            cout << "Enter name of input file: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> input_file;
            cout << "Enter name of output file: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> output_file;
            cout << endl;
            
            // Run simulation
            if (option == 1) {
                cout << "Running simulation with " << input_file << endl;
                if (run_sim(input_file, output_file)) {
                	cout << "  Saving results to " << output_file << endl;
                }
            }

            // Run timing simulation
            if (option == 2) {
                cout << "Running timing simulation on " << input_file << endl;
                if (time_sim(input_file, output_file)) {
                	cout << "  Saving results to " << output_file << endl;
                }
            }
            
            // Prompt for yes or no
            do {
                cout << endl;
                cout << "Would you like to run on an additional input file? [y/n] ";
                cin >> yes_no;
                yes_no = tolower(yes_no);
                if ((yes_no != 'y' && yes_no != 'n') || cin.fail()) {
                    cout << "Invalid option" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (yes_no != 'y' && yes_no != 'n');
        }
    }

    return 0;
}

/*
 * Runs a simulation of jobs on a CPU
 *   input_file is name of file containing jobs
 *   output_file is name of file to write out the results
 */
bool run_sim(string input_file, string output_file) {
    // Attempt to open input file
    ifstream ifs("InputFiles/"+input_file);
    if (!ifs.is_open()) {
        cout << "Error opening: " << input_file << endl;
        return false;
    }

    // Attempt to open output file
    ofstream ofs("OutputFiles/"+output_file);
    if (!ofs.is_open()) {
        cout << "Error opening: " << output_file << endl;
        return false;
    }

    // Create MPQs for simulation
    UnsortedMPQ<CPU_Job> v_mpq;
    SortedMPQ<CPU_Job> ll_mpq;
    BinaryHeapMPQ<CPU_Job> bh_mpq;
    
    // Read jobs from input file and place in each MPQ
    int num_jobs = 0;
    CPU_Job temp;
    while (ifs >> temp) {
        v_mpq.insert(temp);
        ll_mpq.insert(temp);
        bh_mpq.insert(temp);
        num_jobs++;
    }

    // Time slice of cpu
    int time_slice = 0;

    // Run simulation for vector MPQ
    ofs << "Running simulation for UnsortedMPQ with " << num_jobs << " jobs" << endl;
    CPU_Job* current_job = nullptr;
    while (true) {
        time_slice++;
        // No jobs left to process
        if (v_mpq.is_empty()) {
            break;
        }

        // Process current job
        int time = v_mpq.min().length;
        ofs << v_mpq.min() << endl;       

        // The job is finished, if so remove from queue
        v_mpq.remove_min();
    }
    // Simulation finished
    ofs << "No more jobs to run" << endl << endl;

    // Run simulation for linked list MPQ
    time_slice = 0;
    ofs << "Running simulation for SortedMPQ with " << num_jobs << " jobs" << endl;
    current_job = nullptr;
    while (true) {
        time_slice++;
        // No jobs left to process
        if (ll_mpq.is_empty()) {
            break;
        }
        
        // Process current job
        int time = ll_mpq.min().length;
        ofs << ll_mpq.min() << endl;       

        // The job is finished, if so remove from queue
        ll_mpq.remove_min();
    }
    // Simulation finished
    ofs << "No more jobs to run" << endl << endl;

    // Run simulation for binary heap MPQ
    time_slice = 0;
    ofs << "Running simulation for BinaryHeapMPQ with " << num_jobs << " jobs" << endl;
    current_job = nullptr;
    while (true) {
        time_slice++;
        // No jobs left to process
        if (bh_mpq.is_empty()) {
            break;
        }
        
        // Process current job
        int time = bh_mpq.min().length;
        ofs << bh_mpq.min() << endl;       

        // The job is finished, if so remove from queue
        bh_mpq.remove_min();
    }
    // Simulation finished
    ofs << "No more jobs to run" << endl << endl;
    return true;
}

/*
 * Timing simulation for MPQs
 *   input_file is name of jobs file
 *   output_file is name of file to write timings to
 */
bool time_sim(string input_file, string output_file) {
    // Attempt to open input file
    ifstream ifs("InputFiles/"+input_file);
    if (!ifs.is_open()) {
        cout << "Error opening: " << input_file << endl;
        return false;
    }

    // Attempt to open output file
    ofstream ofs("OutputFiles/"+output_file);
    if (!ofs.is_open()) {
        cout << "Error opening: " << output_file << endl;
        return false;
    }

    // Create MPQs
    UnsortedMPQ<CPU_Job> v_mpq;
    SortedMPQ<CPU_Job> ll_mpq;
    BinaryHeapMPQ<CPU_Job> bh_mpq;
    
    // Read jobs from file and store in vector to later load into MPQs
    int num_jobs = 0;
    CPU_Job temp;
    vector<CPU_Job> jobs;
    while (ifs >> temp) {
        jobs.push_back(temp);
        num_jobs++;
    }

    steady_clock::time_point t1;
    steady_clock::time_point t2;
    duration<double> time_span;

    // Timing simulation for vector MPQ
    ofs << "Timing simulation for UnsortedMPQ with " << num_jobs << " jobs" << endl;
    
    // Start the timer for vector MPQ
    t1 = steady_clock::now();
    
    // Insert jobs into MPQ 
    for (auto x : jobs) {
        v_mpq.insert(x);
    }

    // Run the jobs
    int time_slice = 0;
    CPU_Job* current_job = nullptr;
    while (true) {
        time_slice++;
        // No jobs left to process
        if (v_mpq.is_empty()) {
            break;
        }
        
        // Process current job
        int time = v_mpq.min().length;
        while(time != 0){
            time--;
        }        

        // The job is finished, if so remove from queue
        v_mpq.remove_min();
    }

    // End the timer for vector MPQ
    t2 = steady_clock::now();
    
    // Calculate time for simulation and write to file
    time_span = duration_cast<duration<double>>(t2 - t1);
    ofs << "Timing: " << time_span.count() * 1000 << " millisec" << endl << endl;

    // Timing simulation for linked list MPQ
    ofs << "Timing simulation for SortedMPQ with " << num_jobs << " jobs" << endl;
    
    // Start the timer for linked list MPQ
    t1 = steady_clock::now();

    // Insert jobs into MPQ 
    for (auto x : jobs) {
        ll_mpq.insert(x);
    }

    // Run the jobs
    time_slice = 0;
    current_job = nullptr;
    while (true) {
        time_slice++;
        // No jobs left to process
        if (ll_mpq.is_empty()) {
            break;
        }
        
        // Process current job
        int time = ll_mpq.min().length;
        while(time != 0){
            time--;
        }        

        // The job is finished, if so remove from queue
        ll_mpq.remove_min();
    }

    // End the timer for linked list MPQ
    t2 = steady_clock::now();

    // Calculate time for simulation and write to file
    time_span = duration_cast<duration<double>>(t2 - t1);
    ofs << "Timing: " << time_span.count() * 1000 << " millisec" << endl << endl;

    // Timing simulation for binary heap MPQ
    ofs << "Timing simulation for BinaryHeapMPQ with " << num_jobs << " jobs" << endl;
    
    // Start the timer for binary heap MPQ
    t1 = steady_clock::now();

    // Insert jobs into MPQ 
    for (auto x : jobs) {
        bh_mpq.insert(x);
    }

    // Run the jobs
    time_slice = 0;
    current_job = nullptr;
    while (true) {
        time_slice++;
        // No jobs left to process
        if (bh_mpq.is_empty()) {
            break;
        }
        
        // Process current job
        int time = bh_mpq.min().length;
        while(time != 0){
            time--;
        }        

        // The job is finished, if so remove from queue
        bh_mpq.remove_min();
    }

    // End the timer for binary heap MPQ
    t2 = steady_clock::now();
    
    // Calculate time for simulation and write to file
    time_span = duration_cast<duration<double>>(t2 - t1);
    ofs << "Timing: " << time_span.count() * 1000 << " millisec" << endl << endl;
    return true;
}

/*
 * Prompts user for yes or no and returns choice Y or N
 */
char prompt_yes_no() {
    char decision;
    while (true) {
        cout << "[y/n]: ";
        cin >> decision;
        switch(decision) {
            case 'y':
            case 'Y':
            case 'n':
            case 'N':
                return tolower(decision);
                break;
            default:
                cout << "Invalid option" << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
    }
}