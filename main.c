#include "raylib.h"
#include "controles.h"
#include "helper.h"
#include "movement/movement.h"


int main(){
    InitWindow(SCREEN_W , SCREEN_H, "physics");
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_UNDECORATED);

    init_components();

    while (!WindowShouldClose())
    {

        BeginDrawing();
            ClearBackground((Color){ 13, 13, 13, 255 });
            drow_objs();
            if(!is_render_started()) draw_controler();
            else
            {
                rendering_screen();
            }
            
        EndDrawing();
        
        
    }
    
    free_components();
    free_controler();
    CloseWindow();
}