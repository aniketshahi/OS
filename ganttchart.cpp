#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Define a struct to hold the process details
struct Process
{
    string name;
    int start_time;
    int end_time;
    int completion_time;
};

int main()
{
    // Define the processes
    vector<Process> processes = {
        {"Process A", 0, 4, 0},
        {"Process B", 1, 3, 0},
        {"Process C", 2, 5, 0},
        {"Process D", 4, 6, 0},
        {"Process E", 5, 7, 0},
    };

    // Calculate the duration and completion time of each process and determine the maximum completion time
    int max_completion_time = 0;
    for (auto &process : processes)
    {
        process.completion_time = process.end_time;
        if (process.completion_time > max_completion_time)
        {
            max_completion_time = process.completion_time;
        }
    }

    // Determine the number of characters needed to represent the maximum completion time
    int completion_time_width = to_string(max_completion_time).size();

    // Print the chart header
    cout << "Gantt Chart: ";

    // Print the processes
    for (const auto &process : processes)
    {
        // Calculate the duration and the number of spaces needed for alignment
        int duration = process.end_time - process.start_time;

        // Print the process name
        cout << process.name << " ";

        // Print the horizontal bar
        cout << string(duration, '-') << " ";

        // Print the completion time
        cout << setw(completion_time_width) << process.completion_time << " ";
    }

    return 0;
}
