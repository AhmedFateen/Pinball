
#include "Wall.h"

Wall::Wall(float position): position(position), collidedLastFrame(false) {
}

void Wall::draw(Interface& interface) {
    interface.drawWall(position);
}

Vector2D Wall::collideWith(Ball& ball, float collisionTime) {
    if(!collidedLastFrame && abs(position - ball.getCenter().x) < ball.getRadius())
    {
        collidedLastFrame = true;
        return Vector2D {ball.getVelocity().x * -2, 0} / collisionTime;
    }
    else
    {
        collidedLastFrame = false;
        return Vector2D {0, 0};
    }
}

