#pragma once

#include "Obstacle.h"

class Bullseye : public Obstacle {
  private:
    Vector2D center;

    float radius;

    const int increaser[6]=  { 100,50,30,15,10,5 };

    bool justEntered[6]=  { false,false,false,false,false,false };

    void resetBools();


  public:
    Bullseye(Vector2D center, float radius);

    //Constructor
    void draw(Interface & interface);

    Vector2D collideWith(Ball & ball, float collisionTime) override;

    void updateScore(Ball & ball, Score & score) override;

};
