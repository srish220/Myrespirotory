#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Process {
    int id, arrival, burst, remaining, completion, first_exec;
    bool started;
};

int main() {
    int n, time_quantum;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cin >> processes[i].arrival >> processes[i].burst;
        processes[i].remaining = processes[i].burst;
        processes[i].started = false;
        processes[i].first_exec = -1;
    }

    cout << "Enter Time Quantum: ";
    cin >> time_quantum;

    int time = 0, completed = 0;
    queue<int> q;
    vector<bool> in_queue(n, false);

    while (completed < n) {
        // Add new arrivals to the queue
        for (int i = 0; i < n; ++i) {
            if (!in_queue[i] && processes[i].arrival <= time && processes[i].remaining > 0) {
                q.push(i);
                in_queue[i] = true;
            }
        }

        if (q.empty()) {
            time++;
            continue;
        }

        int idx = q.front(); q.pop();

        // First time executing, mark start time
        if (!processes[idx].started) {
            processes[idx].first_exec = time;
            processes[idx].started = true;
        }

        int run_time = min(time_quantum, processes[idx].remaining);
        time += run_time;
        processes[idx].remaining -= run_time;

        // Add newly arrived processes during execution
        for (int i = 0; i < n; ++i) {
            if (!in_queue[i] && processes[i].arrival <= time && processes[i].remaining > 0) {
                q.push(i);
                in_queue[i] = true;
            }
        }

        if (processes[idx].remaining > 0) {
            q.push(idx); // not finished yet
        } else {
            processes[idx].completion = time;
            completed++;
        }
    }

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for (auto& p : processes) {
        int tat = p.completion - p.arrival;
        int wt = tat - p.burst;
        int rt = p.first_exec - p.arrival;
        cout << "P" << p.id << "\t" << p.arrival << "\t" << p.burst << "\t"
             << p.completion << "\t" << tat << "\t" << wt << "\t" << rt << "\n";
    }

    return 0;
}
