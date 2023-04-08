#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

int main()
{
    int num_processes, quantum_time;
    cout << "Enter the number of processes: ";
    cin >> num_processes;
    cout << "Enter the time quantum: ";
    cin >> quantum_time;

    // Initialize the vector of processes
    vector<Process> processes(num_processes);

    // Take user input for process details
    for (int i = 0; i < num_processes; i++)
    {
        cout << "Enter details for Process " << i + 1 << ":" << endl;
        cout << "Enter arrival time: ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time: ";
        cin >> processes[i].burst_time;
        processes[i].pid = i + 1;
    }

    // Sort the processes by arrival time
    sort(processes.begin(), processes.end(), [](Process a, Process b)
         { return a.arrival_time < b.arrival_time; });

    // Initialize the remaining time for each process to be the burst time
    vector<int> remaining_time(num_processes);
    for (int i = 0; i < num_processes; i++)
    {
        remaining_time[i] = processes[i].burst_time;
    }

    // Initialize the current time and the queue of processes
    int current_time = processes[0].arrival_time;
    vector<int> queue;

    // Perform the round-robin scheduling
    while (true)
    {
        bool done = true;
        for (int i = 0; i < num_processes; i++)
        {
            if (remaining_time[i] > 0 && processes[i].arrival_time <= current_time)
            {
                done = false;
                queue.push_back(i);
            }
        }
        if (done)
        {
            break;
        }
        int next_process = queue[0];
        queue.erase(queue.begin());
        if (remaining_time[next_process] > quantum_time)
        {
            remaining_time[next_process] -= quantum_time;
            current_time += quantum_time;
            queue.push_back(next_process);
        }
        else
        {
            current_time += remaining_time[next_process];
            remaining_time[next_process] = 0;
            processes[next_process].completion_time = current_time;
            processes[next_process].turnaround_time = processes[next_process].completion_time - processes[next_process].arrival_time;
            processes[next_process].waiting_time = processes[next_process].turnaround_time - processes[next_process].burst_time;
            processes[next_process].response_time = processes[next_process].completion_time - processes[next_process].arrival_time - processes[next_process].burst_time;
        }
    }

    // Calculate the average completion time, average turnaround time, throughput, and CPU utilization
    double avg_completion_time = 0;
    double avg_turnaround_time = 0;
    double throughput = (double)num_processes / current_time;
    double cpu_utilization = 0;
    for (int i = 0; i < num_processes; i++)
    {
        avg_completion_time += processes[i].completion_time;
        avg_turnaround_time += processes[i].turnaround_time;
        cpu_utilization += processes[i].burst_time;
    }
    avg_completion_time /= num_processes;
    avg_turnaround_time /= num_processes;
    cpu_utilization /= current_time;

    // Print the results
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time" << endl;
    for (int i = 0; i < num_processes; i++)
    {
        cout << processes[i].pid << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << processes[i].completion_time << "\t\t" << processes[i].turnaround_time << "\t\t" << processes[i].waiting_time << "\t\t" << processes[i].response_time << endl;
    }
    cout << endl;
    cout << "Average Completion Time: " << avg_completion_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
    cout << "Throughput: " << throughput << endl;
    cout << "CPU Utilization: " << cpu_utilization << endl;

    return 0;
}
