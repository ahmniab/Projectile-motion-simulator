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
