#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Define a struct to hold the process details
struct Process {
    string name;
    int start_time;
    int end_time;
};

int main() {
    // Define the processes
    vector<Process> processes = {
        {"Process A", 0, 4},
        {"Process B", 1, 3},
        {"Process C", 2, 5},
        {"Process D", 4, 6},
        {"Process E", 5, 7},
    };

    // Calculate the duration of each process and determine the maximum duration
    int max_duration = 0;
    for (const auto& process : processes) {
        int duration = process.end_time - process.start_time;
        if (duration > max_duration) {
            max_duration = duration;
        }
    }

    // Determine the number of characters needed to represent the maximum duration
    int duration_width = to_string(max_duration).size();

    // Print the chart header
    cout << "                    Gantt Chart" << endl;
    cout << "---------------------------------------------------" << endl;

    // Print the processes
    for (const auto& process : processes) {
        // Calculate the duration and the number of spaces needed for alignment
        int duration = process.end_time - process.start_time;
        string spaces;
        for (int i = 0; i < process.start_time * (duration_width + 1); i++) {
            spaces += " ";
        }

        // Print the process name and the necessary number of spaces
        cout << "| " << process.name << spaces;

        // Print the horizontal bar
        cout << string(duration, '-') << " ";

        // Print the remaining spaces
        for (int i = 0; i < (max_duration - duration) * (duration_width + 1); i++) {
            cout << " ";
        }
        cout << "|" << endl;
    }

    // Print the chart footer
    cout << "---------------------------------------------------" << endl;

    return 0;
}