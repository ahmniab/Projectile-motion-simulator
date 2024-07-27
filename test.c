#include "raylib.h"
#include "controles/checkbox.h"
#include <stddef.h>

#define SCREEN_W 1920
#define SCREEN_H 1080

int main()
{

    InitWindow(SCREEN_W, SCREEN_H, "NULL");
    SetTargetFPS(60);  

    SetWindowState(FLAG_WINDOW_UNDECORATED);

    Font font = LoadFontEx("assets/fonts/Montserrat_MediumItalic.ttf", 70, NULL,0);
    Checkbox *chbx = init_checkbox(100 , 100 , "XDDD",false, &font);


    while (!WindowShouldClose())        
    {
 
        BeginDrawing();
            ClearBackground((Color){ 13, 13, 13, 255 });
            draw_check_box(chbx);
        EndDrawing();
    }

    UnloadFont(font);
    free_checkbox(chbx);
    CloseWindow();
    return 0;
}