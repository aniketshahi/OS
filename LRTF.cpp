#include <iostream>
#include <algorithm>
#include <iomanip>
#include <climits>
using namespace std;

struct Process {
    int pid;
    int at;
    int bt;
    int ct, wt, tat, rt, start_time;
};

int main() {
    int n;
    float bt_remaining[100];
    bool is_completed[100] = {false};
    int current_time = 0;
    int completed = 0;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0, total_idle_time = 0;
    float length_cycle, prev = 0;
    float cpu_utilization;
    int max_completion_time = INT_MIN, min_arrival_time = INT_MAX;

    cout << fixed << setprecision(2);

    cout << "Enter total number of processes: ";
    cin >> n;

    Process ps[n];

    for (int i = 0; i < n; i++) {
        cout << "\nEnter Process " << i << " Arrival Time: ";
        cin >> ps[i].at;
        ps[i].pid = i;
    }

    for (int i = 0; i < n; i++) {
        cout << "\nEnter Process " << i << " Burst Time: ";
        cin >> ps[i].bt;
        bt_remaining[i] = ps[i].bt;
    }

    while (completed != n) {
        int max_index = -1;
        int maximum = INT_MIN;
        
        for (int i = 0; i < n; i++) {
            if (ps[i].at <= current_time && !is_completed[i]) {
                if (bt_remaining[i] > maximum || (bt_remaining[i] == maximum && ps[i].at < ps[max_index].at)) {
                    maximum = bt_remaining[i];
                    max_index = i;
                }
            }
        }

        if (max_index == -1)
            current_time++;
        else {
            if (bt_remaining[max_index] == ps[max_index].bt) {
                ps[max_index].start_time = current_time;
                total_idle_time += (ps[max_index].start_time - prev);
            }

            bt_remaining[max_index] -= 1;
            current_time++;
            prev = current_time;

            if (bt_remaining[max_index] == 0) {
                ps[max_index].ct = current_time;
                ps[max_index].tat = ps[max_index].ct - ps[max_index].at;
                ps[max_index].wt = ps[max_index].tat - ps[max_index].bt;
                ps[max_index].rt = ps[max_index].start_time - ps[max_index].at;

                sum_tat += ps[max_index].tat;
                sum_wt += ps[max_index].wt;
                sum_rt += ps[max_index].rt;
                completed++;
                is_completed[max_index] = true;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        max_completion_time = max(max_completion_time, ps[i].ct);
        min_arrival_time = min(min_arrival_time, ps[i].at);
    }

    length_cycle = max_completion_time - min_arrival_time;

    cout << "\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++)
        cout << i << "\t\t" << ps[i].at << "\t" << ps[i].bt << "\t\t" << ps[i].ct << "\t" << ps[i].tat << "\t" << ps[i].wt << "\t" << ps[i].rt << endl;
    cout << endl;

    cpu_utilization = (length_cycle - total_idle_time) / length_cycle;

    cout << "\nAverage Turn Around time= " << sum_tat / n;
    cout << "\nAverage Waiting Time= " << sum_wt / n;
    cout << "\nAverage Response Time= " << sum_rt / n;
    cout << "\nThroughput= " << (n / length_cycle) * 100 << " %";
    cout << "\nCPU Utilization(Percentage)= " << cpu_utilization * 100;
    return 0;
}
