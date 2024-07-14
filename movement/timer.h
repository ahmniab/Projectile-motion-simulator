#ifndef TIMER_H
#define TIMER_H

#include "queue/queue.h"
#include "../raylib.h"

typedef struct __TIMER__
{
    Queue actions;
    bool end;
}Timer;


Timer *create_timer();
void add_function(Timer *timer,void (*ation)() , double life_time);
void play_timer(Timer *timer);


#endif //TIMER_H