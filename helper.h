#ifndef HELPER_H
#define HELPER_H
int str_2_pos_int(char int_str[] , int len);
int get_angle();
int get_velocity();
float get_G();
float get_play_factor();
void set_angle_textbox(int angle);
void set_v0_textbox(int v0);
void set_g_textbox(float G);
void set_play_factor_textbox(float factor);
#endif // HELPER_H