#include <raylib.h>

class Ball {
public:
  Vector2 pos = {400, 300};
  Vector2 speed = {0, 5};
  float radius = 10;
  Vector2 initPos = {400, 300};

  Ball() {}
  Ball(Vector2 speed) : speed(speed) {}
  Ball(Vector2 pos, Vector2 speed) : pos(pos), speed(speed), initPos(pos) {}
  Ball(Vector2 pos, float radius, Vector2 speed) : pos(pos), radius(radius), speed(speed) {}

  inline void draw() { DrawCircle(pos.x, pos.y, radius, PURPLE); }
  inline void move() { pos.x += speed.x; pos.y += speed.y; }
  inline void reset() { pos = initPos; speed = {0, speed.y}; }
};