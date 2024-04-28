#include "maths/raylib.h"
#include <iostream>

Vector2 windowSize = {1280, 720};
float triHeight = 720;
float tan30 = 0.57735026919;

// gets x coord of top point, y coord of top point, and heigh of triangle
void tri(float x, float y, float height) {
    DrawTriangle(Vector2 {x, y}, Vector2 {x - tan30 * height, y + height}, Vector2{x + tan30 * height, y + height}, WHITE);
}

void divide(float x, float y, float height, int lvl, int max) {
    if (lvl >= max) {
        tri(x, y, height);
    }
    else {
        // top triangle
        divide(x, y, height / 2, lvl + 1, max);
        // bottom left triangle
        divide(x - tan30 * height / 2, y + height / 2, height / 2, lvl + 1, max);
        // bottom right triangle
        divide(x + tan30 * height / 2, y + height / 2, height / 2, lvl + 1, max);
    }
}

// funny triangle - draw 3 white triangle in every white triangle
void sierpinski(int max) {
    divide(windowSize.x / 2, (windowSize.y - triHeight) / 2 , triHeight, 1, max);
}


// fractal stuff now >:)
int maxIter = 50;
float scale = 1.0f / float(windowSize.y / 2);

Vector2 squareZn(Vector2 zn, Vector2 C) {
    const float zr = zn.x * zn.x - zn.y * zn.y;
    const float zi = 2.0 * zn.x * zn.y;
    
    return Vector2 {zr + C.x, zi + C.y};
}

float modSq(Vector2 z) {
    return z.x * z.x + z.y * z.y;
}

int iterations(const Vector2 z0, const Vector2 C) {
    int iter = 0;
    Vector2 zcur = z0;
    while (iter < maxIter && modSq(zcur) <= 4.0) {
        zcur = squareZn(zcur, C);
        iter++;
    }
    if (iter >= 50) {
        return 50;
    }
    else {
        return iter;
    }
}

void render(const Vector2 windowSize, const Vector2 C, const float scale) {

    for (int y = 0; y < windowSize.y; y++) {
        for (int x = 0; x < windowSize.x; x++) {
            // colour pixel
            const float px = float(x - windowSize.x / 2) * scale;
            const float py = float(y - windowSize.y / 2) * scale;
            DrawPixel(x, y, ColorFromHSV(float(iterations({px, py}, C) / 50.0 * 360.0), 0.5, 1));
        }
    }
}

int main (int argc, char *argv[]) {
    InitWindow(windowSize.x, windowSize.y, "fractals?");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
            ClearBackground(BLACK);
            //DrawPixel(100, 100, ColorFromHSV(1.0 / 360.0f, 0.8f, float(iterations({float(100), float(100)}, {1,1}) / 50.0f)));
            render(windowSize, Vector2 {-1.5, 0.0}, scale);
            scale = scale - 0.00001;
        EndDrawing();
    }
}
