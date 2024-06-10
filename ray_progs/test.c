#include <raylib.h>
#include <string.h>

#define MAX_INPUT_CHARS 20

typedef struct {
    Rectangle rect;
    char text[MAX_INPUT_CHARS + 1];
    bool isSelected;
} TextInput;

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Text Input Example");

    TextInput input1 = { (Rectangle){ 100, 100, 200, 40 }, "", false };
    TextInput input2 = { (Rectangle){ 100, 200, 200, 40 }, "", false };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePosition = GetMousePosition();

            input1.isSelected = CheckCollisionPointRec(mousePosition, input1.rect);
            input2.isSelected = CheckCollisionPointRec(mousePosition, input2.rect);
        }

        if (input1.isSelected) {
            int key = GetKeyPressed();

            if (key != KEY_NULL && strlen(input1.text) < MAX_INPUT_CHARS) {
                int length = strlen(input1.text);
                input1.text[length] = (char)key;
                input1.text[length + 1] = '\0';
            }

            if (IsKeyPressed(KEY_BACKSPACE) && strlen(input1.text) > 0) {
                int length = strlen(input1.text);
                input1.text[length - 1] = '\0';
            }
        }

        if (input2.isSelected) {
            int key = GetKeyPressed();

            if (key != KEY_NULL && strlen(input2.text) < MAX_INPUT_CHARS) {
                int length = strlen(input2.text);
                input2.text[length] = (char)key;
                input2.text[length + 1] = '\0';
            }

            if (IsKeyPressed(KEY_BACKSPACE) && strlen(input2.text) > 0) {
                int length = strlen(input2.text);
                input2.text[length - 1] = '\0';
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Click on the input fields and start typing!", 100, 50, 20, DARKGRAY);

        DrawRectangleRec(input1.rect, input1.isSelected ? RAYWHITE : LIGHTGRAY);
        DrawRectangleLines(input1.rect.x, input1.rect.y, input1.rect.width, input1.rect.height, input1.isSelected ? BLUE : DARKGRAY);
        DrawText(input1.text, input1.rect.x + 5, input1.rect.y + 8, 20, GRAY);

        DrawRectangleRec(input2.rect, input2.isSelected ? RAYWHITE : LIGHTGRAY);
        DrawRectangleLines(input2.rect.x, input2.rect.y, input2.rect.width, input2.rect.height, input2.isSelected ? BLUE : DARKGRAY);
        DrawText(input2.text, input2.rect.x + 5, input2.rect.y + 8, 20, GRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}