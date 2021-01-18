
#include "Flipper.h"

Flipper::Flipper(FlipperType type, Vector2D center, float length, float majorRadius, float minorRadius):
    type(type), center(center), length(length), majorRadius(majorRadius), minorRadius(minorRadius)

{
    if (type == LEFT)
    {
        angle = INITIAL_LEFT_FLIPPER_ANGLE;
    }
    else
    {
        angle = INITIAL_RIGHT_FLIPPER_ANGLE;
    }
}

Vector2D Flipper::collideWith(Ball& ball, float collisionTime) {
    Vector2D endOfFlipper;
    if (type == LEFT)
    {
        endOfFlipper = { center.x + length * cos(radians(angle)), center.y + length * sin(radians(angle)) }; 
    }
    else
    {
        endOfFlipper = { center.x - length * cos(radians(angle)), center.y - length * sin(radians(angle)) };

    }
    Vector2D tilt= endOfFlipper - center;
    tilt = tilt / tilt.magnitude(); // to move the ball along the tilted ramp
    float distanceToBall;
    distanceToBall= distanceToSegment(ball.getCenter(), center, endOfFlipper);
    if (abs(distanceToBall - majorRadius) < ball.getRadius())
    {

        if (type == LEFT)
        {
            if (angle == INITIAL_LEFT_FLIPPER_ANGLE)
            {
                return (ball.getVelocity() * (-1.f) + tilt *ball.getVelocity().magnitude()) / collisionTime; // ball rolls

            }
            else
            {
                return (ball.getVelocity() * (-1.f) + Vector2D{ tilt.y,-tilt.x } *1.06f * ball.getVelocity().magnitude()) / collisionTime; // {tilt.y,-tilt.x} is the relevant normal to the tilt.
            }
        }
        else // type RIGHT
        {
            if (angle == INITIAL_RIGHT_FLIPPER_ANGLE)
            {
                return (ball.getVelocity() * (-1.f) + tilt *ball.getVelocity().magnitude()) / collisionTime; // ball rolls

            }
            else
            {
                return (ball.getVelocity() * (-1.f) + Vector2D{ -tilt.y,tilt.x } *ball.getVelocity().magnitude()) / collisionTime;
            }
           
        }
    }
    else
    {
        return { 0,0 };
    }
}

void Flipper::draw(Interface& interface) {
    interface.drawFlipper(type, center, length, angle, majorRadius, minorRadius);
}

void Flipper::moveFlipper() {
    if (type == LEFT)
    {
        if (angle > -MAXIMUM_FLIPPER_ANGLE)
        angle -= RATE_OF_CHANGE_OF_FLIPPER_ANGLE;
    }
    else if (type == RIGHT)
    {
        if (angle < MAXIMUM_FLIPPER_ANGLE)

        angle += RATE_OF_CHANGE_OF_FLIPPER_ANGLE;
    }
}

void Flipper::resetAngle() {
    if (type == LEFT)
    {
        angle = INITIAL_LEFT_FLIPPER_ANGLE;
    }
    if (type == RIGHT)
    {
        angle = INITIAL_RIGHT_FLIPPER_ANGLE;
    }
}

