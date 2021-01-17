#pragma once

#include "Bumper.h"

class VibraniumBumper : public Bumper {
  public:
    VibraniumBumper(Vector2D center, float radius);

    void draw(Interface & interface) override;

    Vector2D collideWith(Ball & ball, float collisionTime);

};
