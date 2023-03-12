#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    string name;
    int burst_time;
    int remaining_time;
    int arrival_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void round_robin(vector<Process>& processes, int quantum) {
    int n = processes.size();
    deque<int> queue;
    int time = 0;
    int index = 0;

    // Initialize the queue with the first process.
    queue.push_back(0);

    while (!queue.empty()) {
        // Get the next process from the queue.
        index = queue.front();
        queue.pop_front();

        // If the process is completed, update the completion time, 
        // turnaround time, and waiting time.
        if (processes[index].remaining_time <= quantum) {
            time += processes[index].remaining_time;
            processes[index].completion_time = time;
            processes[index].turnaround_time = processes[index].completion_time - processes[index].arrival_time;
            processes[index].waiting_time = processes[index].turnaround_time - processes[index].burst_time;
        }
        // Otherwise, run the process for the time quantum and add it back to the queue.
        else {
            time += quantum;
            processes[index].remaining_time -= quantum;
            queue.push_back(index);
        }

        // Add any newly arrived processes to the queue.
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && 
                find(queue.begin(), queue.end(), i) == queue.end() && 
                processes[i].remaining_time > 0) {
                queue.push_back(i);
            }
        }
    }
}

void print_result(vector<Process>& processes) {
    cout << "Process\tBurst Time\tArrival Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (Process process : processes) {
        cout << process.name << "\t" << process.burst_time << "\t\t" << process.arrival_time << "\t\t";
        cout << process.completion_time << "\t\t" << process.turnaround_time << "\t\t" << process.waiting_time << "\n";
    }
}

int main() {
    int n;
    int quantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);

    // Get the input for each process.
    for (int i = 0; i < n; i++) {
        cout << "Enter the name, burst time, and arrival time of process " << i + 1 << ": ";
        cin >> processes[i].name >> processes[i].burst_time >> processes[i].arrival_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    cout << "Enter the time quantum: ";
    cin >> quantum;

    round_robin(processes, quantum);
    print_result(processes);

    return 0;
}
