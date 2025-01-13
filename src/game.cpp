#include "game.h"
#include <raylib.h>

// Game::Game() {
//   game(5);
// }

Game::Game(int speed) {
  // Brick placement
  std::fill(bricks.begin(), bricks.end(), 1);
  // Panel placement
  panel = {
    (float)(GetScreenWidth()/2 - 50), (float)(GetScreenHeight() - 15),
    100, 10
  };
  
  // Ball placement
  Ball ball({400, 300}, {0, 5});
  println("Game constructor");
}

void Game::draw() {
  // Draw bricks
  for (int i = 0; i < ROW; i++)
    for (int j = 0; j < COL; j++)
      if (bricks[i + 14*j])
        DrawRectangle(15 + 55*i, 50 + 15*j, 50, 10, RED);
  // Draw panel
  DrawRectangleRec(panel, SKYBLUE);
  // Draw ball
  ball.draw();
  // Draw lives
  DrawText("Lives:", 10, 10, 20, WHITE);
  for (int i = 0; i < lives; i++)
    DrawCircle(80 + 20*i, 20, 5, WHITE);
  // Draw score
  DrawText(TextFormat("Score: %04d", score), GetScreenWidth() - 150, 10, 20, WHITE);
  // Draw game over
  if (gameOver) {
    DrawText("Game Over", GetScreenWidth()/2 - MeasureText("Game Over", 40)/2, GetScreenHeight()/2 - 40, 40, WHITE);
    DrawText("Press [R] to restart", GetScreenWidth()/2 - MeasureText("Press [R] to restart", 20)/2, GetScreenHeight()/2, 20, WHITE);
  }
}

void Game::update() {
  // Move player panel
  if (IsKeyDown(KEY_A) && panel.x > 0) panel.x -= 5;
  if (IsKeyDown(KEY_D) && panel.x < GetScreenWidth()-100) panel.x += 5;
  // Ball movement
  ball.move();

  // Wall collision
  if (ball.pos.x >= GetScreenWidth()-ball.radius || ball.pos.x <= 0+ball.radius) ball.speed.x *= -1;
  if (ball.pos.y <= 0+ball.radius) ball.speed.y *= -1;

  // Panel collision
  if (CheckCollisionCircleRec(ball.pos, ball.radius, panel)) {
    int panelCenter = panel.x + panel.width/2;
    ball.speed.x = (ball.pos.x - panelCenter) / ball.speed.y;
    ball.speed.y *= -1;
  }

  // Brick collision
  for (int i = 0; i < ROW; i++)
    for (int j = 0; j < COL; j++)
      if (bricks[i + ROW*j]) {
        if (CheckCollisionCircleRec(ball.pos, ball.radius, {15.0f + 55.0f*i, 50.0f + 15.0f*j, 50, 10})) {
          bricks[i + ROW*j] = 0;
          score += 100;
          ball.speed.y *= -1;
        }
      }

  // Reset when gameover
  if (gameOver && IsKeyPressed(KEY_R)) {
    gameOver = false;
    lives = 3;
    score = 0;
    std::fill(bricks.begin(), bricks.end(), 1);
    ball.reset();
  }
  // Game Over
  if (gameOver) return;
  static float startTimer = -1.0f;
  if (ball.pos.y >= GetScreenHeight()-ball.radius) {
    if (startTimer < 0) startTimer = GetTime();
  }
  if (GetTime() - startTimer >= 2 && startTimer >= 0) {
    lives--;
    if (lives <= 0) gameOver = true;
    else ball.reset();
    startTimer = -1.0f;
  }
}