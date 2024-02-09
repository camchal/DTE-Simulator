#ifndef HRRN_H
#define HRRN_H

#include "Utility.h"
#include "Scheduler.h"
#include <queue>

class HRRN : public Scheduler {
private:
    //members
    int num_of_processes_complete;
    bool cpu_idle;
    float lambda;
    float service_lambda;
    float clock;
    std::priority_queue<Event> event_queue;
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
    void handle_sample() override;
    int get_num_proc_compl() override;
    void add_proc_complete() override;
    void add_TTI() override; //TTI += (TWA-TWI)
    Event get_event() override;
    void schedule_event(char requested_event_type, float event_time, PCB *pcb) override;
    void pushToRdyQueue(PCB* Pcb) override;
    void incrementPCBID();
    HRRN(float comline_lambda, float comline_service_lambda); // Constructor declaration
    float getavgturn(){ return avg_turnaround_time;};
    void HRRNRatioReevaluation(float clock, std::queue<PCB*> &ready_queue);

    Result final_results() override;
    
    

};
#endif // HRRN_H