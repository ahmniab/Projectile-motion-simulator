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
#include "../objs/values_board.h"


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
double ball_time_now = 0;
unsigned long long frame_counter = 0;
Vector2 ballPosition = {50.0f , 800.0f};
RenderTexture2D target_world ;
RenderTexture2D sup_world ;
Timer * timer;
Font big_font ;
bool is_offset_set = false;

FFMPEG * ffmpeg;
Camera2D camera = { 0 };

void zoom_in(double time ){
    // printf("zm vy = %f\n",__VY__);
    // __VY__ = 0;
    // printf("zm vy = %f\n",__VY__);
    #define zoom_in_duration 1.5
    draw_v_components();
    if (time < zoom_in_duration) {
            float t = time / zoom_in_duration; // Normalized time (0.0 to 1.0)
            camera.zoom = 1.0 + (2.0 - 1.0) * ease_in(t);
    } else {
        camera.zoom = 2.0; // Ensure the zoom level reaches the end value
    }
}
void zoom_out(double time ){
    draw_v_component(0,WHITE);
    draw_v_component(270,WHITE);
    
    #define zoom_out_duration 1.5
    if (time < zoom_out_duration) {
            float t = time / zoom_out_duration; // Normalized time (0.0 to 1.0)
            camera.zoom = 2.0 + (1.0 - 2.0) * ease_out(t);
    } else {
        camera.zoom = 2.0; // Ensure the zoom level reaches the end value
    }
}


void reset_cam(){
    // camera.target = (Vector2){ ballPosition.x + (512*0.2f)/2.0, ballPosition.y + (512*0.2f)/2.0 };
    // camera.offset = (Vector2){ 100, physics_world->ground_level - 44 };
    camera.target = (Vector2){ SCREEN_W/2, SCREEN_H/2 };
    camera.offset = (Vector2){ SCREEN_W/2, SCREEN_H/2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    is_offset_set = false;
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
    sup_world = LoadRenderTexture(SCREEN_W, SCREEN_H);

    timer = create_timer();
    big_font = LoadFontEx("assets/fonts/Montserrat_MediumItalic.ttf", 70, NULL,0);
    reset_cam();
    init_values_board();
}

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
        #ifndef DEVELOPER_MOOD
        ClearBackground((Color){ 13, 13, 13, 255 });
        #endif
        DrawTextEx(big_font , "Rendering...",(Vector2){.x = SCREEN_W / 2 - 100 , .y= SCREEN_H / 2 -100},70,1,WHITE);

        drow_slider(timer->time_now / timer->total_time);
    }
}



void draw_v_component(int angle  , Color v_col){
    Vector2 start_pos;
    start_pos.x = ballPosition.x + (512 * 0.2)/2;
    start_pos.y = ballPosition.y + (512 * 0.2)/2;

    Vector2 end_pos;
    
    end_pos.x = start_pos.x + V_COMPT_PX_LONG * cos(deg2rad_(angle));
    end_pos.y = start_pos.y - V_COMPT_PX_LONG * sin(deg2rad_(angle));

    
    DrawLineEx(start_pos, end_pos, 2, v_col); // main line

    #define ARR_DIFF 5
    
    switch (angle)
    {
    case 0:
        start_pos.x = end_pos.x - ARR_DIFF;
        start_pos.y = end_pos.y - ARR_DIFF;
        DrawLineEx(end_pos,start_pos , 2, v_col);
        start_pos.y = end_pos.y + ARR_DIFF;
        DrawLineEx(end_pos, start_pos, 2, v_col);
        break;
    case 90 :
        start_pos.y = end_pos.y + ARR_DIFF;
        start_pos.x = end_pos.x - ARR_DIFF;
        DrawLineEx(end_pos,start_pos , 2, v_col);
        start_pos.x = end_pos.x + ARR_DIFF;
        DrawLineEx(end_pos, start_pos, 2, v_col);
        break;
    case 270 :
        start_pos.y = end_pos.y - ARR_DIFF;
        start_pos.x = end_pos.x - ARR_DIFF;
        DrawLineEx(end_pos,start_pos , 2, v_col);
        start_pos.x = end_pos.x + ARR_DIFF;
        DrawLineEx(end_pos, start_pos, 2, v_col);
        break;
    
    }

}
void draw_v_components(){
    draw_v_component(0,WHITE);
    if (__VY__ >= 0)
    {
        draw_v_component(90,WHITE);
    }else
    {
        draw_v_component(270,WHITE);
    }
}
void change_component_dirction(double time){
    draw_v_component(0,WHITE);
    draw_v_component(90 - (180 * (time / 2.0)) , RED);
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

void draw_mx_distance_animi(double time){
    // draw_ball_path();
    double life_time = 2;
    if (time > life_time) time = life_time;
    
    Vector2 end_pos = {50.0f,0};// = new_coordinats(physics_world , 2*max_th(physics_world));
    end_pos.x  += (mx_d(physics_world) * physics_world->meter_in_screan) * (time / life_time) ;
    // printf("INFO: endpos.x = %.1lf\nmx d = %.1f\n",end_pos.x, mx_d(physics_world));
    end_pos.y  = physics_world->ground_level - max_h(physics_world) + (512*0.2f);
    Vector2 start_pos ;

    start_pos.x = 50.0f;
    start_pos.y = physics_world->ground_level - max_h(physics_world) + (512*0.2f);
    DrawLineEx(start_pos , end_pos , 2 , WHITE);
}
void draw_mx_heigt_from_ground_animi(double time){
    draw_ball_path();
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

void draw_mx_dims_animi(double time){
    draw_mx_heigt_from_ground_animi(time);
    draw_mx_distance_animi(time);
}
void draw_mx_heigt_from_ground(double time){
    draw_ball_path();

    Vector2 end_pos  = new_coordinats(physics_world , max_th(physics_world));
    end_pos.x  += (512*0.2)/2 - 3 ;
    end_pos.y  += (512*0.2);
    Vector2 start_pos ;
    start_pos.x = end_pos.x;
    start_pos.y = physics_world->ground_level;
    DrawLineEx(start_pos , end_pos , 2 , WHITE);
    start_pos.y -= (max_h(physics_world) - (512*0.2)) *(0.5) + 20 ;
    start_pos.x += 20; 
    DrawTextEx(big_font , TextFormat("%.1f M",max_h(physics_world)/physics_world->meter_in_screan),start_pos,25,1,WHITE);

}
void draw_mx_distance(double time){
    // draw_ball_path();
    double life_time = 2;
    if (time > life_time) time = life_time;
    
    Vector2 end_pos = {50.0f,0};// = new_coordinats(physics_world , 2*max_th(physics_world));
    end_pos.x  += (mx_d(physics_world) * physics_world->meter_in_screan)  ;
    // printf("INFO: endpos.x = %.1lf\nmx d = %.1f\n",end_pos.x, mx_d(physics_world));
    end_pos.y  = physics_world->ground_level - max_h(physics_world) + (512*0.2f);
    Vector2 start_pos ;

    start_pos.x = 50.0f;
    start_pos.y = physics_world->ground_level - max_h(physics_world) + (512*0.2f);
    DrawLineEx(start_pos , end_pos , 2 , WHITE);
    end_pos.x -= 150;
    end_pos.y += 50;
    DrawTextEx(big_font , TextFormat("%.1f M",mx_d(physics_world)),end_pos,25,1,WHITE);
}
void draw_mx_dims(double time){
    draw_mx_distance(time);
    draw_mx_heigt_from_ground(time);
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

void drow_texture2d_world(RenderTexture2D tex_world){
    Rectangle source = { 0.0f, 0.0f, (float)tex_world.texture.width, -(float)tex_world.texture.height };
    Rectangle dest = { 0.0f, 0.0f, (float)tex_world.texture.width, (float)tex_world.texture.height };
    Vector2 origin = { 0.0f, 0.0f };

    // Draw the render texture to the screen, flipping it vertically
    DrawTexturePro(tex_world.texture, source, dest, origin, 0.0f, WHITE);

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
    if(ffmpeg && ffmpeg_end_rendering(ffmpeg)) printf ("INFO:FFMPEG ENDED \n");
    printf ("INFO:SKIPPED FFMPEG ENDED \n");
    ffmpeg = NULL;
    reset_cam();
   ball_time_now = 0;

}

void draw_values_board_start(double time){
    draw_board(__G__ , __V0__ , (int)__ANGLE__ , big_font , time/1.0);
}
void draw_values_board(double time){
    draw_board(__G__ , __V0__ , (int)__ANGLE__ , big_font , 1.0);
}
void draw_values_board_end(double time){
    draw_board(__G__ , __V0__ , (int)__ANGLE__ , big_font , (1.0-time)/1.0);
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
    DrawTextEx(get_font() , TextFormat("vy = %.2f" , __VY__) ,pos,35,1,WHITE);
}
void update_ball_position(double time){
    ballPosition =  new_coordinats(physics_world, (float)time ); 
    __VY__ = vy(physics_world , time) ;
    ball_time_now = time;
    draw_ball_path();
    if(get_checkbox_value(COMPONENTS_CHECKBOX)) draw_v_components();

}
void draw_ball_path_in_time(double time){
    // draw_g(0);
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

void draw_max_w_h(double time){
    draw_mx_heigt_from_ground_animi(time);

}

void set_vy_0(){
    // printf("vy = %f\n",__VY__);
    __VY__ = 0 ;
    // printf("vy = %f\n",__VY__);
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

        if (!render_started)
        {
            set_end_fn(timer , &reset_world_position);
            // printf("rende = %d\n",render_started);
            // add_function(timer , &draw_v0 , 0.3 ,1 );
            wait_time(timer , 0.5);
            add_function(timer , &draw_values_board_start , 1 ,1 );
            add_function(timer , &draw_values_board , 2 ,1 );
            add_function(timer , &draw_values_board_end , 1 ,1 );
            add_function(timer , &draw_ball_path_in_time , 2 ,1 );
            add_function(timer , &update_ball_position , max_th(physics_world) ,__PLAY_SLOWDOWN_FACTOR__ );
            set_end_action(timer , &set_vy_0);
            
            add_function(timer , &zoom_in , 1.5 ,1 );

            add_function(timer , &change_component_dirction , 2 ,1 );
            add_function(timer , &zoom_out , 1.5 ,1 );

            add_function(timer , &update_ball_position , max_th(physics_world) ,__PLAY_SLOWDOWN_FACTOR__ );
            set_time_now(timer , max_th(physics_world) );
            add_function(timer , &draw_mx_dims_animi , 2 ,1 );
            add_function(timer , &draw_mx_dims , 1 ,3 );
            wait_time(timer , 1);
            start_timer(timer);
            #ifndef PREVIEW_MOOD
                ffmpeg = ffmpeg_start_rendering(SCREEN_W , SCREEN_H ,60 , TextFormat("out/G_is-%.2f_V0_is-%d_angle_is-%d_slow_is_%.1f.mp4",__G__,__V0__,__ANGLE__ ,__PLAY_SLOWDOWN_FACTOR__ ) );
            #endif
            render_started = true;
        }
        
    }
    
}
void render_sup_world(){
    #ifdef DEVELOPER_MOOD
        // Camera zoom controls
        camera.zoom += ((float)GetMouseWheelMove()*0.05f);
        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;
    #endif
    if ((render_started || started))
    {
        // camera.offset = (Vector2){ SCREEN_W /2, SCREEN_H/2 };
        camera.target = (Vector2){ ballPosition.x + (512*0.2f)/2.0, ballPosition.y + (512*0.2f)/2.0 };
        
        if (((ballPosition.x > SCREEN_W - 200) || (ballPosition.y < 200 )) && !is_offset_set)
        {
            camera.offset = (Vector2){ ballPosition.x + (512*0.2f)/2.0, ballPosition.y + (512*0.2f)/2.0 };
            is_offset_set = true;
        }
        else {
            if(!is_offset_set)camera.offset = (Vector2){ ballPosition.x + (512*0.2f)/2.0, ballPosition.y + (512*0.2f)/2.0 };
        }

    }else{

        // camera.zoom = 1.0f;

    }
    
    BeginTextureMode(sup_world);
        ClearBackground((Color){ 13, 13, 13, 255 });
        BeginMode2D(camera);
            
            if (started || render_started)
            {
                play_timer(timer);
            }
            
            
            if (render_started && get_checkbox_value(COMPONENTS_CHECKBOX))
            {
                draw_v_components();
            }
            draw_ball(ballPosition.x , ballPosition.y);
            
            if(!render_started) draw_ball_path();

            drow_world_height();
            drow_world_width();
        EndMode2D();
    EndTextureMode();
}

void drow_objs(){
    handle_keyboard();
    handle_world_values();
    
    
    

    render_sup_world();
    BeginTextureMode(target_world);
        ClearBackground((Color){ 13, 13, 13, 255 });
        drow_texture2d_world(sup_world);
        if(ball_time_now != 0.0f) draw_all_info(ball_time_now);
    EndTextureMode();

    

    #ifdef RENDER_EVERY_TIME
        static int sn = 0;
        if (started || render_started)
        {
            take_screenshot(TextFormat("screen/%05d.png",sn++));
        }
    #endif
    #ifdef DEVELOPER_MOOD 
        drow_texture2d_world(target_world);
        if(IsKeyPressed(KEY_S)){
            take_screenshot("screenshot.png");
        }

        // if(!render_started) {
        //     camera.zoom = SCREEN_W / (float)max(SCREEN_W , (int)mx_d(physics_world) * physics_world->meter_in_screan);
        //     printf(TextFormat("INFO:ZOOM FACTOR = %f , max d = %.0f\n" ,camera.zoom , mx_d(physics_world)));
        // }
    #else
        if(!render_started) {
            // camera.zoom = SCREEN_W / (float)max(SCREEN_W , (int)mx_d(physics_world));
            // printf(TextFormat("INFO:ZOOM FACTOR = %f , max d = %.0f\n" ,camera.zoom , mx_d(physics_world)));
            drow_texture2d_world(target_world);
        }
    #endif
    #ifndef PREVIEW_MOOD
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
    UnloadRenderTexture(sup_world);
    free_timer(timer);
    UnloadFont(big_font);
    if (ffmpeg)
    {
        ffmpeg_end_rendering(ffmpeg);
        ffmpeg = NULL;
    }
    free_board();
    
}
