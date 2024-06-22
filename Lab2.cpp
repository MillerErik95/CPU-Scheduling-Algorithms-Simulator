/*
CPU scheduling Algorithms 
First Come First Serve
Shortest Job First 
Round Robin
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <sstream>
using namespace std;

struct Process 
{
	int id;
	int arrivalTime;
	int burstTime;
	int remainingTime;
	int waitTime;
	int turnaroundTime;

	Process(int i, int a, int b, int r, int w, int t)
		: id(i), arrivalTime(a), burstTime(b), remainingTime(r), waitTime(w), turnaroundTime(t) {}
};


// Compare arrival times for fcfs //
bool compareArrivalTime(Process a, Process b)
{
	return a.arrivalTime < b.arrivalTime;
}

// Prints Gantt Function //
void printGanttChart(vector<pair<int, int>> ganttChart)
{
	cout << "\nGantt Chart:\n";
	for (const auto& p : ganttChart)
	{
		cout << "P" << p.first << " ";
		for (int i = 0; i < p.second; i++)
			cout << "*";
	}

	cout << "|\n";
	int time = 0;
	cout << time;
	for (const auto& p : ganttChart)
	{
		for (int i = 0; i < p.second; i++)
			cout << " ";
		time += p.second;
		cout << time;
	}
	cout << "\n";
}
/*
	First Come First Serve Scheduling
*/
void fcfs(vector<Process>& processes)
{
	sort(processes.begin(), processes.end(), compareArrivalTime);
	int time = 0;
	int waitTime = 0;
	int turnAroundtime = 0;
	int contextSwitch = 0;
	int burstSum = 0;
	vector<pair<int, int>> ganttChart;

	for (auto& p : processes)
	{
	    if (time < p.arrivalTime) 
			time = p.arrivalTime;
		
		p.waitTime = time - p.arrivalTime;
		waitTime += p.waitTime;
		time += p.burstTime;
		p.turnaroundTime = time - p.arrivalTime;
		turnAroundtime += p.turnaroundTime;
		contextSwitch++;
		ganttChart.push_back({ p.id, p.burstTime });
		burstSum += p.burstTime;
	}

	printGanttChart(ganttChart);
	cout << "Average Burst Time: " << (double)burstSum / processes.size() << endl;
	cout << "Average Waiting Time: " << (double)waitTime / processes.size() << endl;
	cout << "Average Turnaround Time: " << (double)turnAroundtime / processes.size() << endl;
	cout << "Total # of Context Switches: " << contextSwitch - 1 << endl << endl;
}

// Shortest Job First scheduling //
void sjf(vector<Process>& processes) 
{
	// Sort processes based on arrival time
	sort(processes.begin(), processes.end(), compareArrivalTime);
	int time = 0;
	int waitSum = 0;
	int turnaroundSum = 0;
	int contextSwitch = 0;
	int burstSum = 0;
	vector<pair<int, int>> gantt_chart;
	// Vector to keep track of executed processes
	vector<bool> executed(processes.size(), false);
	int executed_count = 0;

	// Loop until all processes have been executed
	while (executed_count < processes.size()) 
	{
		int min_burst_time = INT32_MAX;
		int selected_process = -1;
		// // Find the process with the minimum burst time that has not been executed and has arrived
		for (int i = 0; i < processes.size(); i++) 
		{
			if (!executed[i] && processes[i].arrivalTime <= time && processes[i].burstTime < min_burst_time) 
			{
				min_burst_time = processes[i].burstTime;
				selected_process = i;
			}
		}

		// If a process is found, execute it
		if (selected_process != -1) 
		{
			Process& p = processes[selected_process];
			executed[selected_process] = true;
			p.waitTime = time - p.arrivalTime;
			waitSum += p.waitTime;
			time += p.burstTime;
			p.turnaroundTime = time - p.arrivalTime;
			turnaroundSum += p.turnaroundTime;
			contextSwitch++;
			gantt_chart.push_back({ p.id, p.burstTime });
			executed_count++;
			burstSum += p.burstTime;
		}
		else 
			// If no process is available to execute, increment the time
			time++;	
	}

	// Print Gantt Chart and performance metrics
	printGanttChart(gantt_chart);
	cout << "Average Burst Time: " << (double)burstSum / processes.size() << endl;
	cout << "Average Waiting Time: " << (double)waitSum / processes.size() << endl;
	cout << "Average Turnaround Time: " << (double)turnaroundSum / processes.size() << endl;
	cout << "Total Context Switches: " << contextSwitch - 1 << endl << endl;
}
/*
	Round Robin Scheduling
*/
void roundRobin(vector<Process>& processes, int time_quantum)
{
	// Sort processes based on arrival time
	sort(processes.begin(), processes.end(), compareArrivalTime);

	int n = processes.size();
	int time = 0;
	int wt = 0;
	int tat = 0;
	int contextSwitch = 0;
	int burstSum = 0;
	vector<pair<int, int>> gantt_chart;
	queue<int> ready_queue;

	int remainingTime[n], arrivalTime[n], burstTime[n];
	for (int i = 0; i < n; i++)
	{
		remainingTime[i] = processes[i].burstTime;
		arrivalTime[i] = processes[i].arrivalTime;
		burstTime[i] = processes[i].burstTime;
    burstSum += processes[i].burstTime;
	}

  int lastProcess = -1;
	// Loop until the ready queue is empty
	while (time < accumulate(burstTime, burstTime + n, 0))
	{
		bool idle = true;
		for (int i = 0; i < n; i++)
		{
			if (arrivalTime[i] <= time && remainingTime[i] > 0)
			{
				idle = false;

        if (lastProcess != i)
        {
          contextSwitch++;
          lastProcess = i;
        }

				// Calculate the executed time for the current process
				int executed_time = min(time_quantum, remainingTime[i]);
				remainingTime[i] -= executed_time;
				time += executed_time;
				gantt_chart.push_back({ processes[i].id, executed_time });
        
				// If the current process has remaining time, add it back to the ready queue
				if (remainingTime[i] == 0)
				{
					// If the process is completed, calculate waiting and turnaround times
					tat += time - arrivalTime[i];
					wt += time - arrivalTime[i] - burstTime[i];
				}
			}
		}
		if (idle)
			time++;
	}

	// Print Gantt Chart and performance metrics
	printGanttChart(gantt_chart);
	cout << "Average Burst Time: " << (double)burstSum / n << endl;
	cout << "Average Waiting Time: " << (double)wt / n << endl;
	cout << "Average Turnaround Time: " << (double)tat / n << endl;
	cout << "Total Context Switches: " << contextSwitch - 1 << endl;
}

int main() {
	vector<Process> processes;

  ifstream inputFile("inputFile");
  if (!inputFile)
  {
    cerr << "Errot opening input file. " << endl;
    return 1;
  }
  // Getting input from file, seperating by commas
  string line;
  while (getline(inputFile, line))
    {
      istringstream lineStream(line);
      int id, arrivalTime, burstTime;
      char comma;

      lineStream >> id >> comma >> arrivalTime >> comma >> burstTime;
      processes.push_back(Process(id, arrivalTime, burstTime, burstTime, 0, burstTime));
    }
    
  inputFile.close();
      
	cout << "//First-Come-First-Serve Scheduling//";
	fcfs(processes);

	cout << "//Shortest-Job-First Scheduling//";
	sjf(processes);

	int quantumTime = 2;
	cout << "//Round Robin Scheduling//";
	roundRobin(processes, quantumTime);

	return 0;
}
