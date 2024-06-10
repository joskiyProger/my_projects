#include "raylib.h"

int main() {
InitWindow(395, 489, "калькулятор");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawFPS(300,10);
        DrawText("+", 333, 220, 27, BLACK);
        EndDrawing();

    }
    CloseWindow();
    return 0;
}
