#ifndef ENGINE_H
#define ENGINE_H
#include "../../raylib.h"

struct WORLD2D
{
    int v0;
    Vector2 init_coordinates;
    float G;
    double angle;
    int ground_level;
    int meter_in_screan;
    
};

typedef struct WORLD2D *World2d ; // a pointer to struct WORLD2D

World2d new_world_2d(int v0 , float G , double angle,int ground_level , int meter_in_screan/*how long the meter well be in your screan*/);
void set_angle(World2d world , double deg_a);
double deg2rad_(double deg_a);
void set_v0(World2d world , int v0/*(m/s)*/);
void set_G(World2d world , float G/*(m/s^2)*/);
void add_obj(World2d world , float init_x , float init_y);
Vector2 new_coordinats(World2d world , float t );
float max_h(World2d world); /*px*/
double max_th(World2d world);
float vx(World2d world , float t);
float vy(World2d world , float t);
float mx_d(World2d world);
Vector2 max_coordinats(World2d world );
void free_world2d(World2d world);


#endif //ENGINE_H