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
    turnaround_times[0] = processes[0].burst_time;
    response_times[0] = processes[0].burst_time;

    // Calculate completion, waiting, turnaround, and response times for the rest of the processes
    for (int i = 1; i < n; i++)
    {
        // Sort processes based on burst time among those that have arrived
        sort(processes.begin() + i, processes.end(), compare_burst_time);

        int j = i - 1;

        // Calculate completion time of the current process
        while (j >= 0 && processes[j].arrival_time + processes[j].burst_time > processes[i].arrival_time)
        {
            j--;
        }
        completion_times[i] = max(processes[i].arrival_time, completion_times[j] + processes[j].burst_time) + processes[i].burst_time;

        // Calculate waiting time, turnaround time, and response time of the current process
        waiting_times[i] = completion_times[i] - processes[i].arrival_time - processes[i].burst_time;
        turnaround_times[i] = completion_times[i] - processes[i].arrival_time;
        response_times[i] = completion_times[i - 1] < processes[i].arrival_time ? processes[i].burst_time : completion_times[i - 1] - processes[i].arrival_time;

    }

    // Calculate average waiting time, turnaround time, and response time
    double avg_waiting_time = 0;
    double avg_turnaround_time = 0;
    double avg_response_time = 0;
    for (int i = 0; i < n; i++)
    {
        avg_waiting_time += waiting_times[i];
        avg_turnaround_time += turnaround_times[i];
        avg_response_time += response_times[i];
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    avg_response_time /= n;

    // Calculate CPU utilization
    int total_cpu_time = 0;
    for (int i = 0; i < n; i++)
    {
        total_cpu_time += processes[i].burst_time;
    }
    double cpu_utilization = (double)total_cpu_time / completion_times[n - 1];

    // Print the Gantt chart
cout << "Gantt chart:" << endl;
int current_time = processes[0].arrival_time;
for (int i = 0; i < n; i++)
{
    cout << "| P" << processes[i].id << " ";
    current_time = completion_times[i];
}
cout << "|" << endl;
cout << "0";
for (int i = 0; i < n; i++)
{
    cout << "      " << completion_times[i];
}
cout << endl;
// Calculate CPU utilization
int total_burst_time = 0;
for (int i = 0; i < n; i++)
{
    total_burst_time += processes[i].burst_time;
}
double cpu_utilization = (double)total_burst_time / (double)completion_times[n - 1];

// Print CPU utilization
cout << endl << "CPU utilization: " << cpu_utilization * 100 << "%" << endl;
// Print the completion, waiting, turnaround, and response times of each process
cout << endl;
cout << "Process\t\tCompletion Time\tWaiting Time\tTurnaround Time\tResponse Time" << endl;
for (int i = 0; i < n; i++)
{
    cout << "P" << processes[i].id << "\t\t" << completion_times[i] << "\t\t" << waiting_times[i] << "\t\t" << turnaround_times[i] << "\t\t" << response_times[i] << endl;
}

// Print the average waiting time, turnaround time, response time, and CPU utilization
cout << endl;
cout << "Average waiting time: " << avg_waiting_time << endl;
cout << "Average turnaround time: " << avg_turnaround_time << endl;
cout << "Average response time: " << avg_response_time << endl;
cout << "CPU utilization: " << cpu_utilization << endl;

return 0;