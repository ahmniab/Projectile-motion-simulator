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
typedef enum {
    COMPONENTS_CHECKBOX                         = 0 
} CheckboxName;

void init_controler();


void draw_controler();
char *get_text_string(TextboxName name , int * str_len);
bool get_checkbox_value(CheckboxName chbx);
Font get_font();
void free_controler();


#endif // CONTROLES_H