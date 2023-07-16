#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Process
{
public:
    int Pid;
    int AT;
    int BT;
    int CT;
    int WT;
    int TAT;
    int THPT;
    int CPU;

    Process(int pid, int at, int bt)
        : Pid(pid), AT(at), BT(bt), CT(0), WT(0), TAT(0), THPT(0), CPU(0)
    {
    }
};

bool compare_AT(const Process &p1, const Process &p2)
{
    return p1.AT < p2.AT;
}

void print_table(const vector<Process> &processes, float avg_WT, float avg_TAT, float THPT)
{
    cout << "Pid\tAT\tBT\tCT\tTAT\tWT " << endl;
    for (const Process &process : processes)
    {
        cout << process.Pid << "\t" << process.AT << "\t" << process.BT << "\t" << process.CT << "\t" << process.TAT << "\t" << process.WT << endl;
    }
    cout << "Average WT is: " << avg_WT << endl;
    cout << "Average TAT is: " << avg_TAT << endl;
    cout << "Throughput is: " << THPT << endl;
}

void fcfs_scheduling(vector<Process> &processes)
{
    int current_time = 0;
    float total_WT = 0, total_TAT = 0;
    for (Process &process : processes)
    {
        if (current_time < process.AT)
        {
            current_time = process.AT;
        }
        current_time += process.BT;
        process.CT = current_time;
        process.TAT = process.CT - process.AT;
        process.WT = process.TAT - process.BT;
        total_WT += process.WT;
        total_TAT += process.TAT;
    }
    float avg_WT = total_WT / processes.size();
    float avg_TAT = total_TAT / processes.size();
    float THPT = static_cast<float>(processes.size()) / current_time;

    print_table(processes, avg_WT, avg_TAT, THPT);
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;
    for (int i = 0; i < n; i++)
    {
        int pid, at, bt;
        pid = i + 1;
        cout << "Enter the AT of process " << pid << ": ";
        cin >> at;
        cout << "Enter the BT of process " << pid << ": ";
        cin >> bt;
        processes.push_back(Process(pid, at, bt));
    }

    sort(processes.begin(), processes.end(), compare_AT);

    fcfs_scheduling(processes);

    return 0;
}
