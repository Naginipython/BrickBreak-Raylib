#include "game.h"
#include <raylib.h>

int main(int argc, char* argv[]) {
  InitWindow(800, 600, "Brick Break");
  SetTargetFPS(60);
  Game game(5);

  while (!WindowShouldClose()) {
    game.update();
    BeginDrawing();
      ClearBackground(DARKGRAY);
      game.draw();
    EndDrawing();
  }
  return 0;
}