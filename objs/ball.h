#ifndef BALL_H
#define BALL_H
#include "../raylib.h"

#define BALL_X 50
#define BALL_Y 800

struct Ball
{
    Texture2D ball_texture;
    Rectangle dimintions;
    Vector2 coordinates;
    int width;
    int height;
};

void init_ball ();
void draw_ball (float x , float y);
void unload_ball();
Vector2 get_ball_position();
Texture2D get_ball_tex();
#endif // BALL_H