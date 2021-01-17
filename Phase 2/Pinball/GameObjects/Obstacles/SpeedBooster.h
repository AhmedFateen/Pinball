#pragma once

#include "Obstacle.h"

class SpeedBooster : public Obstacle {
  private:

    Vector2D center;

    float radius;


  public:
    SpeedBooster(Vector2D center, float radius);

    void draw(Interface & interface) override;

    Vector2D collideWith(Ball & ball, float collisionTime) override;

};
