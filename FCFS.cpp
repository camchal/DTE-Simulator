#include "FCFS.h"
#include "Utility.h"
using namespace std;
#include<iostream>
FCFS::FCFS(float comline_lambda, float comline_service_lambda){
    num_of_processes_complete = 0;
    cpu_idle = 1;
    lambda = comline_lambda;
    service_lambda = 1/comline_service_lambda;//important
    clock = 0;

    //both already created in header file.
    // std::priority_queue<Event> event_queue;
    // std::priority_queue<PCB*, std::vector<PCB*>, FCFSRdyQueuePriority> ready_queue;

    //cpu utilization variables
     TTI = 0; //Total Time Idle
     TWI = 0; //Time Went Idle
     TWA = 0; //Time Went Active
    //TTI = (TWA-TWI)

     avg_size_rdy_queue = 0;
     samples_processed = 0;

    //used for pcb structs
     PCBid = 0;

    //Turnaround time variables
     avg_turnaround_time = 0; //divide by 10000 at end

    //pre-inflating ready queue with regular events to sample at regular intervals
    for(int i = 0; i < 150000; i++){
    PCB *sampPCB = nullptr;
    schedule_event('S', i+1, sampPCB);
  }
}
void FCFS::handle_arrival(Event& E){
    clock = E.time;
    if(cpu_idle == 1){
    cpu_idle = 0;
    TWA = clock; //time cpu went active
    add_TTI(); // TTI += (TWA - TWI);
    avg_turnaround_time +=  E.Pcb->remaining_service_time;
    schedule_event('D', clock+E.Pcb->remaining_service_time,E.Pcb );
  } else pushToRdyQueue(E.Pcb); //cpu busy, adding to ready queue(based on when it arrived)
  
  float next_arrival_time = Utility::PoissonExpRand(lambda);
  float next_service_time = Utility::PoissonExpRand(service_lambda); 
  incrementPCBID();
  PCB* new_PCB = Utility::create_PCB(clock + next_arrival_time, next_service_time, next_service_time,PCBid );
  schedule_event('A',clock+next_arrival_time,new_PCB); //next incoming process
}
void FCFS::handle_departure(Event &E){
    clock = E.time;
    if(ready_queue.empty()){
    cpu_idle = 1;
    TWI = clock;//time CPU went idle
  }else {
    //shows dif in time between arrival and completion, adds to avg
    PCB * next_in_line_pcb = ready_queue.top();
    avg_turnaround_time += (clock - (next_in_line_pcb->arrival_time) + next_in_line_pcb->initial_service_time);
    ready_queue.pop();
    schedule_event('D', clock+next_in_line_pcb->remaining_service_time,next_in_line_pcb); //passing next pcb in rq

  }
}
void FCFS::handle_sample(){
    avg_size_rdy_queue += ready_queue.size();
    samples_processed++;
}
int FCFS::get_num_proc_compl(){
    return num_of_processes_complete;
}
void FCFS::add_TTI(){
    TTI += (TWA - TWI);
}
Event FCFS:: get_event(){
    Event E = Utility::get_event(event_queue);
    return E;
}
void FCFS:: schedule_event( char requested_event_type, float event_time, PCB *pcb){
    //in this nonpremptive implementation - event time can be used as departure time, so 
    //remaining service t has no use. but this is neccessary to have for other schedulers using the virtual layouts of 
    //schedulers.h
    Utility::util_schedule_event(event_queue, requested_event_type, event_time, pcb);
}
void FCFS::pushToRdyQueue(PCB* Pcb){
    ready_queue.push(Pcb);
}
void FCFS:: incrementPCBID(){
    PCBid++;
}
void FCFS:: add_proc_complete(){
  num_of_processes_complete++;
}

Result FCFS:: final_results(){
  results.avg_rdy_size = avg_size_rdy_queue/samples_processed;
  results.avg_turnaround_time = avg_turnaround_time/10000;
  results.cpu_util = (clock-TTI)/clock;
  results.total_throughput = 10000/clock;
  return results;
}