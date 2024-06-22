Title:
CPU Scheduling Algorithms Simulator

Summary:
This C++ program simulates three common CPU scheduling algorithms: First-Come-First-Serve (FCFS), Shortest Job First (SJF), and Round Robin (RR). It reads process details from an input file, executes each scheduling algorithm, and prints the Gantt charts along with performance metrics such as average burst time, waiting time, turnaround time, and the total number of context switches.

Key Features:
Process Representation:

Uses a Process struct to store details of each process, including ID, arrival time, burst time, remaining time, wait time, and turnaround time.
Scheduling Algorithms:

First-Come-First-Serve (FCFS): Processes are executed in the order of their arrival.
Shortest Job First (SJF): Processes with the shortest burst time are executed next, considering only those that have arrived.
Round Robin (RR): Processes are executed in a cyclic order using a fixed time quantum, allowing for fair sharing of CPU time.
Performance Metrics:

Calculates and displays average burst time, waiting time, and turnaround time for each scheduling algorithm.
Tracks and displays the total number of context switches.
Gantt Chart Visualization:

Prints a Gantt chart for each scheduling algorithm to visually represent the order and duration of process execution.
Usage:
Input File:
The input file should contain process details formatted as id,arrivalTime,burstTime on each line.
Running the Program:
Compile and run the program. Ensure the input file is in the same directory or provide the correct path.
The program reads the input file, processes the data, and executes each scheduling algorithm.
The results, including Gantt charts and performance metrics, are printed to the console.
Example:
yaml
Copy code
Input File (inputFile):
1,0,5
2,2,3
3,4,1

Output:
First-Come-First-Serve Scheduling
Gantt Chart:
P1 ***** P2 *** P3 *
Average Burst Time: 3.00
Average Waiting Time: 3.33
Average Turnaround Time: 6.33
Total # of Context Switches: 2

Shortest-Job-First Scheduling
Gantt Chart:
P1 ***** P3 * P2 ***
Average Burst Time: 3.00
Average Waiting Time: 1.67
Average Turnaround Time: 4.67
Total Context Switches: 2

Round Robin Scheduling
Gantt Chart:
P1 ** P2 ** P3 * P1 ** P2 *
Average Burst Time: 3.00
Average Waiting Time: 3.33
Average Turnaround Time: 6.33
Total Context Switches: 4
This program is useful for students and professionals learning about CPU scheduling algorithms, providing a clear visual and numerical comparison of the different scheduling methods.






