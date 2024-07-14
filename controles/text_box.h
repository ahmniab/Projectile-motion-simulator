#ifndef TEXT_BOX_H
#define TEXT_BOX_H
#include "../raylib.h"

typedef struct 
{
    int max_len;
    int len ;
    char *buff;
    Color backgrond_color;
    Color border_color;
    Color border_color_on_hover;
    Color text_color;
    Font *text_font;
    float font_size;
    float spacing;
    Rectangle textbox_rectangle;
    bool mouseOnText;
    unsigned long framesCounter;

}Text_box;

Text_box *create_new_text_box(int max_len ,Font *text_font ,float font_size, float spacing,\
                              Color backgrond_color , Color border_color , Color border_color_on_hover ,\
                              Color Text_color , float x , float y , float width , \
                              float height);

void draw_text_box(Text_box *ptbx); 
void free_text_box(Text_box *ptb);



#endif // TEXT_BOX_H