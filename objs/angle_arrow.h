#ifndef ANGLE_ARROW_H
#define ANGLE_ARROW_H

#include "../raylib.h"


struct Arrow
{
    Texture2D texture;
    Rectangle dimintions;
    Vector2 coordinates;
    int width;
    int height;
};
void init_angle_arrow();
void draw_angle_arrow(float deg_angle);
void unload_angle_arrow();
#endif //ANGLE_ARROW_H