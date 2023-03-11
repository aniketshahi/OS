#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

bool compareByArrivalTime(const vector<int>& a, const vector<int>& b) {
    return a[1] < b[1];
}

bool compareByBurstTime(const vector<int>& a, const vector<int>& b) {
    return a[2] < b[2];
}

void sjn(vector<vector<int>>& processes) {
    int n = processes.size();
    int current_time = 0;
    int waiting_time = 0;
    int turnaround_time = 0;
    vector<vector<int>> completed_processes;
    
    sort(processes.begin(), processes.end(), compareByArrivalTime);
    
    while (completed_processes.size() < n) {
        int smallest_burst_time = INT_MAX;
        int smallest_process_index = -1;
        
        for (int i = 0; i < n; i++) {
            if (processes[i][2] < smallest_burst_time && find(completed_processes.begin(), completed_processes.end(), processes[i]) == completed_processes.end() && processes[i][1] <= current_time) {
                smallest_burst_time = processes[i][2];
                smallest_process_index = i;
            }
        }
        
        if (smallest_process_index == -1) {
            current_time++;
        } else {
            vector<int> current_process = processes[smallest_process_index];
            int current_process_start_time = current_time;
            current_time += current_process[2];
            
            waiting_time += current_process_start_time - current_process[1];
            turnaround_time += current_time - current_process[1];
            
            completed_processes.push_back(current_process);
        }
    }
    
    double avg_waiting_time = static_cast<double>(waiting_time) / n;
    double avg_turnaround_time = static_cast<double>(turnaround_time) / n;
    
    cout << "Average waiting time: " << avg_waiting_time << endl;
    cout << "Average turnaround time: " << avg_turnaround_time << endl;
}

int main() {
    int choice, n, id, arrival_time, burst_time;
    vector<vector<int>> processes;
    
    do {
        cout << "Enter your choice:" << endl;
        cout << "1. Add a process" << endl;
        cout << "2. Run SJN algorithm" << endl;
        cout << "3. Exit" << endl;
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter process ID: ";
                cin >> id;
                cout << "Enter arrival time: ";
                cin >> arrival_time;
                cout << "Enter burst time: ";
                cin >> burst_time;
                processes.push_back({id, arrival_time, burst_time});
                break;
            case 2:
                sjn(processes);
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
        
        cout << endl;
    } while (choice != 3);
    
    return 0;
}
