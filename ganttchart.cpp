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
        {"Process A", 0, 4},
        {"Process B", 1, 3},
        {"Process C", 2, 5},
        {"Process D", 4, 6},
        {"Process E", 5, 7},
    };

    // Calculate the duration and completion time of each process and determine the maximum completion time
    int max_completion_time = 0;
    for (auto &process : processes)
    {
        process.completion_time = process.end_time;
        for (const auto &other_process : processes)
        {
            if (other_process.start_time >= process.end_time && other_process.completion_time < process.completion_time)
            {
                process.completion_time = other_process.completion_time;
            }
        }
        if (process.completion_time > max_completion_time)
        {
            max_completion_time = process.completion_time;
        }
    }

    // Determine the number of characters needed to represent the maximum completion time
    int completion_time_width = to_string(max_completion_time).size();

    // Print the chart header
    cout << "                    Gantt Chart" << endl;
    cout << "---------------------------------------------------------------" << endl;

    // Print the processes
    for (const auto &process : processes)
    {
        // Calculate the duration and the number of spaces needed for alignment
        int duration = process.end_time - process.start_time;
        string spaces;
        spaces.reserve(process.start_time * (completion_time_width + 1));
        for (int i = 0; i < process.start_time * (completion_time_width + 1); i++)
        {
            spaces += " ";
        }

        // Print the process name and the necessary number of spaces
        cout << "| " << setw(process.name.size() + process.start_time * (completion_time_width + 1)) << process.name << " ";

        // Print the horizontal bar
        cout << string(duration, '-') << " ";

        // Print the completion time
        cout << setw(completion_time_width) << process.completion_time << "|" << endl;
    }

    // Print the chart footer
    cout << "---------------------------------------------------------------" << endl;

    return 0;
}