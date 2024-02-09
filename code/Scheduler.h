#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "Utility.h"
#include <iostream>
struct EventParams {
    char requested_event_type;
    float event_time;
    float proc_arrival_time;
    // Add more parameters as needed
};
class Scheduler {
public:
    virtual void handle_arrival(Event& E) = 0;
    virtual void handle_departure(Event& E) = 0;
    virtual void handle_time_slice(Event& E){std::cout << "hey" << std::endl;};
    virtual void handle_sample() = 0;
    virtual int get_num_proc_compl() = 0;
    virtual Event get_event() =0;
    virtual void schedule_event(char requested_event_type, float event_time, PCB *pcb) = 0;
    virtual void add_TTI() = 0; //TTI += (TWA-TWI)
    virtual void pushToRdyQueue(PCB* Pcb) = 0;
    virtual void add_proc_complete() = 0;
    virtual Result final_results()=0;
    virtual float getavgturn()=0;

};
#endif // SCHEDULER_H
