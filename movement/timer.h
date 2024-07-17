#ifndef TIMER_H
#define TIMER_H

#include "queue/queue.h"
#include "../raylib.h"

typedef struct __TIMER__
{
    Queue actions;
    bool end;
    void (*end_fn)(void);
    double total_time ;
    double time_now ;
}Timer;


Timer *create_timer();
void add_function(Timer *timer,void (*action)(double) , double life_time , double slow_down_factor);
void wait_time(Timer *timer , double time);
void set_end_fn(Timer *timer , void (*end_fn)(void));
void set_time_now(Timer *timer , double time_now);
void start_timer(Timer *timer);
void play_timer(Timer *timer);
void free_timer(Timer *timer);


#endif //TIMER_H