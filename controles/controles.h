#ifndef CONTROLES_H
#define CONTROLES_H
#include "../raylib.h"
#include "text_box.h"
typedef enum {
    ANGLE_TEXTBOX                         = 0 ,
    V_TEXTBOX                             = 1
} TextboxName;

void init_controler();


void draw_controler();
char *get_text_string(TextboxName name , int * str_len);
void free_controler();


#endif // CONTROLES_H