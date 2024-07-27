#include "controles.h"
#include <stdio.h>

int str_2_pos_int(char int_str[] , int len){
    if (len == 0 || !int_str) return -1;
    
    for (long i = 0; i < len; i++)
    {
        if(int_str[i] < '0' || int_str[i] > '9') return -1;
    }

    int res = 0;
    int place = 1;
    for (long i = len - 1 ; i >= 0; i--)
    {
        res += (int_str[i] - '0') * place;
        place *= 10;
    }
    return res;
    
    
}
float str_2_pos_float(char float_str[] , int len){

    if (len == 0 || !float_str) return -1;

    bool dot = false;
    for (long i = 0; i < len; i++)
    {
        if (float_str[i] == '.' )
        {
            if (dot)
            {
                return -1;
            }
            dot = true ;
            continue;
            
        }
        
        if(float_str[i] < '0' || float_str[i] > '9') return -1;
    }

    float nm ;
    sscanf(float_str,"%f",&nm);
    return nm;

}

int get_velocity(){
    int v0_str_len;
    char* v0_str = get_text_string(V_TEXTBOX , &v0_str_len);
    int v0 = str_2_pos_int(v0_str , v0_str_len);
    return (v0);
}

int get_angle(){
    int angle_str_len;
    char* angle_str = get_text_string(ANGLE_TEXTBOX , &angle_str_len);
    int angle = str_2_pos_int(angle_str , angle_str_len);

    return (angle >= 0 && angle <= 90 )? angle : -1;
}
float get_G(){
    int G_str_len;
    char* G_str = get_text_string(G_TEXTBOX , &G_str_len);
    float G = str_2_pos_float(G_str , G_str_len);
    return G;
}

float get_play_factor(){
    int sp_str_len;
    char* sp_str = get_text_string(PLAY_TEXTBOX , &sp_str_len);
    float sp = str_2_pos_float(sp_str , sp_str_len);
    return sp;
}


void set_angle_textbox(int angle){
    int len;
    char *str_angle = get_text_string(ANGLE_TEXTBOX , &len);
    sprintf(str_angle , "%d" , angle);

}
void set_v0_textbox(int v0){
    int len;
    char *str_v0 = get_text_string(V_TEXTBOX , &len);
    sprintf(str_v0 , "%d" , v0);

}
void set_g_textbox(float G){
    int len;
    char *str_G = get_text_string(G_TEXTBOX , &len);
    sprintf(str_G , "%.2f" , G);

}

void set_play_factor_textbox(float factor){
    int len;
    char *str_factor = get_text_string(PLAY_TEXTBOX , &len);
    sprintf(str_factor , "%.2f" , factor);

}

int max(int a , int b){
    if (a > b) return a;
    return b;
} 
int min(int a , int b){
    if (a < b) return a;
    return b;
} 

float ease_in(float t) {
    return t * t;
}

float ease_out(float t) {
    return t * (2 - t);
}

Texture2D backgraund;
void init_wallpaper(){
    backgraund = LoadTexture("assets/imgs/wallpaper.png");
}
void draw_wallpaper(){
    DrawTexture(backgraund , 0 , 0 ,WHITE);
}
void free_wallpaper(){
    UnloadTexture(backgraund );
}