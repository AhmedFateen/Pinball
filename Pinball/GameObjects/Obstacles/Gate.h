#pragma once

#include "Obstacle.h"

class Gate : public Obstacle {
  private:

    Vector2D point;
    float length;


  public:
    Gate(Vector2D center, float length);

    Vector2D collideWith(Ball & ball, float collisionTime) override;

    void draw(Interface & interface);

};
