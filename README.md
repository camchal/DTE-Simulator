# Discrete Time Event Simulator

## Overview
This discrete time event simulator is designed to mimic the arrival and processing of events using a Poisson distribution. The simulator provides different CPU scheduling algorithms to handle these events: Round Robin, First Come First Serve (FCFS), Shortest Time Remaining First (STRF), and Highest Response Ratio Next (HRRN).

## Features
- Simulates events arriving based on a Poisson distribution.
- Supports various CPU scheduling algorithms.
- Provides statistics and metrics for performance evaluation.

## Supported CPU Scheduling Algorithms
1. **Round Robin (RR)**
   - Each process is assigned a fixed time slice in the CPU.
   - Processes are serviced in a circular order.
   
2. **First Come First Serve (FCFS)**
   - Processes are executed in the order they arrive.
   
3. **Shortest Time Remaining First (STRF)**
   - The process with the shortest remaining processing time is executed next.
   
4. **Highest Response Ratio Next (HRRN)**
   - Calculates the ratio of the waiting time of a process to its estimated processing time.
   - Processes with the highest ratio are given priority.
## How to Compile and Run
To compile the simulator, use the following command:

g++ -o sim *.cpp

./sim (scheduler) (arrival rate) (average service time) (round robin quantum)

Replace the placeholders with the respective values:
- `(scheduler)`: An integer ranging within [1-4] corresponding to:
  - 1: First Come First Serve
  - 2: Shortest Remaining Time First
  - 3: Highest Response Ratio Next
  - 4: Round Robin
- `(arrival rate)`: The average rate at which events arrive.
- `(average service time)`: The average time taken to process an event.
- `(round robin quantum)`: Must be provided even if not using Round Robin. It represents the time slice for Round Robin scheduling.

##Example
./sim 2 5 10 1

This command runs the simulator with Shortest Remaining Time First (STRF) scheduling, an arrival rate of 5 events per time unit, an average service time of 10 time units, and a Round Robin quantum of 1 time unit.