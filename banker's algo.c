#include <iostream>
using namespace std;

const int P = 5;
const int R = 3;

int available[R] = {3, 3, 2};
int maxNeed[P][R] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
int allocation[P][R] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};
int need[P][R];


void calculateNeed() {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maxNeed[i][j] - allocation[i][j];
}

// Check if the system is in a
bool isSafe() {
    int work[R];
    bool finish[P] = {false};
    int safeSeq[P];
    int count = 0;

    for (int i = 0; i < R; i++)
        work[i] = available[i];

    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                bool canProceed = true;
                for (int r = 0; r < R; r++) {
                    if (need[p][r] > work[r]) {
                        canProceed = false;
                        break;
                    }
                }
                if (canProceed) {
                    for (int r = 0; r < R; r++)
                        work[r] += allocation[p][r];
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "System is not in a safe state.\n";
            return false;
        }
    }

    cout << "System is in a safe state.\nSafe sequence: ";
    for (int i = 0; i < P; i++)
        cout << "P" << safeSeq[i] << " ";
    cout << endl;

    return true;
}

// Try to request resources for a process
bool requestResources(int p, int request[]) {
    // Check if request <= need
    for (int i = 0; i < R; i++) {
        if (request[i] > need[p][i]) {
            cout << "Error: Process has exceeded its maximum claim.\n";
            return false;
        }
    }

    // Check if request <= available
    for (int i = 0; i < R; i++) {
        if (request[i] > available[i]) {
            cout << "Resources not available. Process must wait.\n";
            return false;
        }
    }

    // Pretend to allocate
    for (int i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[p][i] += request[i];
        need[p][i] -= request[i];
    }

    // Check if system is still safe
    if (isSafe()) {
        cout << "Request granted.\n";
        return true;
    } else {
        // Rollback
        for (int i = 0; i < R; i++) {
            available[i] += request[i];
            allocation[p][i] -= request[i];
            need[p][i] += request[i];
        }
        cout << "Request denied to keep system safe.\n";
        return false;
    }
}

int main() {
    calculateNeed();
    isSafe();

    // Example: P1 requests (1, 0, 2)
    int request[R] = {1, 0, 2};
    cout << "\nProcess P1 requesting resources: {1, 0, 2}\n";
    requestResources(1, request);

    return 0;
}
