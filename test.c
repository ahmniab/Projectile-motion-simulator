#include "raylib.h"
#include <math.h>
#include "movement/pysics/engine.h"

int main(void)
{

    const int screenWidth = 1000;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Moving Ball with Initial Velocity");

    float ballRadius = 3;
    


    SetTargetFPS(60);     

    World2d physics_world = new_world_2d(20 , 10 , 70,screenHeight - 100 , 5);
    add_obj(physics_world , 20, screenHeight - 100);

    while (!WindowShouldClose())    
    {
        
    
        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (float t = 0; t < 20; t += 0.3)
        {
            Vector2 ballPosition =  new_coordinats(physics_world, t  );
            DrawCircleV(ballPosition, ballRadius, MAROON);
            
        }
        

        EndDrawing();
    }
    free_world2d(physics_world);

    CloseWindow();  
    return 0;
}
