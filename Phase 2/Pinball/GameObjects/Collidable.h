#pragma once


#include "Ball.h"

// An interface class that should be implemented by any class that can apply force on the ball upon collision
class Collidable {
  public:
    virtual Vector2D collideWith(Ball & ball, float collisionTime) = 0;

};
