#pragma once

#include "Obstacle.h"

class Kickers : public Obstacle { // to be drawn in the top right corner because we only care about the tilted part
  private:
      float length;
      const Vector2D cornerPoint = { layout.GAME_WIDTH,0 };
      Vector2D leftPoint;
      Vector2D bottomPoint;
      bool collidedLastFrame;


  public:
    Kickers(float length);

    void draw(Interface & interface) override;

    Vector2D collideWith(Ball & ball, float collisionTime) override;

};
