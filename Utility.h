#ifndef UTILITY_H
#define UTILITY_H
#include <queue>
struct PCB {
        float arrival_time;
        float initial_service_time;
        float remaining_service_time;
        int PCBid;
};
struct Event {
    char event_type;
    float time;
    PCB *Pcb;
    bool operator<(const Event& t) const { //priority queue
        return time > t.time;
    }
};
struct Result {
    double avg_rdy_size;
    double avg_turnaround_time;
    double cpu_util;
    double total_throughput;
};

class Utility {
public:
    static float PoissonExpRand(double rate);
    static void util_schedule_event(std::priority_queue<Event>& event_queue, char requested_event_type, float event_time, PCB *pcb);
    static Event get_event(std::priority_queue<Event>& event_queue);
    static PCB* create_PCB(float arrival_time, float initial_service_time, float remaining_service_time, int pcbid);
    static void output(Result results);
};
#endif // UTILITY_H