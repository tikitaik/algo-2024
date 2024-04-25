#include "maths/raylib.h"
#include <iostream>

// draw a right way up triangle
void drawTriangleUp(float startX, float startY, float midX, float midY, float endX, float endY) {
    DrawLine(startX, startY, midX, midY, RED);
    DrawLine(midX, midY, endX, endY, RED);
    DrawLine(endX, endY, startX, startY, RED);
}
// draw an upside down triangle
void drawTriangleDown() {

}


int main () {
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(1280, 720, "fractals?");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

            ClearBackground(BLACK);

            // Triangle shapes and lines
            DrawTriangle((Vector2){ screenWidth/4.0f *3.0f, 80.0f },
                         (Vector2){ screenWidth/4.0f *3.0f - 60.0f, 150.0f },
                         (Vector2){ screenWidth/4.0f *3.0f + 60.0f, 150.0f }, VIOLET);

            drawTriangleUp(100.0f, 100.0f, 50.0f, 150.0f, 150.0f, 150.0f);
            // NOTE: We draw all LINES based shapes together to optimize internal drawing,
            // this way, all LINES are rendered in a single draw pass
            DrawLine(18, 42, screenWidth - 18, 42, RAYWHITE);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
}
