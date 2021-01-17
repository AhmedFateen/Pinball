#pragma once

#include "Bumper.h"

class ThrustBumper : public Bumper {
  private:
    float speedingFactor;

    bool collidedLastFrame;


  public:
    ThrustBumper(Vector2D center, float radius, float speedingFactor);

    void draw(Interface & interface) override;

    Vector2D collideWith(Ball & ball, float collisionTime);

};

