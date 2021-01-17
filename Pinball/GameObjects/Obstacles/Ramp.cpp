
#include "Ramp.h"

Ramp::Ramp(FlipperType type, float height): type(type), height(height), collidedLastFrame(false) 
{

    if (type == LEFT)
    {
        flipperPoint = { layout.GAME_WIDTH / 2.f - (layout.FLIPPER_LENGTH + layout.FLIPPERS_DISTANCE / 2.f) + layout.FLIPPER_MINOR_RADIUS, layout.GAME_HEIGHT - 50.f - layout.FLIPPER_MAJOR_RADIUS};
    }
    else
    {
        flipperPoint = { layout.GAME_WIDTH / 2.f + (layout.FLIPPER_LENGTH + layout.FLIPPERS_DISTANCE / 2.f) - layout.FLIPPER_MINOR_RADIUS, layout.GAME_HEIGHT - 50.f - layout.FLIPPER_MAJOR_RADIUS };

    }
}

void Ramp::draw(Interface& interface) {

    interface.drawRamp(type, flipperPoint, height);
}

Vector2D Ramp::collideWith(Ball& ball, float collisionTime) {

    Vector2D highestPoint= (type==LEFT) ? Vector2D{ 0, flipperPoint.y - height } : Vector2D{ layout.GAME_WIDTH, flipperPoint.y - height };
   
    Vector2D tilt = flipperPoint - highestPoint;
    tilt = tilt / tilt.magnitude(); // to move the ball along the tilted ramp
    float distanceToBall = distanceToSegment(ball.getCenter(), flipperPoint, highestPoint);

    if (!collidedLastFrame && distanceToBall < ball.getRadius())
    {

        collidedLastFrame = true;
        return (ball.getVelocity() * (-1.f) + tilt * ball.getVelocity().magnitude()) / collisionTime;
    }
    else
    {

        collidedLastFrame = false;
        return Vector2D{ 0, 0 }; // if no collision
    }
}

