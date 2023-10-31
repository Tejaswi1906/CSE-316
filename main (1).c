#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10
#define TIME_QUANTUM 2

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

int main() {
    struct Process processes[MAX_PROCESSES];
    int num_processes, total_waiting_time = 0, total_turnaround_time = 0;
    int time = 0, completed = 0, i;

    // Read input from user
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    for (i = 0; i < num_processes; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Run the Round Robin algorithm
    while (completed < num_processes) {
        for (i = 0; i < num_processes; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time <= TIME_QUANTUM) {
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    completed++;
                    processes[i].waiting_time = time - processes[i].arrival_time - processes[i].burst_time;
                    processes[i].turnaround_time = time - processes[i].arrival_time;
                } else {
                    time += TIME_QUANTUM;
                    processes[i].remaining_time -= TIME_QUANTUM;
                }
            }
        }
    }

    // Calculate the average waiting time and turnaround time
    for (i = 0; i < num_processes; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    float avg_waiting_time = (float)total_waiting_time / num_processes;
    float avg_turnaround_time = (float)total_turnaround_time / num_processes;

    // Print the results
    printf("Round Robin Scheduling Algorithm\n");
    printf("Number of processes: %d\n", num_processes);
    printf("Time quantum: %d\n", TIME_QUANTUM);
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < num_processes; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("Average waiting time: %.2f\n", avg_waiting_time);
    printf("Average turnaround time: %.2f\n", avg_turnaround_time);

    return 0;
}
