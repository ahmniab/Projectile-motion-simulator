#ifndef ENGINE_H
#define ENGINE_H
#include "../../raylib.h"

struct WORLD2D
{
    int v0;
    Vector2 init_coordinates;
    int G;
    double angle;
    int ground_level;
    int meter_in_screan;
    
};

typedef struct WORLD2D *World2d ; // a pointer to struct WORLD2D

World2d new_world_2d(int v0 , int G , double angle,int ground_level , int meter_in_screan/*how long the meter well be in your screan*/);
void set_angle(World2d world , double deg_a);
void add_obj(World2d world , float init_x , float init_y);
Vector2 new_coordinats(World2d world , float t );
void free_world2d(World2d world);


#endif //ENGINE_H