#include "raylib.h"
#include "objs/values_board.h"
#include <stddef.h>

#define SCREEN_W 1920
#define SCREEN_H 1080

int main()
{

    InitWindow(SCREEN_W, SCREEN_H, "NULL");
    SetTargetFPS(60);  

    SetWindowState(FLAG_WINDOW_UNDECORATED);

    init_values_board();
    Font font = LoadFontEx("assets/fonts/Montserrat_MediumItalic.ttf", 70, NULL,0);


    while (!WindowShouldClose())        
    {
 
        BeginDrawing();
            ClearBackground((Color){ 13, 13, 13, 255 });
            draw_board(10 ,20,45,font, 0.5);
        EndDrawing();
    }

    free_board();
    UnloadFont(font);
    CloseWindow();
    return 0;
}