
#include "ThrustBumper.h"

ThrustBumper::ThrustBumper(Vector2D center, float radius, float speedingFactor): Bumper(radius,center), speedingFactor(speedingFactor), collidedLastFrame(false){
}

void ThrustBumper::draw(Interface& interface) {

    interface.drawThrustBumper(center, radius);
}

Vector2D ThrustBumper::collideWith(Ball& ball, float collisionTime) {

	if (!collidedLastFrame)
	{
		float distanceToBall = distance2points(center,ball.getCenter());
		if (abs(distanceToBall - radius) < ball.getRadius())
		{
			collidedLastFrame = true;

			return Vector2D{ ball.getVelocity() * -2.f * speedingFactor } / collisionTime;
		}
	}
	collidedLastFrame = false;
	return Vector2D{ 0, 0 }; // if no collision}
}

