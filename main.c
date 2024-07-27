#include "raylib.h"
#include "controles.h"
#include "helper.h"
#include "movement/movement.h"


int main(){
    InitWindow(SCREEN_W , SCREEN_H, "Projectile Motion Simulator");
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_UNDECORATED);

    init_components();
    #ifndef DEVELOPER_MOOD
        double wallpaper_timer = 3;
        init_wallpaper();
    #endif

    while (!WindowShouldClose())
    {

        BeginDrawing();
            ClearBackground((Color){ 13, 13, 13, 255 });
            #ifndef DEVELOPER_MOOD
                if(wallpaper_timer > 0){
                    draw_wallpaper();
                    wallpaper_timer -= GetFrameTime();
                }
                else{
            #endif
                    drow_objs();
                    if(!is_render_started()) draw_controler();
                    else
                    {
                        #ifndef PREVIEW_MOOD
                            rendering_screen();
                        #endif
                    }
            #ifndef DEVELOPER_MOOD
                }
            #endif
            
        EndDrawing();
        
        
    }
    
    free_wallpaper();
    free_components();
    free_controler();
    CloseWindow();
}