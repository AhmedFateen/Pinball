
#include "SpeedBooster.h"

SpeedBooster::SpeedBooster(Vector2D center, float radius) : center(center), radius(radius) {
}

//Constructor
void SpeedBooster::draw(Interface& interface) {

	interface.drawSpeedBooster(center, radius);
}

// Draws a speed booster
Vector2D SpeedBooster::collideWith(Ball& ball, float collisionTime) {

	
		float distanceToBall = distance2points(center,ball.getCenter());
		if (distanceToBall - radius < ball.getRadius())
		{

			return Vector2D { ball.getVelocity() * 0.2f } / collisionTime;  
		}

		return { 0,0 }; // if no collision
}

