#include "controles.h"
#include "../helper.h"
#include "physics/engine.h"
#include "movement.h"
#include "timer.h"
#include "../ffmpeg.h"
// #include "../objs/angle_arrow.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define V_COMPT_PX_LONG 170
// #define RENDER_EVERY_TIME 

bool started = false;
bool render_started = false;
int __ANGLE__ = 45;
int __V0__ = 15;
double __VY__ = 0;
float __G__ = 10;
float __PLAY_SLOWDOWN_FACTOR__ = 1;
const float ballRadius = 3;
World2d physics_world;
float T = 0;
unsigned long long frame_counter = 0;
Vector2 ballPosition = {50.0f , 800.0f};
RenderTexture2D target_world ;
Timer * timer;
Font big_font ;

FFMPEG * ffmpeg;

bool is_started(){
    return started;
}
bool is_render_started(){
    return render_started;
}

void drow_slider(float precent){
    if(precent > 1.0) precent = 1.0;
    Rectangle rec_lines = {10.0f, 1000.0f, 1900.0f, 20.0f};
    // Rectangle rec_slider = {13.0f, 1003.0f, (1900.0f - 6.0f), (20.0f - 0.06f)};


    DrawRectangleLinesEx(rec_lines, 3, WHITE);
    DrawRectangle(13 ,  1003, (int)((1900 - 6 ) * precent), 20 - 6, WHITE);
    // DrawRectangleLines(10, 1000, 1900, 20, BLUE);
}

void rendering_screen(void)
{
    int w = SCREEN_W;
    int h = SCREEN_H;

    if (ffmpeg == NULL) { // Starting FFmpeg process has failed for some reason
        if (IsKeyPressed(KEY_ENTER)) {
            render_started = false;
        }

        const char *label = "FFmpeg Failure: Check the Logs";
        Color color = RED;
        int fontSize = 70;
        Vector2 size = MeasureTextEx(big_font, label, fontSize, 0);
        Vector2 position = {
            w/2 - size.x/2,
            h/2 - size.y/2,
        };
        DrawTextEx(big_font, label, position, fontSize, 0, color);

        label = "(Press ENTER to Continue)";
        fontSize = 70*2/3;
        size = MeasureTextEx(big_font, label, fontSize, 0);
        position.x = w/2 - size.x/2,
        position.y = h/2 - size.y/2 + fontSize,
        DrawTextEx(big_font, label, position, fontSize, 0, color);
    } else { // FFmpeg process is going
        ClearBackground((Color){ 13, 13, 13, 255 });
        DrawTextEx(big_font , "Rendering...",(Vector2){.x = SCREEN_W / 2 - 100 , .y= SCREEN_H / 2 -100},70,1,WHITE);

        drow_slider(timer->time_now / timer->total_time);
    }
}


void init_components(){
    init_ball();
    
    init_controler();
    set_angle_textbox(__ANGLE__);
    set_v0_textbox(__V0__);
    set_g_textbox(__G__);
    set_play_factor_textbox(__PLAY_SLOWDOWN_FACTOR__);

    physics_world = new_world_2d(__V0__ , __G__ , (double)__ANGLE__,GROUND_LEVEL , 70);
    add_obj(physics_world , BALL_X, BALL_Y);
    target_world = LoadRenderTexture(SCREEN_W, SCREEN_H);

    timer = create_timer();
    big_font = LoadFontEx("assets/fonts/Montserrat_MediumItalic.ttf", 70, NULL,0);
}

void draw_v_component(int angle){
    Vector2 start_pos;
    start_pos.x = ballPosition.x + (512 * 0.2)/2;
    start_pos.y = ballPosition.y + (512 * 0.2)/2;

    Vector2 end_pos;
    
    end_pos.x = start_pos.x + V_COMPT_PX_LONG * cos(deg2rad_(angle));
    end_pos.y = start_pos.y - V_COMPT_PX_LONG * sin(deg2rad_(angle));

    
    DrawLineEx(start_pos, end_pos, 2, WHITE); // main line
    
    switch (angle)
    {
    case 0:
        start_pos.x = end_pos.x - 15;
        start_pos.y = end_pos.y - 15;
        DrawLineEx(end_pos,start_pos , 2, WHITE);
        start_pos.y = end_pos.y + 15;
        DrawLineEx(end_pos, start_pos, 2, WHITE);
        break;
    case 90 :
        start_pos.y = end_pos.y + 15;
        start_pos.x = end_pos.x - 15;
        DrawLineEx(end_pos,start_pos , 2, WHITE);
        start_pos.x = end_pos.x + 15;
        DrawLineEx(end_pos, start_pos, 2, WHITE);
        break;
    case 270 :
        start_pos.y = end_pos.y - 15;
        start_pos.x = end_pos.x - 15;
        DrawLineEx(end_pos,start_pos , 2, WHITE);
        start_pos.x = end_pos.x + 15;
        DrawLineEx(end_pos, start_pos, 2, WHITE);
        break;
    
    }

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

void draw_mx_heigt_from_ground_animi(double time){
    draw_ball_path();
    draw_all_info(max_th(physics_world));
    double life_time = 2;
    if (time > life_time) time = life_time;
    
    Vector2 end_pos  = new_coordinats(physics_world , max_th(physics_world));
    end_pos.x  += (512*0.2)/2 - 3 ;
    end_pos.y  = physics_world->ground_level;
    end_pos.y -= max_h(physics_world) *(time / life_time) ;
    Vector2 start_pos ;
    start_pos.x = end_pos.x;
    start_pos.y = physics_world->ground_level;
    DrawLineEx(start_pos , end_pos , 2 , WHITE);
}
void draw_mx_heigt_from_ground(double time){
    draw_ball_path();
    draw_all_info(max_th(physics_world));

    Vector2 end_pos  = new_coordinats(physics_world , max_th(physics_world));
    end_pos.x  += (512*0.2)/2 - 3 ;
    end_pos.y  += (512*0.2);
    Vector2 start_pos ;
    start_pos.x = end_pos.x;
    start_pos.y = physics_world->ground_level;
    DrawLineEx(start_pos , end_pos , 2 , WHITE);
    start_pos.y -= (max_h(physics_world) - (512*0.2)) *(0.5) + 20 ;
    start_pos.x += 20; 
    DrawTextEx(get_font() , TextFormat("%.1f M",max_h(physics_world)/physics_world->meter_in_screan),start_pos,25,1,WHITE);

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

    if(!render_started) draw_line_mx_height();
    
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
Image get_world_image_flipped()
{
    Image world_image = LoadImageFromTexture(target_world.texture);
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

void handle_world_values(){
    if (!started)
    {
        
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

        float factor = get_play_factor();
        if (factor != -1.0f)
        {
            __PLAY_SLOWDOWN_FACTOR__ = factor;
        }
        
    }
}


void reset_world_position(){
    ballPosition = (Vector2){50.0f , 800.0f};
    started = false;
    render_started = false;
    __VY__ = 0 ;
    printf ("INFO:TRY FFMPEG ENDED \n");
    if(ffmpeg_end_rendering(ffmpeg)) printf ("INFO:FFMPEG ENDED \n");
    printf ("INFO:SKIPPED FFMPEG ENDED \n");
    ffmpeg = NULL;
}

void draw_v0(double time){
    Vector2 pos = {100 , 20};
    DrawTextEx(get_font() , TextFormat("V0 = %d" , __V0__) ,pos,35,1,WHITE);
}

void draw_g(double time){
    draw_v0(0);
    Vector2 pos = {100 , 50};
    DrawTextEx(get_font() , TextFormat("G = %.1f" , __G__) ,pos,35,1,WHITE);
}
void draw_all_info(float time){
    draw_g(0);
    Vector2 pos = {100 , 80};
    DrawTextEx(get_font() , TextFormat("vx = %.2f" , vx(physics_world , time)) ,pos,35,1,WHITE);
    pos.y = 110;
    DrawTextEx(get_font() , TextFormat("vy = %.2f" , vy(physics_world , time)) ,pos,35,1,WHITE);
}
void update_ball_position(double time){
    ballPosition =  new_coordinats(physics_world, (float)time ); 
    draw_all_info(time);
    __VY__ = vy(physics_world , time) ;
    draw_ball_path();
    

}
void draw_ball_path_in_time(double time){
    draw_g(0);
    float end_time = 2;
    if (time > end_time) time = end_time;
    
    float time2stop = 2*max_th(physics_world) * (time / end_time);
    for (float t = 0; t < time2stop; t += 0.05)
    {
        Vector2 ballPosition =  new_coordinats(physics_world, t  );
        ballPosition.x += 50.9f;
        ballPosition.y += 50.9f;
        DrawCircleV(ballPosition, ballRadius, MAROON);
    }
}

void handle_keyboard(){
    if (IsKeyPressed(KEY_SPACE)) {
        if (started)
        {
            started = false;
            return;
        }else if (timer->end)
        {
            add_function(timer , &update_ball_position , 2 * max_th(physics_world) ,__PLAY_SLOWDOWN_FACTOR__ );
            set_end_fn(timer , &reset_world_position);
            wait_time(timer , 0.5);

            start_timer(timer);
        }
        
        started = true;
        
        
    }
    if (IsKeyPressed(KEY_F)) {
        ToggleFullscreen();
    }
    if ((IsKeyDown(KEY_RIGHT_CONTROL) || IsKeyDown(KEY_LEFT_CONTROL)) && IsKeyDown(KEY_R)) {

        // printf("key r pressed\n");
        if (!render_started)
        {
            set_end_fn(timer , &reset_world_position);
            // printf("rende = %d\n",render_started);
            // add_function(timer , &draw_v0 , 0.3 ,1 );
            add_function(timer , &draw_g , 1.5 ,1 );
            add_function(timer , &draw_ball_path_in_time , 2 ,1 );
            add_function(timer , &update_ball_position , max_th(physics_world) ,__PLAY_SLOWDOWN_FACTOR__ );
            add_function(timer , &draw_mx_heigt_from_ground_animi , 2 ,1 );
            add_function(timer , &draw_mx_heigt_from_ground , 1 ,1 );
            add_function(timer , &update_ball_position , max_th(physics_world) ,__PLAY_SLOWDOWN_FACTOR__ );
            set_time_now(timer , max_th(physics_world) );
            // add_function(timer , &draw_ball_path , max_th(physics_world) ,__PLAY_SLOWDOWN_FACTOR__ );
            wait_time(timer , 1);
            start_timer(timer);
            ffmpeg = ffmpeg_start_rendering(SCREEN_W , SCREEN_H ,60 , TextFormat("out/G-%f_V0-%d.mp4",__G__,__V0__) );
            render_started = true;
        }
        
    }
    
}

void drow_objs(){
    handle_keyboard();
    handle_world_values();

    BeginTextureMode(target_world);
        ClearBackground((Color){ 13, 13, 13, 255 });
        
        if (started || render_started)
        {
            play_timer(timer);
        }
        drow_world_height();
        drow_world_width();
        
        
        if (render_started)
        {
            draw_v_component(0);
            if (__VY__ >= 0)
            {
                draw_v_component(90);
            }else
            {
                draw_v_component(270);
            }
        }
        draw_ball(ballPosition.x , ballPosition.y);
        
        if(!render_started) draw_ball_path();
        EndTextureMode();

    

    #ifdef RENDER_EVERY_TIME
        static int sn = 0;
        if (started || render_started)
        {
            take_screenshot(TextFormat("screen/%05d.png",sn++));
        }
    #endif
    if(!render_started) drow_target_world();
    #ifdef DEVELOPER_MOOD 
        if(IsKeyPressed(KEY_S)){
            take_screenshot("screenshot.png");
        }

    #else
        if(render_started){
            Image image = get_world_image_flipped();
            if (!ffmpeg_send_frame_flipped(ffmpeg, image.data, image.width, image.height)) {
                // NOTE: we don't check the result of ffmpeg_end_rendering here because we
                // don't care at this point: writing a frame failed, so something went completely
                // wrong. So let's just show to the user the "FFmpeg Failure" screen. ffmpeg_end_rendering
                // should log any additional errors anyway.
                ffmpeg_end_rendering(ffmpeg);
                ffmpeg = NULL;
            }
            UnloadImage(image);
        }
    #endif
}

void free_components(){
    unload_ball();
    free_world2d(physics_world);
    UnloadRenderTexture(target_world);
    free_timer(timer);
    UnloadFont(big_font);
}
