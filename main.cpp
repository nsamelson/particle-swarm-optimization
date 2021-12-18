#include "raylib.h"
#include <sstream>
#include <array>
#include <string>
#include <raymath.h>
#include <ctime>
#include <cstdlib>
#include "src/Particles.h"
#include "src/Perlin.h"

int main(void)
{
    // Initialization
    //---------------------------------------------------------
    const int screenWidth = 1900;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "raylib PSO - Particle Swarm Optimization");

    //ball
    int iteration = 0;
    float dt = 0;
    float delta = 0;
    srand(time(0));

    //map
    Perlin terrain = Perlin();

    
    //Pause game
    bool pause = 1;
    int framesCounter = 0;
 


    //camera

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 20.0f, 20.0f, 20.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type
    SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

    int freq = 1;
    int depth = 1;
    float scale = 1.0f;
    bool update = true;
    bool info = true;   

    //Swarm

    Particles particles = Particles(100);
    int factor = 2;

    //create map :
    int size = 30;
    float semisize = size/2;

    float map[size][size];    
   

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //----------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //-----------------------------------------------------
        UpdateCamera(&camera);          // Update camera

        //keys
        if (IsKeyPressed(KEY_UP)) { freq++; update = true; }
        if (IsKeyPressed(KEY_DOWN)) { freq--; update = true; }
        if (IsKeyPressed(KEY_LEFT)) { depth++; update = true; }
        if (IsKeyPressed(KEY_RIGHT)) { depth--; update = true; }
        if (IsKeyPressed(KEY_N)) { scale += 0.1; update = true; }
        if (IsKeyPressed(KEY_M)) { scale -= 0.1; update = true; }
        if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        if (IsKeyPressed(KEY_ENTER)) update = true;
        if (IsKeyPressed(KEY_SPACE)) pause = !pause;
        if (IsKeyPressed(KEY_I)) { info = !info; }

        //map

        if (update)
        {
            particles.empty_vector();

            for (int x = 0; x < size; x++)
            {
                for (int y = 0; y < size; y++)
                {
                    float z = terrain.perlin2d(x * scale, y * scale, freq / 10.0f, depth) * 10;
                    map[x][y] = z;

                    float random_height = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); //0 to 1


                    
                    if (x %factor == 0 and y % factor == 0){
                        particles.init_position((float)(x - semisize) /2.0f, (float)z *1.5f+ random_height * 5, (float)(y - semisize)/2.0f );

                    }
                }
            }
            update = false;
        }
        
        //pso

        if (!pause)
        {
            dt = GetFrameTime();
            delta += dt;
            iteration +=1;

            particles.move_particles(dt);


        }
        else {
            framesCounter++;
            
        }
        //-----------------------------------------------------

        // Draw
        //-----------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);


            BeginMode3D(camera);
                
                int i = 0;
                for (int x = 0; x < size; x++)
                {
                    for (int y = 0; y < size; y++)
                    {
                        DrawCube((Vector3) { (float)(x - semisize) /2.0f, map[x][y] , (float)(y - semisize)/2.0f},
                                    0.5f,
                                    map[x][y],
                                    0.5f,
                                    (Color) { (unsigned char)((map[x][y] / 10) * 255),(unsigned char) ((map[x][y] / 10) * 255), (unsigned char)((map[x][y] / 10) * 255), 255 });

                        if (x %factor == 0 and y % factor == 0){
                            DrawSphere(particles.get_particles()[i].getPosition(), particles.get_particles()[i].getRadius(), BLUE);
                            i++;

                        }
                    }
                    
                }

                DrawGrid(semisize, 1.0f);

            EndMode3D();

            for (int x = 0; x < size; x++)
            {
                for (int y = 0; y < size; y++)
                {
                    DrawPixel(screenWidth - 100 + x, y, (Color) { 255, 255, 255, (unsigned char)((map[x][y] / 10) * 255) });
                }
            }

            // On pause, we draw a blinking message
            if (pause && ((framesCounter/30)%2)) DrawText("PAUSED", 350, 200, 30, GRAY);
            if (info)
            {
                DrawRectangle(10, 10, 200, 130, LIGHTGRAY );
                DrawText(TextFormat("Iterations: %d", iteration), 20, 20, 15, BLACK);
                DrawText(TextFormat("W: %0.001f", particles.w), 20, 40, 15, BLACK);
                DrawText(TextFormat("c1: %0.1f", particles.c1), 20, 60, 15, BLACK);
                DrawText(TextFormat("c2: %0.1f", particles.c2), 20, 80, 15, BLACK);
                DrawFPS(20, 100);

                
            }
            else{
                DrawFPS(10, 10);
            }
           

        EndDrawing();
        //-----------------------------------------------------
    }

    // De-Initialization
    //---------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------
    return 0;
}