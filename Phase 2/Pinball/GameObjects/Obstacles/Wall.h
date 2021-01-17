#pragma once


#include "Obstacle.h"


// Represents a thin vertically infinite wall, on which the ball can bounce
class Wall : public Obstacle {
  private:
    // The horizontal position of the wall
    float position;

    // Whether or not the last frame was a collision (to prevent flapping)
    bool collidedLastFrame;


  public:
    explicit Wall(float position);

    void draw(Interface & interface) override;

    Vector2D collideWith(Ball & ball, float collisionTime) override;

};
