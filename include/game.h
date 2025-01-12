#pragma once
#include <iostream>
#include <array>
#include <raylib.h>
#include "ball.h"

#define println(x) std::cout << x << std::endl
#define ROW 14
#define COL 5

class Game {
  std::array<int, ROW*COL> bricks;
  // Vector2 panel;
  Rectangle panel;
  Ball ball;
public:
  // Game();
  Game(int speed);
  void update();
  void draw();
};