#include <iostream>
#include <algorithm>

using namespace std;

struct Process {
    int pid; // process id
    int at;  // arrival time
    int bt;  // burst time
};

bool compareAT(const Process& p1, const Process& p2) {
    return p1.at < p2.at;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process* processes = new Process[n];
    cout << "Enter process details (Pid, AT, BT) one by one:\n";
    for (int i = 0; i < n; ++i) {
        cin >> processes[i].pid >> processes[i].at >> processes[i].bt;
    }

    sort(processes, processes + n, compareAT);

    int clock = 0;
    double tsum = 0, wsum = 0;
    cout << "Pid \t AT \t BT \t CT \t TAT \t WT\n";
    for (int i = 0; i < n; ++i) {
        clock = max(clock, processes[i].at);
        int ct = clock + processes[i].bt;
        int tat = ct - processes[i].at;
        int wt = tat - processes[i].bt;
        tsum += tat;
        wsum += wt;
        cout << processes[i].pid << "\t" << processes[i].at << "\t" << processes[i].bt << "\t" << ct << "\t" << tat << "\t" << wt << endl;
        clock = ct;
    }

    double tavg = tsum / n;
    double wavg = wsum / n;
    cout << "Tsum = " << tsum << " \t WT sum = " << wsum << endl;
    cout << "Tavg = " << tavg << " \t WT avg = " << wavg << endl;

    delete[] processes;

    return 0;
}
