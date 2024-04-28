#include "maths/raylib.h"
#include <iostream>

const int screenWidth = 1280;
const int screenHeight = 720;
float triHeight = 500;

// gets x coord of top point, y coord of top point, and heigh of triangle
void tri(float xTop, float yTop, float height) {
    DrawTriangle(Vector2 {xTop, yTop}, Vector2 {static_cast<float>(xTop - (0.57735 * height)), yTop + height}, Vector2{static_cast<float>(xTop + (0.57735 * height)), yTop + height}, WHITE);
}

void divide(float x, float y, float height, int lvl, int max) {
    if (lvl >= max) {
        tri(x, y, height);
    }
    else {
        //DrawTriangle(Vector2 {x, y}, Vector2 {static_cast<float>(x - (0.57735 * height)), y + height}, Vector2{static_cast<float>(x + (0.57735 * height)), y + height}, BLACK);
        // top triangle
        divide(x, y, height / 2, lvl + 1, max);
        // bottom left triangle
        divide(x - (0.57735 * height / 2), y + height / 2, height / 2, lvl + 1, max);
        // bottom right triangle
        divide(x + (0.57735 * height / 2), y + height / 2, height / 2, lvl + 1, max);
    }
}

// funny triangle - draw three black triangles and a white triangle in every white triangle
void sierpinski(int max) {
    divide(screenWidth / 2, (screenHeight - triHeight) / 2 , triHeight, 1, max);
}

int main () {
    InitWindow(screenWidth, screenHeight, "fractals?");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
            ClearBackground(BLACK);
            sierpinski(10);
        EndDrawing();
    }
}
