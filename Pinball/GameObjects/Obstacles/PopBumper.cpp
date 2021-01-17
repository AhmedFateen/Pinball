
#include "PopBumper.h"
#include "Ball.h"

PopBumper::PopBumper(Vector2D center, float radius): Bumper(radius,center), collidedLastFrame(false) {
}

//Constructor
void PopBumper::draw() {

	interface.drawPopBumper(center, radius);
}

// Draws a pop bumper
Vector2D PopBumper::collideWith() {

	if (!collidedLastFrame)
	{
		float distanceToBall = distance2points(center,ball.getCenter());
		if (distanceToBall - radius/2.f < ball.getRadius()) //radius/2 is the minor radius;
		{
			collidedLastFrame = true;
			return Vector2D{ ball.getVelocity() * -2.f } / collisionTime;
		}
	}
		collidedLastFrame = false;
		return Vector2D{ 0, 0 }; // if no collision
}

