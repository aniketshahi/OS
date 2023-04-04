#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

bool compareArrivalTime(const Process &a, const Process &b) {
    return a.arrival_time < b.arrival_time;
}

bool comparePriority(const Process &a, const Process &b) {
    return a.priority < b.priority;
}

int main() {
    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        std::cout << "Enter arrival time, burst time, and priority for process " << i + 1 << ": ";
        std::cin >> processes[i].arrival_time >> processes[i].burst_time >> processes[i].priority;
    }

    std::sort(processes.begin(), processes.end(), compareArrivalTime);
    int current_time = processes[0].arrival_time;

    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_burst_time = 0;

    std::cout << std::left << std::setw(5) << "P#" << std::setw(15) << "Arrival Time" << std::setw(15)
              << "Burst Time" << std::setw(15) << "Priority" << std::setw(15) << "Completion Time"
              << std::setw(15) << "Turnaround Time" << "Waiting Time" << std::endl;

    while (!processes.empty()) {
        std::vector<Process> ready_queue;
        for (const auto &p : processes) {
            if (p.arrival_time <= current_time) {
                ready_queue.push_back(p);
            } else {
                break;
            }
        }

        if (!ready_queue.empty()) {
            std::sort(ready_queue.begin(), ready_queue.end(), comparePriority);
            Process &selected_process = ready_queue.front();
            selected_process.completion_time = current_time + selected_process.burst_time;
            selected_process.turnaround_time = selected_process.completion_time - selected_process.arrival_time;
            selected_process.waiting_time = selected_process.turnaround_time - selected_process.burst_time;
            current_time = selected_process.completion_time;

            total_turnaround_time += selected_process.turnaround_time;
            total_waiting_time += selected_process.waiting_time;
            total_burst_time += selected_process.burst_time;

            processes.erase(std::remove_if(processes.begin(), processes.end(),
                                           [&](const Process &p) { return p.id == selected_process.id; }),
                            processes.end());
            std::cout << "P" << std::left << std::setw(4) << selected_process.id << std::setw(15)
                      << selected_process.arrival_time << std::setw(15) << selected_process.burst_time << std::setw(15)
                      << selected_process.priority << std::setw(15) << selected_process.completion_time
                      << std::setw(15) << selected_process.turnaround_time << selected_process.waiting_time
                      << std::endl;
        } else {
            current_time++;
        }
    }

    double cpu_utilization = (static_cast<double>(total_burst_time) / current_time) * 100.0;
    double throughput = static_cast<double>(n) / total_turnaround_time;

    std::cout << "CPU Utilization: " << cpu_utilization << "%" << std::endl;
    std::cout << "Throughput: " << throughput << " processes/unit time" << std::endl;

    return 0;
}