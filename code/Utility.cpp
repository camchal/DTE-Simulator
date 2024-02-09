#include "Utility.h"
#include <cmath>
#include <cstdlib>
#include<iostream>
using namespace std;

float Utility::PoissonExpRand(double rate) {
    float Random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return (-1 / rate) * log(1 - Random);
}

void Utility::util_schedule_event(std::priority_queue<Event>& event_queue, char requested_event_type, float event_time, PCB *pcb) {
    Event E;
    E.event_type = requested_event_type;
    E.time = event_time;
    if (requested_event_type == 'S') {
        //delete E.Pcb; 
    } else {
        E.Pcb = pcb;
    }
    event_queue.push(E);
}

Event Utility::get_event(std::priority_queue<Event>& event_queue) {
    Event E = event_queue.top();
    event_queue.pop();
    return E;
}
PCB *Utility::create_PCB(float arrival_time, float initial_service_time, float remaining_service_time, int pcbid){
    PCB *pcb = new PCB;
    pcb->PCBid = pcbid;
    pcb->arrival_time = arrival_time;
    pcb->initial_service_time = initial_service_time;
    pcb->remaining_service_time = remaining_service_time;

    return pcb;

}
void Utility:: output(Result results){
    //turnaround time, throughput, cpu util, rdyq size
    std::cout << "Avg Turnaround: " << results.avg_turnaround_time << endl;
    std::cout << "Avg Throughput: " << results.total_throughput << endl;
    std::cout << "CPU Util: " << results.cpu_util << endl;
    std::cout << "Avg Rdy Queue: " << results.avg_rdy_size << endl;
    cout << endl;
}