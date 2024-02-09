
// Developed by Cameron Chalupa 
#include <iostream>
#include <iomanip>
#include <queue>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "FCFS.h"
#include "HRRN.h"
#include "RR.h"
#include "SRTF.h"
#include "Scheduler.h"
#include "Utility.h"
using namespace std;


void simulation(int scheduler_type, float comline_lambda, float comline_service_lambda, float quantum){

  Scheduler *scheduler;

  switch(scheduler_type){
    case 1:
      scheduler = new FCFS(comline_lambda, comline_service_lambda);
    break;
    case 2:
      scheduler = new SRTF(comline_lambda, comline_service_lambda);
    break;
    case 3:
      scheduler = new HRRN(comline_lambda, comline_service_lambda);
    break;
    case 4:
      scheduler = new RR(comline_lambda, comline_service_lambda, quantum);
    break;
    default: cout<< "Invalid Scheduler" << endl;
    return;
    break;
  }
  
  //first arrival
  float starter_arrival_time = Utility::PoissonExpRand(comline_lambda);
  float starter_service_time = Utility::PoissonExpRand(1/comline_service_lambda);
  PCB * firstPCB = Utility::create_PCB(starter_arrival_time, starter_service_time, starter_service_time, 0);//pcbid of 0
  scheduler->schedule_event('A', starter_arrival_time, firstPCB);
  while(scheduler->get_num_proc_compl() < 10000){
    Event current_event = scheduler->get_event();
    switch(current_event.event_type){
      case 'A' :
            scheduler->handle_arrival(current_event);
            break;
      case 'D' :
            scheduler->handle_departure(current_event);
            scheduler->add_proc_complete();
            delete current_event.Pcb; //only deletes processes that have been completed :P
            break;
      case 'T' :
            scheduler->handle_time_slice(current_event);
            break;
      case 'S' :
            scheduler->handle_sample();
            break;
    }
}
//turnaround, throughput, cpuutil, avg num in rdy queue
Utility::output(scheduler->final_results());

delete scheduler;
}

int main(int argc, char *argv[]) {
  srand(time(0));
  if(argc <= 4){
    cout << "COMPILE: g++ -o sim *.cpp" << endl;
    cout << "INPUT: ./sim (scheduler) (arrival lambda) (average service time) (rr quantum)"<< endl;
    cout << "\t Input integer value for specified scheduler:" <<endl;
    cout << "\t \t 1-- First Come First Serve " << endl;
    cout << "\t \t 2-- Shortest Remaining Time First " << endl;
    cout << "\t \t 3-- Highest Response Ratio Next " << endl;
    cout << "\t \t 4-- Round Robbin " << endl;
    cout << "----------------------------------------------------" <<  endl;
}else{
  int scheduler_type = std::atoi(argv[1]);
  float comline_lambda = std::strtof(argv[2], NULL);
  float comline_service_lambda = std::strtof(argv[3], NULL);
  float quantum = std::strtof(argv[4], NULL);
  simulation(scheduler_type, comline_lambda, comline_service_lambda, quantum);
}

 return 0;
}