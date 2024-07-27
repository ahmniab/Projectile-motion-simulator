#ifndef CHECK_BOX_H
#define CHECK_BOX_H
#include "../raylib.h"

typedef struct 
{
    bool value ;
    const char * lable;
    Rectangle place;
    Font * font;
}Checkbox;
Checkbox * init_checkbox(int x , int y , char *lable_text , bool default_value , Font * pfont);
void draw_check_box(Checkbox * chbox);
void free_checkbox(Checkbox * chbox);


#endif // CHECK_BOX_H