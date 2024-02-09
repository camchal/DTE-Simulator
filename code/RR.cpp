#include "RR.h"
#include "Utility.h"
using namespace std;
#include<iostream>
RR::RR(float comline_lambda, float comline_service_lambda, float comline_quantum){
    num_of_processes_complete = 0;
    cpu_idle = 1;
    lambda = comline_lambda;
    service_lambda = 1/comline_service_lambda;//important
    clock = 0;
    quantum = comline_quantum;

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
void RR::handle_arrival(Event& E){
    clock = E.time;
    if(cpu_idle == 1){
        cpu_idle = 0;
        TWA = clock;
        add_TTI();
        if(E.Pcb->remaining_service_time < quantum){
            avg_turnaround_time +=  E.Pcb->remaining_service_time;
            schedule_event('D', clock+ E.Pcb->remaining_service_time, E.Pcb);
        }else{
            E.Pcb->remaining_service_time -= quantum;
            schedule_event('T', clock + quantum, E.Pcb); //schedule time slice event
        }
    }else pushToRdyQueue(E.Pcb);

    float next_arrival_time = Utility::PoissonExpRand(lambda);
    float next_service_time = Utility::PoissonExpRand(service_lambda); 
    incrementPCBID();
    PCB* new_PCB = Utility::create_PCB(clock + next_arrival_time, next_service_time, next_service_time,PCBid );
    schedule_event('A',clock+next_arrival_time,new_PCB); //next incoming process
}
void RR::handle_departure(Event &E){
    clock = E.time;
    avg_turnaround_time += clock - E.Pcb->arrival_time;
    if(ready_queue.empty()){
        cpu_idle = 1;
        TWI = clock;
    } else {
        PCB *next_pcb = ready_queue.front();
        ready_queue.pop();
    if(next_pcb->remaining_service_time <= quantum){
        schedule_event('D', clock + next_pcb->remaining_service_time, next_pcb);
    }else {
        next_pcb->remaining_service_time -= quantum;
        schedule_event('T', clock + quantum, next_pcb);
        }
    }
}
void RR::handle_time_slice(Event& E){
    clock = E.time;
    pushToRdyQueue(E.Pcb);
    PCB *next_pcb = ready_queue.front();
    ready_queue.pop();
    if(next_pcb->remaining_service_time <= quantum){
        schedule_event('D', clock + next_pcb->remaining_service_time, next_pcb);
    } else {
        next_pcb->remaining_service_time -= quantum;
        schedule_event('T', clock + quantum, next_pcb);
        }
    
}
void RR::handle_sample(){
    avg_size_rdy_queue += ready_queue.size();
    samples_processed++;
}
int RR::get_num_proc_compl(){
    return num_of_processes_complete;
}
void RR::add_TTI(){
    TTI += (TWA - TWI);
}
Event RR:: get_event(){
    Event E = Utility::get_event(event_queue);
    return E;
}
void RR:: schedule_event( char requested_event_type, float event_time, PCB *pcb){
    //in this nonpremptive implementation - event time can be used as departure time, so 
    //remaining service t has no use. but this is neccessary to have for other schedulers using the virtual layouts of 
    //schedulers.h
    Utility::util_schedule_event(event_queue, requested_event_type, event_time, pcb);
}
void RR::pushToRdyQueue(PCB* Pcb){
    ready_queue.push(Pcb);
}
void RR:: incrementPCBID(){
    PCBid++;
}
void RR:: add_proc_complete(){
  num_of_processes_complete++;
}

Result RR:: final_results(){
  results.avg_rdy_size = avg_size_rdy_queue/samples_processed;
  results.avg_turnaround_time = avg_turnaround_time/10000;
  results.cpu_util = (clock-TTI)/clock;
  results.total_throughput = 10000/clock;
  return results;
}