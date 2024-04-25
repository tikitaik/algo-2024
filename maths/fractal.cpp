#include "maths/raylib.h"
#include <iostream>

int main () {
    InitWindow(1280, 720, "game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
}
