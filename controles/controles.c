#include "controles.h"
#include "../objs/angle_arrow.h"
#include "../movement/movement.h"
#define BOX_NUM 3
#define size_t unsigned long

char  text_array[BOX_NUM][25] = {
    "Angle (deg)",
    "Velocity (m/s)" ,
    "Gravity (m/(s*s))"
};

Text_box *text_boxes[BOX_NUM];   
Font main_font ;


void init_controler(){
    main_font = LoadFont("assets/fonts/Montserrat_MediumItalic.ttf"); 

    text_boxes[ANGLE_TEXTBOX] = create_new_text_box(2 ,&main_font ,20,1,PURPLE,PURPLE,RED ,BLACK, 10 , 940 ,300 , 40);
    text_boxes[V_TEXTBOX] = create_new_text_box(5 ,&main_font ,20,1,PURPLE,PURPLE,RED ,BLACK, 350 , 940 ,300 , 40);
    text_boxes[G_TEXTBOX] = create_new_text_box(5 ,&main_font ,20,1,PURPLE,PURPLE,RED ,BLACK, 690 , 940 ,300 , 40);
    init_angle_arrow();
}
Font get_font(){
    return main_font;
}
bool mouse_on_textbox(){
    for (size_t i = 0; i < BOX_NUM; i++)
    {
        if (text_boxes[i]->mouseOnText)
        {
            return true;
        }
        
    }
    return false;
    
}

void draw_controler(){
    
    for (size_t i = 0; i < BOX_NUM; i++)
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
    
    draw_angle_arrow(get_working_angle());
}

char *get_text_string(TextboxName name , int * str_len){
    *str_len = text_boxes[name]->len;
    return text_boxes[name]->buff;
}

void free_controler(){
    for (size_t i = 0; i < BOX_NUM; i++)
    {
        free_text_box(text_boxes[i]);
    }
    UnloadFont(main_font);
    unload_angle_arrow();

}
