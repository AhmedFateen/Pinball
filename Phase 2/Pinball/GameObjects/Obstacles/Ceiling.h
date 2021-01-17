#pragma once


#include "Obstacle.h"

// Represents a thin vertically infinite wall, on which the ball can bounce
class Ceiling : public Obstacle {
  private:
    // The vertical position of the ceiling
    float position;

    // Whether or not the last frame was a collision (to prevent flapping)
    bool collidedLastFrame;


  public:
    Ceiling(float position);

    void draw(Interface & interface) override;

    Vector2D collideWith(Ball & ball, float collisionTime) override;

};
