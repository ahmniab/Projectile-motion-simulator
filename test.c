#include "raylib.h"
#include <math.h>
#include "movement/timer.h"
#include <stdio.h>

void draw_red_circle(){
    DrawCircle(250, 250, 50, RED);
    // printf("red function\n");
}

void draw_green_circle(){
    DrawCircle(250, 250, 50, GREEN);
    // printf("green function\n");
}


int main(){
    InitWindow(500 , 500, "test");
    SetTargetFPS(60);
    Timer *timer = create_timer();
    add_function(timer,&draw_red_circle , 3 , 1);
    add_function(timer,&draw_green_circle , 4 , 0.2);
    // void (*fn)(void) = &draw_green_circle;
    while (!WindowShouldClose())
    {

        BeginDrawing();
            ClearBackground(RAYWHITE);
            play_timer(timer);
            // (*fn)();
        EndDrawing();
        
    
    }
    free_timer(timer);
    CloseWindow();
}

