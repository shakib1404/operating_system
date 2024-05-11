#include <bits/stdc++.h>
using namespace std;

#define M 20

struct Process {
    string name;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int turnaround;
    int waiting;
    int priority; // Priority of the process
};

bool compareArrival(const Process &a, const Process &b) {
    return a.arrival < b.arrival;
}

bool comparePriority(const Process &a, const Process &b) {
    return a.priority > b.priority; // Higher priority value has higher priority
}

int main() {
    int n;
    cout << "Number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        cout << "Enter process name, arrival time, burst time, and priority for process " << i + 1 << ": ";
        cin >> processes[i].name >> processes[i].arrival >> processes[i].burst >> processes[i].priority;
        processes[i].remaining = processes[i].burst;
    }

    sort(processes.begin(), processes.end(), compareArrival);

    int current_time = 0;
    int completed_processes = 0;
    string store;
    int storetime;
    bool flag=false;
    cout << "gantt chart" << endl;
    while (completed_processes < n) {
        int highest_priority_index = -1;
        int highest_priority = INT_MIN;

        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival <= current_time && processes[i].remaining > 0 && processes[i].priority > highest_priority) {
                highest_priority = processes[i].priority;
                highest_priority_index = i;

                if(store==processes[i].name)
                    continue;

               // if(storetime=current_time)
                   // continue;

                cout << current_time << ".....";
                cout << processes[i].name << ".....";

                store = processes[i].name;
               // storetime=current_time;
            }
        }

        if (highest_priority_index == -1) {
            if (!flag){
                cout << current_time << "...idle...";
                flag = true;
            }
            ++current_time;
            continue;
        }
        flag = false;

        --processes[highest_priority_index].remaining;
        ++current_time;

        if (processes[highest_priority_index].remaining == 0) {
            ++completed_processes;
            processes[highest_priority_index].completion = current_time;
            processes[highest_priority_index].turnaround = processes[highest_priority_index].completion - processes[highest_priority_index].arrival;
            processes[highest_priority_index].waiting = processes[highest_priority_index].turnaround - processes[highest_priority_index].burst;
        }
    }

    cout << current_time << endl;
    double avg_turnaround = 0, avg_waiting = 0;
    cout << "Process\tTurnaround Time\tWaiting Time" << endl;
    for (int i = 0; i < n; ++i) {
        cout << processes[i].name << "\t" << processes[i].turnaround << "\t\t" << processes[i].waiting << endl;
        avg_turnaround += processes[i].turnaround;
        avg_waiting += processes[i].waiting;
    }
    avg_turnaround /= n;
    avg_waiting /= n;

    cout << "Average Turnaround Time:  " << avg_turnaround << endl;
    cout << "Average Waiting Time: " << avg_waiting << endl;

    return 0;
}

