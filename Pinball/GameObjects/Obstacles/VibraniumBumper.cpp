
#include "VibraniumBumper.h"

VibraniumBumper::VibraniumBumper(Vector2D center, float radius): Bumper(radius,center) {
}

//constructor
void VibraniumBumper::draw(Interface& interface) {

    interface.drawVibraniumBumper(center, radius);
}

Vector2D VibraniumBumper::collideWith(Ball& ball, float collisionTime) {

	float distanceToBall = distance2points(center,ball.getCenter());
		if (distanceToBall - radius < ball.getRadius())
		{
			return Vector2D{ ball.getVelocity() * -1.f } / collisionTime;
		}
		return { 0,0 }; // if no collision
	
}

