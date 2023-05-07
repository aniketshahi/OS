#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
};

bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrival_time < b.arrival_time;
}

bool compareBurstTime(const Process& a, const Process& b) {
    return a.burst_time < b.burst_time;
}

void calculateCompletionTime(vector<Process>& processes) {
    int n = processes.size();
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].completion_time = current_time + processes[i].burst_time;
        current_time = processes[i].completion_time;
    }
}

void calculateTurnAroundTime(vector<Process>& processes) {
    int n = processes.size();
    for (int i = 0; i < n; i++) {
        processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;
    }
}

void calculateWaitingTime(vector<Process>& processes) {
    int n = processes.size();
    for (int i = 0; i < n; i++) {
        processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;
    }
}

void printTable(const vector<Process>& processes) {
    int n = processes.size();
    cout << "PID\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].pid << "\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t"
            << processes[i].completion_time << "\t\t" << processes[i].turn_around_time << "\t\t\t"
            << processes[i].waiting_time << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].pid = i + 1;
    }

    sort(processes.begin(), processes.end(), compareArrivalTime);

    vector<Process> ready_queue;
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].completion_time == 0) {
                ready_queue.push_back(processes[i]);
            }
        }

        if (!ready_queue.empty()) {
            sort(ready_queue.begin(), ready_queue.end(), compareBurstTime);
            Process next_process = ready_queue.front();
            ready_queue.erase(ready_queue.begin());

            next_process.completion_time = current_time + next_process.burst_time;
            current_time = next_process.completion_time;

            completed_processes++;
            processes[next_process.pid - 1] = next_process;
        } else {
            current_time++;
        }
    }

    calculateCompletionTime(processes);
    calculateTurnAroundTime(processes);
    calculateWaitingTime(processes);
    printTable(processes);

    return 0;
}