#include "controles.h"
#include "../helper.h"
#include "physics/engine.h"
#include "movement.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


bool started = false;
int __ANGLE__ = 45;
int __V0__ = 15;
float __G__ = 10;
const float ballRadius = 3;
World2d physics_world;
float T = 0;
unsigned long long frame_counter = 0;
Vector2 ballPosition = {50.0f , 800.0f};
RenderTexture2D target_world ;

void init_components(){
    init_ball();
    
    init_controler();
    set_angle_textbox(__ANGLE__);
    set_v0_textbox(__V0__);
    set_g_textbox(__G__);

    physics_world = new_world_2d(__V0__ , __G__ , (double)__ANGLE__,GROUND_LEVEL , 70);
    add_obj(physics_world , BALL_X, BALL_Y);
    target_world = LoadRenderTexture(SCREEN_W, SCREEN_H);
}

void draw_line_mx_height(){
    Vector2 max_pos = max_coordinats(physics_world);
    Vector2 line_start_pos = {0 , 0};
    line_start_pos.y = max_pos.y + 102.4f;
    Vector2 line_end_pos = {SCREEN_W,0};
    line_end_pos.y = max_pos.y + 102.4f;
    DrawLineEx(line_start_pos , line_end_pos , 1 , (Color){ 255, 255, 255, 100});

    line_start_pos.x +=50;
    line_start_pos.y -=30;
    DrawTextEx(get_font() , TextFormat("%.1f M",max_h(physics_world)/physics_world->meter_in_screan),line_start_pos,25,1,WHITE);
}

void drow_world_height(){
    Vector2 end_pos = (Vector2){0 , SCREEN_H};
    end_pos.y -= (SCREEN_H - physics_world->ground_level);
    DrawLineEx((Vector2){0 , 0} , end_pos , 10 , WHITE);
    for (long long px = end_pos.y - physics_world->meter_in_screan , m = 1; px > 0; px -= physics_world->meter_in_screan , m++)
    {
        DrawRectangle(0+4, px, 8, 4, WHITE);  
        char meters[20];
        sprintf(meters , "%lld",m) ;
        Vector2 pos = {20 , 0};
        pos.y = px -5;
        DrawTextEx(get_font(), meters,pos, 15,1, WHITE);
    }
    draw_line_mx_height();
    
}
void drow_world_width(){
    Vector2 start_pos =  {0 , GROUND_LEVEL };
    Vector2 end_pos =  {SCREEN_W , GROUND_LEVEL };
    DrawLineEx(start_pos, end_pos, 5, WHITE);

    for (long long px = physics_world->meter_in_screan , m = 1; px < SCREEN_W; px += physics_world->meter_in_screan , m++)
    {
        DrawRectangle(px, start_pos.y, 4, 8, WHITE); 
        char meters[20];
        sprintf(meters , "%lld",m) ;
        Vector2 text_pos ;
        text_pos.x = px - 5 ;
        text_pos.y = start_pos.y + 13;
        DrawTextEx(get_font(), meters,text_pos, 15,1, WHITE);
    }
    
}


int get_working_angle(){
    return __ANGLE__;
}



Image get_world_image()
{
    Image world_image = LoadImageFromTexture(target_world.texture);
    ImageFlipVertical(&world_image);
    return world_image;
}

void take_screenshot(const char * file_name){
    Image screenshot = get_world_image();
    ExportImage(screenshot, file_name);
    UnloadImage(screenshot);
}

void draw_ball_path(){
    float time2stop = 2*max_th(physics_world); 
    for (float t = 0; t < time2stop; t += 0.05)
    {
        Vector2 ballPosition =  new_coordinats(physics_world, t  );
        ballPosition.x += 50.9f;
        ballPosition.y += 50.9f;
        DrawCircleV(ballPosition, ballRadius, MAROON);
    }
}

void drow_target_world(){
    Rectangle source = { 0.0f, 0.0f, (float)target_world.texture.width, -(float)target_world.texture.height };
    Rectangle dest = { 0.0f, 0.0f, (float)target_world.texture.width, (float)target_world.texture.height };
    Vector2 origin = { 0.0f, 0.0f };

    // Draw the render texture to the screen, flipping it vertically
    DrawTexturePro(target_world.texture, source, dest, origin, 0.0f, WHITE);

}

float final_time = -1.0f;
void drow_objs(){
    BeginTextureMode(target_world);
        ClearBackground((Color){ 13, 13, 13, 255 });
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

            int v0 = get_velocity();
            if (v0 != -1)
            {
                __V0__ = v0;
                set_v0(physics_world , __V0__);
            }
            
            float G = get_G();
            if (G != -1.0f)
            {
                __G__ = G;
                set_G(physics_world , __G__);
            }
            
        }else{
            frame_counter++;
            T = frame_counter/60.0f;
            ballPosition =  new_coordinats(physics_world, T );
            const char* info = TextFormat("frame conter = %d\n\ntime = %ds\n\n final time = %.2f\n\n( %.3f , %.3f )", frame_counter , (int)T, final_time , ballPosition.x , ballPosition.y);
            DrawText(info, 700, 10, 30, WHITE);
            if ((int)ballPosition.y >= 800 && frame_counter > 1 )
            {
                if (final_time == -1.0f) final_time = T - ((frame_counter - 1)/60.0f);
                
                ballPosition =  new_coordinats(physics_world, final_time );
            }
            
            

        }
        drow_world_height();
        drow_world_width();
        draw_ball(ballPosition.x , ballPosition.y);
        draw_ball_path();
        
        // if(ballPosition.x == 50.0f) draw_angle_arrow(__ANGLE__);
    EndTextureMode();

    #ifdef RENDER_EVERY_TIME
        static int sn = 0;
        if (started)
        {
            take_screenshot(TextFormat("screen/%05d.png",sn++));
        }
    #endif

    drow_target_world();
    if(IsKeyPressed(KEY_S)){
        take_screenshot("screenshot.png");
    }
}

void free_components(){
    unload_ball();
    free_world2d(physics_world);
    UnloadRenderTexture(target_world);
}
