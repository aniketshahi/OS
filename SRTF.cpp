#include <iostream>
#include <climits>

using namespace std;

struct Process
{
    int pid;           // process ID
    int arrivalTime;   // arrival time
    int burstTime;     // burst time
    int remainingTime; // remaining time
};

int main()
{
    const int n = 5; // number of processes
    Process processes[n];

    // Initialize the processes
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        cout << "Enter the arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n)
    {
        int shortestTime = INT_MAX;
        int shortestIndex = -1;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime < shortestTime && processes[i].remainingTime > 0)
            {
                shortestTime = processes[i].remainingTime;
                shortestIndex = i;
            }
        }

        if (shortestIndex == -1)
        {
            currentTime++;
            continue;
        }

        // Execute the process for 1 unit of time
        processes[shortestIndex].remainingTime--;
        currentTime++;

        // Check if the process has completed
        if (processes[shortestIndex].remainingTime == 0)
        {
            cout << "Process " << processes[shortestIndex].pid << " completed at time " << currentTime << endl;
            completedProcesses++;
        }
    }

    return 0;
}
