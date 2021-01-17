#pragma once

#include "Obstacle.h"

class ScoreMultiplier : public Obstacle {
  private:
    Vector2D center;

    float radius;

    unsigned multiplier;

    bool collidedLastFrame;


  public:
    ScoreMultiplier(Vector2D center, float radius, unsigned multiplier);

    //Constructor
    void draw(Interface & interface);

    Vector2D collideWith(Ball & ball, float collisionTime) override;

    void updateScore(Ball & ball, Score & score) override;

};