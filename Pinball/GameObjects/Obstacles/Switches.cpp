
#include "Switches.h"

Switches::Switches(Vector2D position, float length):position(position), length(length) {
}

Vector2D Switches::collideWith(Ball& ball, float collisionTime) {

	if (!alreadyPassed) {
		float distanceToBall = distanceToSegment(ball.getCenter(), { position.x,position.y }, { position.x + length,position.y });
		if (distanceToBall < ball.getRadius()) {
			alreadyPassed = true;
			return (ball.getVelocity() * -2.f)/collisionTime;
		}

	}

    return Vector2D {0, 0};  
}

void Switches::draw(Interface& interface) {

	interface.drawSwitches(position,length);

}

