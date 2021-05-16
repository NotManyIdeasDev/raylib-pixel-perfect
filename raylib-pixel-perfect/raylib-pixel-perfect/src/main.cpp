#include "raylib.h"
#include "pixel_camera.h"
#include <string>

int main(void)
{
    //dummy values.
    int screenWidth = 800;
    int screenHeight = 450;

    const int virtualScreenWidth = 320;
    const int virtualScreenHeight = 180;

    SetConfigFlags(FLAG_VSYNC_HINT);

    InitWindow(screenWidth, screenHeight, "raylib - C++ pixel-perfect camera");

    //Set Fullscreen
    screenWidth = GetMonitorWidth(0);
    screenHeight = GetMonitorHeight(0);
    SetWindowSize(screenWidth, screenHeight);
    ToggleFullscreen();

    const float virtualRatio = (float)screenWidth / (float)virtualScreenWidth;

    PixelCamera camera(screenWidth, screenHeight, virtualRatio);

    while (!WindowShouldClose())
    {
        //TODO: Move objects and camera here.

        camera.Update();

        BeginDrawing();
        ClearBackground(debug::debug_color);

        camera.BeginWorldMode();

        //TODO: Call draw for world objects here.

        DrawRectanglePro({ 160, 90, 40, 40 }, { 20, 20 }, sinf(GetTime() / 100) * 4000, WHITE);
        DrawRectanglePro({ 90, 30, 16, 16 }, { 8, 8 }, sinf(GetTime() / 100) * 30000, RED);
        DrawRectanglePro({ 250, 150, 30, 30 }, { 15, 15 }, sinf(GetTime() / 100) * 5000, YELLOW);
        DrawRectanglePro({ 50, 160, 60, 60 }, { 30, 30 }, -cosf(GetTime() / 100) * 10000, BLUE);
        DrawRectanglePro({ 190, 40, 24, 24 }, { 12, 12 }, -sinf(GetTime() / 100) * 9090, GREEN);
        DrawRectanglePro({ 280, 30, 48, 48 }, { 24, 24 }, cosf(GetTime() / 25) * 1500, VIOLET);

        camera.EndWorldMode();

        camera.DrawWorld();

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}