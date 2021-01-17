#include "PopBumper.h"

PopBumper::PopBumper(Vector2D center, float radius): Bumper(radius,center), collidedLastFrame(false) {}


void PopBumper::draw(Interface& interface)
{
	interface.drawPopBumper(center, radius);
}
Vector2D PopBumper::collideWith(Ball& ball, float collisionTime)
{
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
