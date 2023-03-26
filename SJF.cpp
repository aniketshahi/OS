#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
};

bool compare_arrival_time(Process a, Process b)
{
    return a.arrival_time < b.arrival_time;
}

bool compare_burst_time(Process a, Process b)
{
    return a.burst_time < b.burst_time;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Enter the process ID, arrival time, and burst time for process " << i + 1 << ": ";
        cin >> processes[i].id >> processes[i].arrival_time >> processes[i].burst_time;
    }

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), compare_arrival_time);

    vector<int> completion_times(n);
    vector<int> waiting_times(n);
    vector<int> turnaround_times(n);
    vector<int> response_times(n);

    // Initialize the first process
    completion_times[0] = processes[0].arrival_time + processes[0].burst_time;
    waiting_times[0] = 0;
    turnaround_times[0] = completion_times[0] - processes[0].arrival_time;
    response_times[0] = processes[0].burst_time;

    // Calculate completion, waiting, and turnaround times for each process
    for (int i = 1; i < n; i++)
    {
        int previous_completion_time = completion_times[i - 1];
        int current_arrival_time = processes[i].arrival_time;
        int current_burst_time = processes[i].burst_time;

        // If the process arrives after the previous process completes, its completion time is its arrival time plus its burst time
        if (current_arrival_time > previous_completion_time)
        {
            completion_times[i] = current_arrival_time + current_burst_time;
        }
        // Otherwise, its completion time is the previous completion time plus its burst time
        else
        {
            completion_times[i] = previous_completion_time + current_burst_time;
        }

        // Calculate waiting time, turnaround time, and response time for the process
        waiting_times[i] = completion_times[i - 1] - processes[i].arrival_time;
        turnaround_times[i] = completion_times[i] - processes[i].arrival_time;
        response_times[i] = waiting_times[i] + processes[i].burst_time;
    }

    // Calculate the average waiting time, turnaround time, and response time
    double total_waiting_time = 0;
    double total_turnaround_time = 0;
    double total_response_time = 0;

    for (int i = 0; i < n; i++)
    {
        total_waiting_time += waiting_times[i];
        total_turnaround_time += turnaround_times[i];
        total_response_time += response_times[i];
    }

    double average_waiting_time = total_waiting_time / n;
    double average_turnaround_time = total_turnaround_time / n;
    double average_response_time = total_response_time / n;

    // Print the completion, waiting, and turnaround times for each process
    cout << "Process\tCompletion Time\tWaiting Time\tTurnaround Time\tResponse Time\n";

    for (int i = 0; i < n; i++)
    {
        cout << processes[i].id << "\t\t" << completion_times[i] << "\t\t" << waiting_times[i] << "\t\t" << turnaround_times[i] << "\t\t" << response_times[i] << "\n";
    }

    // Print the average waiting time, turnaround time, and response time
    cout << "Average waiting time: " << average_waiting_time << "\n";
    cout << "Average turnaround time: " << average_turnaround_time << "\n";
    cout << "Average response time: " << average_response_time << "\n";

    return 0;
}