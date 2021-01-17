#pragma once


#include "Obstacle.h"

class Bumper : public Obstacle {
  protected:

    float radius;
    Vector2D center;


  public:
    Bumper(float radius, Vector2D center) :radius(radius), center(center) {};

};
