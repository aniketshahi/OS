#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
};

bool compare_arrival(Process p1, Process p2) {
    return p1.arrival_time < p2.arrival_time;
}

bool compare_remaining(Process p1, Process p2) {
    return p1.remaining_time > p2.remaining_time;
}

int main() {
    int n; // number of processes
    vector<Process> processes;

    cout << "Enter the number of processes: ";
    cin >> n;

    // Input process details
    for (int i = 0; i < n; i++) {
        Process p;
        p.pid = i + 1;
        cout << "Enter arrival time of process " << p.pid << ": ";
        cin >> p.arrival_time;
        cout << "Enter burst time of process " << p.pid << ": ";
        cin >> p.burst_time;
        p.remaining_time = p.burst_time;
        processes.push_back(p);
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), compare_arrival);

    vector<int> completion_time(n);
    vector<int> turnaround_time(n);
    vector<int> waiting_time(n);

    int current_time = 0;
    int completed_processes = 0;
    int cpu_utilization = 0;

    cout << endl << "Scheduling table:" << endl;
    cout << "PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;

    while (completed_processes < n) {
        // Find process with longest remaining time
        int index = -1;
        int longest_remaining_time = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > longest_remaining_time) {
                longest_remaining_time = processes[i].remaining_time;
                index = i;
            }
        }

        if (index == -1) {
            // No process is available at current time, wait for the next process
            current_time++;
        } else {
            // Execute the process with longest remaining time
            int current_burst_time = processes[index].remaining_time;
            cpu_utilization += current_burst_time;
            current_time += current_burst_time;
            processes[index].remaining_time = 0;
            completed_processes++;

            // Update completion time, turnaround time, and waiting time
            completion_time[index] = current_time;
            turnaround_time[index] = completion_time[index] - processes[index].arrival_time;
            waiting_time[index] = turnaround_time[index] - processes[index].burst_time;

            // Print process details in scheduling table
            cout << processes[index].pid << "\t" << processes[index].arrival_time << "\t\t" << processes[index].burst_time << "\t\t"
                << completion_time[index] << "\t\t" << turnaround_time[index] << "\t\t" << waiting_time[index] << endl;
        }
    }

    // Calculate throughput and CPU utilization
    double throughput = (double) n / current_time * 100;
    double avg_cpu_utilization = (double) cpu_utilization / current_time * 100;

    // Print throughput and CPU utilization
    cout << endl << "Throughput: " << fixed << setprecision(2) << throughput << "%" << endl;
    cout << "CPU Utilization: " << fixed << setprecision(2) << avg_cpu_utilization << "%" << endl;

    return 0;
}