#include "raylib.h"
#include "controles.h"
#include "helper.h"
#include "movement/movement.h"


int main(){
    InitWindow(SCREEN_W , SCREEN_H, "physics");
    SetTargetFPS(60);
    SetWindowState(FLAG_FULLSCREEN_MODE);

    init_components();

    while (!WindowShouldClose())
    {

        BeginDrawing();
            ClearBackground((Color){ 13, 13, 13, 255 });
            drow_objs();
            draw_controler();
        EndDrawing();
        
        
    }
    
    free_components();
    free_controler();
    CloseWindow();
}