#pragma once


#include "Obstacle.h"

class Collectables : public Obstacle {
  private:
    Vector2D center;

    char character[6]=  { 'C','I','E','2','0','2' };

    unsigned int fontSize;

    bool ballSteps[6]=  { false,false,false,false,false,false };

    Vector2D bottomLeft[6];

    Vector2D bottomRight[6];

    Vector2D topLeft[6];

    Vector2D TopRight[6];


  public:
    Collectables(Vector2D center, unsigned int fontSize);

    void draw(Interface & interface) override;

    Vector2D collideWith(Ball & ball, float collisionTime) override;

    void updateScore(Ball & ball, Score & score) override;

};