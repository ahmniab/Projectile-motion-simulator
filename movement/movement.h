#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "../raylib.h"
#include "ball.h"
#include "angle_arrow.h"
#include "text_box.h"

#define SCREEN_H 1080
#define SCREEN_W 1920
#define GROUND_LEVEL 896
// #define DEVELOPER_MOOD
// #define PREVIEW_MOOD


void init_components();
void drow_objs();
bool is_started();
bool is_render_started();
void draw_all_info(float time);
void draw_ball_path();
void rendering_screen(void);
Image get_world_image();
void free_components();
int get_working_angle();
void draw_v_component(int angle  , Color v_col);
void draw_v_components();

#endif //MOVEMENT_H