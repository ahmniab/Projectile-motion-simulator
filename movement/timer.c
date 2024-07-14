#include <stdlib.h>
#include <assert.h>
#include "timer.h"

typedef struct __TIMER_NODE_
{
    double time;
    void (*ation)();
}Timer_node;

Timer *create_timer(){
    Timer *new_timer = (*Timer) malloc(sizeof (Timer));
    assert(new_timer);
    new_timer->actions = create_queue();
    new_timer->end = false;
    return new_timer;
}

void add_function(Timer *timer,void (*ation)() , double life_time){
    assert(timer);

    Timer_node *new_timer_node = (Timer_node*) malloc(sizeof(Timer_node));
    new_timer_node->time = time;
    new_timer_node->action = action;

    void enqueue (Timer->queue, (void*) new_timer_node);
}

void play_timer(Timer *timer){
    if (is_q_empty(timer->actions))
    {
        timer->end = true;
        return;
    }

    Timer_node *node = (Timer_node*)queue_front (timer->actions) ;
    if (node->time <= 0 )
    {
        node = dequeue(timer->actions)
        free(node);
        return;
    }

    (*node->action)();
    node->time -= GetFrameTime();
    

    
}
