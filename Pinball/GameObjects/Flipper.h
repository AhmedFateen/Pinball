#pragma once

#include "Drawable.h"
#include "Collidable.h"


// Represents a (controllable) flipper
class Flipper : public Drawable, private Collidable {
  private:
    // Left or right flipper
    FlipperType type;

    // Center of rotation
    Vector2D center;

    // Flipper length
    float length;

    // Angle of rotation
    float angle;

    // The radius of the rotation end
    float majorRadius;

    // The radius of the other end
    float minorRadius;

    const float INITIAL_LEFT_FLIPPER_ANGLE=  25.f;

    // No need to take them from user
    const float INITIAL_RIGHT_FLIPPER_ANGLE=  -25.f;

    const float MAXIMUM_FLIPPER_ANGLE=  35.f;

    const float RATE_OF_CHANGE_OF_FLIPPER_ANGLE=  8.f;


  public:
    // The angle should probably be removed from the constructor after adding the controls ----- removed
    Flipper(FlipperType type, Vector2D center, float length, float majorRadius, float minorRadius);

    Vector2D collideWith(Ball & ball, float collisionTime) override;

    void draw(Interface & interface) override;

    void moveFlipper();

    void resetAngle();

};
