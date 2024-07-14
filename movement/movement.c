#include "controles.h"
#include "../helper.h"
#include "physics/engine.h"
#include "movement.h"

bool started = false;
int __ANGLE__ = 45;
const float ballRadius = 3;
World2d physics_world;
float T = 0;
unsigned long long frame_counter = 0;
Vector2 ballPosition = {50.0f , 800.0f};


void init_components(){
    init_ball();
    init_angle_arrow();
    init_controler();
    set_angle_textbox(__ANGLE__);

    physics_world = new_world_2d(20 , 10 , (double)__ANGLE__,GROUND_LEVEL , 5);
    add_obj(physics_world , BALL_X, BALL_Y);
}

void draw_ball_path(){

    for (float t = 0; t < 20; t += 0.3)
    {
        Vector2 ballPosition =  new_coordinats(physics_world, t  );
        ballPosition.x += 50.9f;
        ballPosition.y += 50.9f;
        DrawCircleV(ballPosition, ballRadius, MAROON);
    }
}

float final_time = -1.0f;
void drow_objs(){
    if (IsKeyPressed(KEY_SPACE)) started = !started;
    
    if (!started)
    {
        if (final_time != -1)
        {
            final_time = -1;
            T=0;
            frame_counter = 0;
            ballPosition = (Vector2){50.0f , 800.0f};
        }
        
        int angle = get_angle();
        if (angle != -1)
        {
            __ANGLE__ = angle;
            set_angle(physics_world , (double)angle);
        }
    }else{
        frame_counter++;
        T += frame_counter/840.0f;
        ballPosition =  new_coordinats(physics_world, T );
        DrawText(TextFormat("frame conter = %d\ntime = %ds\n final time = %.2f\n( %.3f , %.3f )", frame_counter , (int)T, final_time , ballPosition.x , ballPosition.y), 10, 10, 20, WHITE);
        if ((int)ballPosition.y >= 800 && frame_counter > 1 )
        {
            if (final_time == -1.0f) final_time = T - ((frame_counter - 1)/1680.0f);
            
            ballPosition =  new_coordinats(physics_world, final_time );
        }
        

    }
    

    draw_ball(ballPosition.x , ballPosition.y);
    draw_ball_path();
    DrawLineEx((Vector2) {0 , GROUND_LEVEL }, (Vector2) {SCREEN_W , GROUND_LEVEL }, 2, GRAY);
        if(IsKeyPressed(KEY_S)){
                Image screen = GetScreenData();
                ExportImage(screen, "resources/part_screenshot.png");
                UnloadImage(screen);
        }
    if(ballPosition.x == 50.0f) draw_angle_arrow(__ANGLE__);
}

void free_components(){
    unload_ball();
    unload_angle_arrow();
    free_world2d(physics_world);
}
