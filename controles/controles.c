#include "controles.h"
#include "../objs/angle_arrow.h"
#include "../movement/movement.h"
#include "checkbox.h"
#include <stddef.h>
#define TEXT_BOX_NUM 4
#define CHECKBOX_NUM 1
#define size_t unsigned long

char  text_array[TEXT_BOX_NUM][50] = {
    "Angle (deg)",
    "Velocity (m/s)" ,
    "Gravity (m/(s*s))" ,
    "Play Slowdown Factor"
};

Text_box *text_boxes[TEXT_BOX_NUM];   
Checkbox *checkboxes[CHECKBOX_NUM];
Font main_font ;


void init_controler(){
    main_font = LoadFontEx("assets/fonts/Montserrat_MediumItalic.ttf" , 70 , NULL , 0); 

    text_boxes[ANGLE_TEXTBOX] = create_new_text_box(2 ,&main_font ,20,1,PURPLE,PURPLE,RED ,BLACK, 10 , 940 ,300 , 40);
    text_boxes[V_TEXTBOX] = create_new_text_box(5 ,&main_font ,20,1,PURPLE,PURPLE,RED ,BLACK, 350 , 940 ,300 , 40);
    text_boxes[G_TEXTBOX] = create_new_text_box(5 ,&main_font ,20,1,PURPLE,PURPLE,RED ,BLACK, 690 , 940 ,300 , 40);
    text_boxes[PLAY_TEXTBOX] = create_new_text_box(5 ,&main_font ,20,1,PURPLE,PURPLE,RED ,BLACK, 1030 , 940 ,300 , 40);
    
    checkboxes[COMPONENTS_CHECKBOX] = init_checkbox(1470 , 940 ,"Draw vx vy components" ,true , &main_font);
    init_angle_arrow();
}
Font get_font(){
    return main_font;
}
bool mouse_on_textbox(){
    for (size_t i = 0; i < TEXT_BOX_NUM; i++)
    {
        if (text_boxes[i]->mouseOnText)
        {
            return true;
        }
        
    }
    return false;
    
}

void draw_controler(){
    
    for (size_t i = 0; i < TEXT_BOX_NUM; i++)
    {
        draw_text_box(text_boxes[i]);
        
        Vector2 text_position;
        text_position.x = text_boxes[i]->textbox_rectangle.x +10;
        text_position.y = text_boxes[i]->textbox_rectangle.y + 50;

        DrawTextEx(main_font, text_array[i], text_position, 30, 1, WHITE);
        
    }
    if (mouse_on_textbox())
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
    }else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    
    if(!(is_started() || is_render_started())) draw_angle_arrow(get_working_angle());

    for (size_t i = 0; i < CHECKBOX_NUM; i++)
    {
        draw_check_box(checkboxes[i]);
    }

}

char *get_text_string(TextboxName name , int * str_len){
    *str_len = text_boxes[name]->len;
    return text_boxes[name]->buff;
}

bool get_checkbox_value(CheckboxName chbx){
    return checkboxes[chbx]->value;
}

void free_controler(){
    for (size_t i = 0; i < TEXT_BOX_NUM; i++)
    {
        free_text_box(text_boxes[i]);
    }
    for (size_t i = 0; i < CHECKBOX_NUM; i++)
    {
        free_checkbox(checkboxes[i]);
    }
    UnloadFont(main_font);
    unload_angle_arrow();

}
