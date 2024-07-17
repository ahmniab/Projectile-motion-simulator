#ifndef CONTROLES_H
#define CONTROLES_H
#include "../raylib.h"
#include "text_box.h"
typedef enum {
    ANGLE_TEXTBOX                         = 0 ,
    V_TEXTBOX                             = 1 ,
    G_TEXTBOX                             = 2 ,
    PLAY_TEXTBOX                          = 3
} TextboxName;

void init_controler();


void draw_controler();
char *get_text_string(TextboxName name , int * str_len);
Font get_font();
void free_controler();


#endif // CONTROLES_H