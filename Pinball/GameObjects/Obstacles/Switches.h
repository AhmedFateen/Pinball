#pragma once

#include "Obstacle.h"

class Switches : public Obstacle {
  private:

    Vector2D position;

    float length;

    bool alreadyPassed = false;


  public:
    Switches(Vector2D position, float length);

    Vector2D collideWith(Ball & ball, float collisionTime) override;

    void draw(Interface & interface) override;

};
