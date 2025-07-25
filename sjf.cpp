#include <bits/stdc++.h>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitTime;
};
bool compareByBurst(Process a, Process b) {
    return a.burstTime < b.burstTime;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);


    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter Burst Time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
    }


    sort(processes.begin(), processes.end(), compareByBurst);

    int currentTime = 0, totalWait = 0, totalTAT = 0;


    for (int i = 0; i < n; ++i) {
        currentTime += processes[i].burstTime;
        processes[i].completionTime = currentTime;
        processes[i].turnaroundTime = processes[i].completionTime; // Arrival = 0
        processes[i].waitTime = processes[i].turnaroundTime - processes[i].burstTime;

        totalWait += processes[i].waitTime;
        totalTAT += processes[i].turnaroundTime;
    }


    cout << "\nProcess\tBurst\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; ++i) {
        cout << "P" << processes[i].id << "\t"
             << processes[i].burstTime << "\t"
             << processes[i].completionTime << "\t"
             << processes[i].turnaroundTime << "\t"
             << processes[i].waitTime << "\n";
    }


    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << (float)totalWait / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTAT / n << endl;

    return 0;
}
