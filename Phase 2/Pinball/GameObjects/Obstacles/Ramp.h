#pragma once

#include "Obstacle.h"

class Ramp : public Obstacle {
  private:
    FlipperType type;

    // point closest to the flippers
    Vector2D flipperPoint;

    float height;

    bool collidedLastFrame;


  public:
    Ramp(FlipperType type, float height);

    void draw(Interface & interface) override;

    Vector2D collideWith(Ball & ball, float collisionTime) override;

};
