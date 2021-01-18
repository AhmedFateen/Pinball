#pragma once

#include "Drawable.h"

class Ball : public Drawable {
  private:
    // Radius of the ball
    float radius=  layout.BALL_RADIUS;

    // The instantaneous center of the ball
    Vector2D center;

    // The instantaneous velocity of the ball
    Vector2D velocity;


  public:
    explicit Ball(Vector2D center = layout.INITIAL_CENTER, Vector2D velocity = layout.INITIAL_VELOCITY);

    float getRadius() const;

    Vector2D getCenter() const;

    Vector2D getVelocity() const;

    void move(Vector2D acceleration, float time);

    // Simulates the ball's motion under uniform acceleration for a period of time
    void draw(Interface & interface) override;

};
