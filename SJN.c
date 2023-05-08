#include <stdio.h>
void sjf(int p, int process[], int arrival[], int burst[], int wait[], int turnaround[], int completion[]) {
    int i, j, pos, temp;
    int total = 0, t = 0, min;
    float avg_wt, avg_tat;

    // Initialize wait and turnaround times
    for (i = 0; i < p; i++) {
        wait[i] = 0;
        turnaround[i] = 0;
        completion[i] = -1;
    }

    // Sort processes based on arrival time
    for (i = 0; i < p - 1; i++) {
        pos = i;
        for (j = i + 1; j < p; j++) {
            if (arrival[j] < arrival[pos]) {
                pos = j;
            }
        }
        temp = process[i];
        process[i] = process[pos];
        process[pos] = temp;
        temp = arrival[i];
        arrival[i] = arrival[pos];
        arrival[pos] = temp;
        temp = burst[i];
        burst[i] = burst[pos];
        burst[pos] = temp;
    }

    // Calculate completion times, waiting times, and turnaround times
    for (i = 0; i < p; i++) {
        min = 100000;
        pos = -1;
        for (j = 0; j < p; j++) {
            if (arrival[j] <= t && completion[j] == -1) {
                if (burst[j] < min) {
                    min = burst[j];
                    pos = j;
                }
            }
        }
        if (pos != -1) {
            completion[pos] = t + burst[pos];
            wait[pos] = completion[pos] - arrival[pos] - burst[pos];
            if (wait[pos] < 0) {
                wait[pos] = 0;
            }
            turnaround[pos] = completion[pos] - arrival[pos];
            total += turnaround[pos];
            t = completion[pos];
        } else {
            t++;
        }
    }

    // Calculate average waiting time and turnaround time
    avg_wt = (float)total / p;
    avg_tat = (float)total / p;

    // Display output
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tCompletion Time\tTurnaround Time\n");
    for (i = 0; i < p; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process[i], arrival[i], burst[i], wait[i], completion[i], turnaround[i]);
    }
    printf("\nAverage Waiting Time: %f\n", avg_wt);
    printf("Average Turnaround Time: %f\n", avg_tat);
    printf("\nThroughput: %f\n", (float)p / t);
    printf("CPU Utilization: %f\n", (float)total / t);
}


int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int p =n;
    int process[n], arrival[n], burst[n];
    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time and burst time for process %d: ", i+1);
        scanf("%d %d", &arrival[i], &burst[i]);
        process[i] = i+1;
    }
    
     int wait[p], turnaround[p], completion[p];

    sjf(p, process, arrival, burst, wait, turnaround, completion);
    // rest of the SJF code here
    return 0;
}