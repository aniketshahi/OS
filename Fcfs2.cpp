#include <iostream>
#include <conio.h>
using namespace std;
int main()
{
    int n, i, j, k, temp, sum = 0;
    int at[10], bt[10], ct[10], wt[10], tat[10];
    float awt = 0, atat = 0;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the arrival time and burst time of the processes:" << endl;
    for (i = 0; i < n; i++)
    {
        cout << "Arrival time of process " << i + 1 << ": ";
        cin >> at[i];
        cout << "Burst time of process " << i + 1 << ": ";
        cin >> bt[i];
    }
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (at[i] > at[j])
            {
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        sum = sum + bt[i];
        ct[i] = sum;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        awt = awt + wt[i];
        atat = atat + tat[i];
    }
    cout << endl
         << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    for (i = 0; i < n; i++)
    {
        cout << i + 1 << "\t" << at[i] << "\t\t" << bt[i] << "\t\t" << ct[i] << "\t\t" << tat[i] << "\t\t" << wt[i] << endl;
    }
    cout << endl
         << "Average Waiting Time: " << awt / n << endl;
    cout << "Average Turnaround Time: " << atat / n << endl;
    getch();
    return 0;
}
