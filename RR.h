#ifndef RR_H
#define RR_H

#include "Utility.h"
#include "Scheduler.h"
#include <queue>

// struct FCFSRdyQueuePriority {
//         bool operator()(const PCB* pcb1, const PCB* pcb2) const {
//             return pcb1->arrival_time > pcb2->arrival_time;
//         };
//     };


class RR : public Scheduler {
private:
    //members
    int num_of_processes_complete;
    float quantum;
    bool cpu_idle;
    float lambda;
    float service_lambda;
    float clock;
    std::priority_queue<Event> event_queue;
    //std::priority_queue<PCB*, std::vector<PCB*>, FCFSRdyQueuePriority> ready_queue;
    std::queue<PCB*> ready_queue;
    float TTI;
    float TWI;
    float TWA;
    float avg_turnaround_time;
    float avg_size_rdy_queue;
    int samples_processed;
    int PCBid;
    Result results;

public:
    //functions
    void handle_arrival(Event& E) override;//unique parameters
    void handle_departure(Event& E) override;
    void handle_time_slice(Event& E)override;
    void handle_sample() override;
    int get_num_proc_compl() override;
    void add_proc_complete() override;
    void add_TTI() override; //TTI += (TWA-TWI)
    Event get_event() override;
    void schedule_event(char requested_event_type, float event_time, PCB *pcb) override;
    void pushToRdyQueue(PCB* Pcb) override;
    void incrementPCBID();
    RR(float comline_lambda, float comline_service_lambda, float quantum); // Constructor declaration
    float getavgturn(){ return avg_turnaround_time;};


    Result final_results() override;
    
    

};
#endif // RR_H