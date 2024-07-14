#include "ball.h"
#define BALL_IMG "assets/imgs/ball.png"

struct Ball ball;


void init_ball(){
    ball.coordinates.x =BALL_X ;
    ball.coordinates.y = BALL_Y ;
    ball.ball_texture = LoadTexture(BALL_IMG);

}

void draw_ball(float x , float y){
    ball.coordinates.x = x ;
    ball.coordinates.y = y ;
    DrawTextureEx(ball.ball_texture,ball.coordinates,0.0f,0.2f, WHITE);
}

void unload_ball(){
    UnloadTexture(ball.ball_texture); 
}

Vector2 get_ball_position(){
    // printf("ball coordinates x = %f , y = %f\n",ball.coordinates.x , ball.coordinates.y);
    return ball.coordinates;
}
Texture2D get_ball_tex(){
    return ball.ball_texture;
}

