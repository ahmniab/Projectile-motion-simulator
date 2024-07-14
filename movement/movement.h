#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "../raylib.h"
#include "ball.h"
#include "angle_arrow.h"
#include "text_box.h"

#define SCREEN_H 1080
#define SCREEN_W 1920
#define GROUND_LEVEL 896


void init_components();
void drow_objs();
void free_components();

#endif //MOVEMENT_H