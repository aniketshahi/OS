// Longest Job First
// Criteria : Burst Time
// Mode : Non Preemptive
#include <bits/stdc++.h>
using namespace std;
class Process
{
public:
    int pid; //process id
    int at;  //arrival time
    int bt;  //burst time
    int wt;  //waiting time
    int tat; //turn around time
    int ct;  //completion time
    Process()
    {
        pid = -1;
        at = -1;
        bt = 0;
        wt = 0;
        tat = 0;
        ct = 0;
    }
};

bool processCmpAT(Process p1, Process p2)
{
    // to Sort According to AT
    if (p1.at < p2.at)
        return true;
    if (p1.at == p2.at)
        return p1.pid < p2.pid; //if arrival times are equal compare pid
    return false;
}
bool processCmpPid(Process p1, Process p2)
{
    // to Sort According to AT
    if (p1.pid < p2.pid)
        return true;
    return false;
}
bool processCmpBT(Process p1, Process p2)
{
    // to Sort According to AT
    if (p1.bt > p2.bt)
        return true;
    if (p1.bt == p2.bt)
        return p1.pid < p2.pid; //if arrival times are equal compare pid
    return false;
}
void display(vector<Process> &, int);
void display(vector<Process> &v, int n)
{
    int i = 0;
    cout << "Pid \t AT \t BT \t CT \t TAT \t WT" << endl;
    for (i = 0; i < n; i++)
    {
        cout << v[i].pid << "\t" << v[i].at << "\t" << v[i].bt << "\t" << v[i].ct << "\t" << v[i].tat << "\t" << v[i].wt << endl;
    }
}
int main()
{
    int n, i = 0;
    cout << "Enter no. of processes\n";
    cin >> n;
    vector<Process> incoming(n, Process());
    vector<Process> ready;
    vector<Process> completed;

    cout << "Input , enter one process on one line <Pid> <AT> <BT> \n";
    for (i = 0; i < n; i++)
    {
        cin >> incoming[i].pid >> incoming[i].at >> incoming[i].bt;
    }
    sort(incoming.begin(), incoming.end(), processCmpAT);

    int tc = 0; // no of tasks or process completed
    int clock = 0;
    double tsum = 0, wsum = 0;
    while (completed.size() != n)
    {
        for (int j = 0; j < incoming.size(); j++)
        {
            if (incoming[j].at <= clock)
            {
                // erase from incoming , put it into ready for processing
                ready.push_back(incoming[j]);
                incoming.erase(incoming.begin() + j);
                j--;
            }
        }

        if (ready.empty())
        {
            clock++;
        }
        else
        {
            // process ready and calculate ct
            sort(ready.begin(), ready.end(), processCmpBT);
            clock += ready[0].bt;
            //instead of following complicated if else I could do ct = clock ;
            ready[0].ct = clock;
            // if (completed.empty()) //first case
            // {
            //     ready[0].ct = ready[0].at + ready[0].bt;
            // }
            // else if (completed.back().ct >= ready[0].at)
            // {
            //     ready[0].ct = completed.back().ct + ready[0].bt;
            // }
            // else
            // {
            //     ready[0].ct = ready[0].at + ready[0].bt;
            // }
            ready[0].tat = ready[0].ct - ready[0].at;
            ready[0].wt = ready[0].tat - ready[0].bt;
            tsum += ready[0].tat;
            wsum += ready[0].wt;

            completed.push_back(ready[0]);
            ready.erase(ready.begin());
        }
    }
    double tavg = tsum / n;
    double wavg = wsum / n;
    sort(completed.begin(), completed.end(), processCmpPid);
    display(completed, n);
    cout << "Tsum = " << tsum << " \t WT sum =" << wsum << endl;
    cout << "Tavg = " << tavg << " \t WT avg =" << wavg;
    return 0;
}