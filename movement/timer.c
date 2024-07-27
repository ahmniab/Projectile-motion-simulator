#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "timer.h"

typedef struct __TIMER_NODE_
{
    double slow_down_factor;
    double left_time;
    double time_now;
    void (*action)(double);
    void (*end_action)();
}Timer_node;

Timer *create_timer(){
    Timer *new_timer = (Timer*) malloc(sizeof (Timer));
    assert(new_timer);
    new_timer->actions = create_queue();
    new_timer->end = true;
    new_timer->end_fn = NULL;
    new_timer->total_time = 0;
    new_timer->time_now = 0;
    return new_timer;
}

void start_timer(Timer *timer){
    timer->end = false;
}

void set_end_fn(Timer *timer , void (*end_fn)(void)){
    timer->end_fn = end_fn;
}

void add_function(Timer *timer,void (*action)(double) , double life_time , double slow_down_factor){
    assert(timer);

    Timer_node *new_timer_node = (Timer_node*) malloc(sizeof(Timer_node));
    new_timer_node->left_time = life_time;
    new_timer_node->time_now = 0;
    new_timer_node->action = action;
    new_timer_node->end_action = NULL;
    new_timer_node->slow_down_factor = slow_down_factor;
    timer->total_time += life_time; 

    enqueue (timer->actions, (void*) new_timer_node);
}
void wait_time(Timer *timer , double time){
    add_function(timer , NULL , time , 1);
}
void set_time_now(Timer *timer , double time_now){
    assert(timer);
    if (timer->end)
    {
        if (!is_q_empty(timer->actions))
        {
            Timer_node *node = (Timer_node*)queue_rear (timer->actions) ;
            node->time_now = time_now;
            // printf("tamam\n");
            
        }
    }
}
void set_end_action(Timer *timer , void (*end_action)()){
    assert(timer);
    if (!is_q_empty(timer->actions))
    {
        Timer_node *node = (Timer_node*)queue_rear (timer->actions) ;
        node->end_action = end_action;
        printf("TIMER: end action set\n");
        
    }
    
}
void play_timer(Timer *timer){
    assert(timer);
    if (!timer->end)
    {
        if (is_q_empty(timer->actions))
        {
            if (timer->end_fn)
            {
                (*timer->end_fn)();
            }
            timer->end = true;
            return;
        }

        Timer_node *node = (Timer_node*)queue_front (timer->actions) ;
        if (node->left_time <= 0 )
        {
            if(node->end_action) {
                (*node->end_action)();
                printf("TIMER: end action executed\n");

            }
            
            node = dequeue(timer->actions);
            free(node);
            if (is_q_empty(timer->actions)){ 
                timer->time_now = 0;
                timer->total_time = 0;
                return;
            }
            node = (Timer_node*)queue_front (timer->actions) ;
        }
        if (node->action)
        {        
            (*(node->action))(node->time_now);
        }
        node->left_time -= 1.0 / (60.0 * node->slow_down_factor);
        node->time_now += 1.0 / (60.0 * node->slow_down_factor);
        timer->time_now += 1.0 / (60.0 * node->slow_down_factor);
        // printf("now = %lf , left = %lf\n" ,node->time_now , node->left_time);
    }
    
}

void free_timer(Timer *timer){
    if (!is_q_empty (timer->actions))
    {    
        for (
            Timer_node * node = (Timer_node *)dequeue(timer->actions); 
            !is_q_empty (timer->actions);
            node = (Timer_node *) dequeue (timer->actions)
        )
        {
            free(node);
        }
    }
    
    free(timer);
}