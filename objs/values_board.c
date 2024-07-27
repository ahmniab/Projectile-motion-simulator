#include "../raylib.h"
#include "values_board.h"
#include <stddef.h>
Vector2 pos;
Texture2D _board;

void init_values_board(){
    _board = LoadTexture("assets/imgs/values_board.png");
    pos.x =  1920/ 2 - (_board.width * 0.7f)/2;
    pos.y = 1080/ 2 - (_board.height * 0.7f)/2;
}
void draw_board(float G , int v , int angle , Font font , float display_factor){
    Color color = {255 , 255 , 255 , 255};
    if(display_factor > 1) display_factor = 1;
    else if (display_factor < 0) display_factor = 0;
    color.a *= display_factor;

    DrawTextureEx(_board,pos,0.0f,0.7f, color);
    Vector2 text_pos = pos;
    const char *text = TextFormat("Gravity = %.1f",G);
    text_pos.x += (_board.width * 0.7f)/2  - MeasureTextEx(font,text, 70 , 1).x / 2;
    text_pos.y += 220;
    DrawTextEx(font, text, text_pos, 70,1, color); 

    text = TextFormat("Velocity = %d",v);
    text_pos.x = pos.x + (_board.width * 0.7f)/2  - MeasureTextEx(font,text, 70 , 1).x / 2;
    text_pos.y += 100;
    DrawTextEx(font, text, text_pos, 70,1, color); 
    
    text = TextFormat("Anagle = %d",angle);
    text_pos.x = pos.x + (_board.width * 0.7f)/2  - MeasureTextEx(font,text, 70 , 1).x / 2;
    text_pos.y += 100;
    DrawTextEx(font, text, text_pos, 70,1, color); 

    
}
void free_board(){
    UnloadTexture(_board); 

}