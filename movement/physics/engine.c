#include "engine.h"
#include <math.h>
#include <stdlib.h>


double deg2rad_(double deg_a){
    return deg_a * (PI / 180.0f);
}

World2d new_world_2d(int v0 , float G , double angle,int ground_level, int meter_in_screan) {
    World2d new_world = (World2d) malloc(sizeof(struct WORLD2D));
    new_world->v0 = v0 ;
    new_world->G = G;
    set_angle(new_world, angle);
    new_world->ground_level = ground_level;
    new_world->meter_in_screan = meter_in_screan;

    return new_world;
}

void set_angle(World2d world , double deg_a){
    world->angle = deg2rad_(deg_a);
}
void set_v0(World2d world , int v0/*(m/s)*/){
    world->v0 = v0 ;
}
void set_G(World2d world , float G/*(m/s^2)*/){
    world->G = G ;
}


void add_obj(World2d world , float init_x , float init_y){
    world->init_coordinates.x = init_x;
    world->init_coordinates.y = init_y;
}

Vector2 new_coordinats(World2d world, float t  ){
    Vector2 c ;
    c.x = (world->init_coordinates.x / world->meter_in_screan) + (world->v0 * t * (float)cos(world->angle));
    c.x /*(m)*/ *= world->meter_in_screan/*(px)*/;

    c.y = (float)((world->init_coordinates.y / world->meter_in_screan) - (world->v0 * t * (float)sin(world->angle) - 0.5 * world->G * (t * t)));
    c.y /*(m)*/ *= world->meter_in_screan/*(px)*/; // this is to change unit from (meter) to (px)  
    return c;
}

float max_h(World2d world){
    double a_sin = sin(world->angle);
    double mh = ((world->v0 * world->v0)*(a_sin*a_sin)) / (2*world->G);
    return (float)(mh *world->meter_in_screan);
}

double max_th(World2d world){
    return ((world->v0 *sin(world->angle)) / world->G);
}

Vector2 max_coordinats(World2d world ){
    return new_coordinats(world ,(float) max_th(world) );
}
void free_world2d(World2d world){
    free(world);
}

float vx(World2d world , float t){
    return (float)(world->v0 *cos(world->angle));
}
float vy(World2d world , float t){
    return (float)(world->v0 * sin(world->angle) - world->G *t);
}

float mx_d(World2d world){
    return ((world->v0 * world->v0) / world->G * sin(world->angle));
}
