#include "engine.h"
#include <math.h>
#include <stdlib.h>


double deg2rad_(double deg_a){
    return deg_a * (PI / 180.0f);
}

World2d new_world_2d(int v0 , int G , double angle,int ground_level, int meter_in_screan) {
    World2d new_world = (World2d) malloc(sizeof(struct WORLD2D));
    new_world->v0 = v0 * meter_in_screan;
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
    world->v0 = v0 * world->meter_in_screan;
}


void add_obj(World2d world , float init_x , float init_y){
    world->init_coordinates.x = init_x;
    world->init_coordinates.y = init_y;
}

Vector2 new_coordinats(World2d world, float t  ){
    Vector2 c ;
    c.x = world->init_coordinates.x + (world->v0 * t * (float)cos(world->angle));

    c.y = world->init_coordinates.y - (world->v0 * t * (float)sin(world->angle) - 0.5 * world->G * (t * t));
    return c;
}

void free_world2d(World2d world){
    free(world);
}
