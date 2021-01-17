#pragma once

#include "Bumper.h"

class PopBumper : public Bumper {
  private:
    bool collidedLastFrame;


  public:
    PopBumper(Vector2D center, float radius);

    void draw(Interface & interface);

    Vector2D collideWith(Ball & ball, float collisionTime) override;

};
