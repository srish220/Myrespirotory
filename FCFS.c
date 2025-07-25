#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burstTime[n], waitTime[n], turnaroundTime[n];
    int totalWait = 0, totalTurnaround = 0;

    // Take burst time input
    for(int i = 0; i < n; i++) {
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    // First process has 0 waiting time
    waitTime[0] = 0;

    // Calculate waiting times
    for(int i = 1; i < n; i++) {
        waitTime[i] = waitTime[i - 1] + burstTime[i - 1];
    }

    // Calculate turnaround times
    for(int i = 0; i < n; i++) {
        turnaroundTime[i] = waitTime[i] + burstTime[i];
        totalWait += waitTime[i];
        totalTurnaround += turnaroundTime[i];
    }

    // Output results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\n", i + 1, burstTime[i], waitTime[i], turnaroundTime[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWait / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaround / n);

    return 0;
}
