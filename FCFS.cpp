#include <iostream>
#include <algorithm>

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

    Process() : Pid(0), AT(0), BT(0), CT(0), WT(0), TAT(0), THPT(0), CPU(0)
    {
    }

    Process(int pid, int at, int bt)
        : Pid(pid), AT(at), BT(bt), CT(0), WT(0), TAT(0), THPT(0), CPU(0)
    {
    }
};

bool compare_AT(const Process &p1, const Process &p2)
{
    return p1.AT < p2.AT;
}

void print_table(Process *processes, int n, float avg_WT, float avg_TAT, float THPT)
{
    cout << "Pid\tAT\tBT\tCT\tTAT\tWT " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].Pid << "\t" << processes[i].AT << "\t" << processes[i].BT << "\t" << processes[i].CT << "\t" << processes[i].TAT << "\t" << processes[i].WT << endl;
    }
    cout << "Average WT is: " << avg_WT << endl;
    cout << "Average TAT is: " << avg_TAT << endl;
    cout << "Throughput is: " << THPT << endl;
}

void fcfs_scheduling(Process *processes, int n)
{
    int current_time = 0;
    float total_WT = 0, total_TAT = 0;
    for (int i = 0; i < n; i++)
    {
        if (current_time < processes[i].AT)
        {
            current_time = processes[i].AT;
        }
        current_time += processes[i].BT;
        processes[i].CT = current_time;
        processes[i].TAT = processes[i].CT - processes[i].AT;
        processes[i].WT = processes[i].TAT - processes[i].BT;
        total_WT += processes[i].WT;
        total_TAT += processes[i].TAT;
    }
    float avg_WT = total_WT / n;
    float avg_TAT = total_TAT / n;
    float THPT = static_cast<float>(n) / current_time;

    print_table(processes, n, avg_WT, avg_TAT, THPT);
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process *processes = new Process[n];
    for (int i = 0; i < n; i++)
    {
        int pid, at, bt;
        pid = i + 1;
        cout << "Enter the AT of process " << pid << ": ";
        cin >> at;
        cout << "Enter the BT of process " << pid << ": ";
        cin >> bt;
        processes[i] = Process(pid, at, bt);
    }

    sort(processes, processes + n, compare_AT);

    fcfs_scheduling(processes, n);

    delete[] processes;

    return 0;
}
