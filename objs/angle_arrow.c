#include "angle_arrow.h"
#include "ball.h"
#include <stdio.h>
#include <math.h>


#ifdef IMG_MOOD
    #define ARROW_PATH "assets/imgs/angle_arrow.png"
#else
    #define ARROW_PX_LONG 300
#endif // IMG_MOOD

struct Arrow arrow ;

double deg2rad(double deg_angle){
    return deg_angle * (PI /180) ;
}

void init_angle_arrow(){

    Vector2 ball_pos = get_ball_position();
    arrow.coordinates.x = ball_pos.x + 512*0.2 / 2 ;
    arrow.coordinates.y = ball_pos.y + 512*0.2 / 2 ;
    printf("x = %f , y = %f\n" , ball_pos.x  ,ball_pos.y);

#ifdef IMG_MOOD
    arrow.texture = LoadTexture(ARROW_PATH);
#endif //IMG_MOOD    
}

void draw_angle_arrow(float deg_angle){
#ifdef IMG_MOOD

        Vector2 ball_pos = get_ball_position();
    if(deg_angle < 45){
        arrow.coordinates.y = ball_pos.y + 512*0.2 / 2 - arrow.texture.height * 0.1 / 2;
    } else{
        arrow.coordinates.x = ball_pos.x + 512*0.2 / 2 - arrow.texture.height * 0.1 / 2;
    }
    DrawTextureEx(arrow.texture,arrow.coordinates,-1*deg_angle,0.1f, WHITE);
#else
    Vector2 endPos;
    
    endPos.x = arrow.coordinates.x + ARROW_PX_LONG * cos(deg2rad(deg_angle));
    endPos.y = arrow.coordinates.y - ARROW_PX_LONG * sin(deg2rad(deg_angle));
    // printf("( %.2f , %.2f ) angle = %f\n" , endPos.x , endPos.y , deg_angle);

    
    DrawLineEx(arrow.coordinates, endPos, 2, VIOLET);
#endif // IMG_MOOD

}
void unload_angle_arrow(){
#ifdef IMG_MOOD
    UnloadTexture(arrow.texture);
#endif //IMG_MOOD
}