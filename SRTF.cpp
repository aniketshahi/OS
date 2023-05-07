#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    int pid;       // process id
    int arrival;   // arrival time
    int burst;     // burst time
    int remaining; // remaining time
    int waiting;   // waiting time
    int turnaround;// turnaround time
};

bool operator<(const Process& p1, const Process& p2) {
    return p1.remaining > p2.remaining; // sort by remaining time
}

void SRTF(vector<Process>& processes) {
    int n = processes.size();
    int current_time = 0;
    int total_waiting = 0;
    int total_turnaround = 0;
    priority_queue<Process> ready_queue;

    // sort processes by arrival time
    sort(processes.begin(), processes.end(),
         [](const Process& p1, const Process& p2) {
             return p1.arrival < p2.arrival;
         });

    // process the processes
    while (!ready_queue.empty() || !processes.empty()) {
        // add arriving processes to the ready queue
        while (!processes.empty() && processes.back().arrival <= current_time) {
            ready_queue.push(processes.back());
            processes.pop_back();
        }

        // pick the shortest remaining time process from the ready queue
        if (!ready_queue.empty()) {
            Process p = ready_queue.top();
            ready_queue.pop();

            // update waiting and turnaround times
            p.waiting = current_time - p.arrival;
            p.turnaround = p.waiting + p.burst;
            total_waiting += p.waiting;
            total_turnaround += p.turnaround;

            // execute the process for one unit of time
            p.remaining--;
            current_time++;

            // add the process back to the ready queue if it's not finished
            if (p.remaining > 0) {
                ready_queue.push(p);
            }
        }
        else {
            // no processes are ready, wait for the next one to arrive
            current_time = processes.back().arrival;
        }
    }

    // print the results
    double cpu_utilization = (double)(current_time - processes.front().arrival) / current_time * 100;
    double avg_waiting = (double)total_waiting / n;
    double avg_turnaround = (double)total_turnaround / n;
    cout << "CPU utilization: " << cpu_utilization << "%" << endl;
    cout << "Average waiting time: " << avg_waiting << endl;
    cout << "Average turnaround time: " << avg_turnaround << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;
    for (int i = 0; i < n; i++) {
        Process p;
        cout << "Enter arrival time and burst time for process " << i+1 << ": ";
        cin >> p.arrival >> p.burst;
        p.pid = i+1;
        p.remaining = p.burst;
        processes.push_back(p);
    }

    SRTF(processes);
    return 0;
}