#include "checkbox.h"
#include <string.h>
#include <stdlib.h>
#define FONT_SIZE 30

Checkbox * init_checkbox(int x , int y , char *lable_text , bool default_value , Font * pfont){
    Checkbox * new_checkbox = (Checkbox*)malloc(sizeof(Checkbox));
    if (!new_checkbox) return NULL;
    char * text = (char*)malloc(strlen(lable_text) * sizeof(char) + 1);
    strcpy(text , lable_text); 
    new_checkbox->lable = (const char *)text;
    new_checkbox->value = default_value;
    new_checkbox->font = pfont;
    
    Vector2 dims = MeasureTextEx(*pfont , lable_text , FONT_SIZE , 1);
    new_checkbox->place.x = x;
    new_checkbox->place.y = y;
    new_checkbox->place.width = dims.x + 45;
    new_checkbox->place.height = dims.y;

    return new_checkbox;
}

void draw_check_box(Checkbox * chbox){

    // DrawRectangle(chbox->place.x , chbox->place.y , chbox->place.width , chbox->place.height , GREEN);

    Color main_color ;
    if (CheckCollisionPointRec(GetMousePosition(), chbox->place))
    {
        main_color = PURPLE;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            chbox->value = !chbox->value;
        
    }
    else 
        main_color = RAYWHITE;

    Vector2 coordinates;
    coordinates.x = chbox->place.x;
    coordinates.y = chbox->place.y;
    
    DrawRectangle(coordinates.x , coordinates.y , 30 , 30 , main_color);

    if (chbox->value)
    {
        DrawRectangle(coordinates.x + 3  , coordinates.y + 3 , 24 , 24 , BLUE);
        
    }

    coordinates.x += 45;
    DrawTextEx(*chbox->font, chbox->lable, coordinates, FONT_SIZE, 1, main_color);
     
    
    
    

}

void free_checkbox(Checkbox * chbox)
{
    if (chbox)
    {
        free((void*)chbox->lable);
        free(chbox);
    }
    
}