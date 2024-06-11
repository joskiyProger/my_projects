#include "raylib.h"

int main(){
  SetTargetFPS(700);
  int r = 0, g = 0, b = 0, flag = 0;
  
  InitWindow(800, 450, "ra(Y)inbow");

  while (!WindowShouldClose()){
    BeginDrawing();
    Color background_color = {r, g, b, 255};
    if (!flag) {
      if (r<255) {
        r++;
      }
      if ((r>=254) && (g<255)) {
        g++;
      }
      if ((g>=254) && (b<255)) {
        b++;
      }
      if (g>=254) {
        flag = 1;
      }
     } else {
      if (r>0) {
        r--;
      }
      if ((r<=1) && (g>0)) {
        g--;
      }
      if ((g<=1) && (b>0)) {
        b--;
      }
      if (b <100) {
        flag = 0;
      }
    }
        ClearBackground(background_color);
        DrawText("ra(Y)inbow", 300, 200, 40, BLACK);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
