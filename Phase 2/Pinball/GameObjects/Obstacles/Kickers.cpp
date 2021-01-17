
#include "Kickers.h"

Kickers::Kickers(float length):length(length) , collidedLastFrame(false){
	leftPoint = { cornerPoint.x - length,cornerPoint.y };
	bottomPoint = { cornerPoint.x,cornerPoint.y + length };

}

void Kickers::draw(Interface& interface) {

	interface.drawKickers(cornerPoint,leftPoint,bottomPoint);
}

Vector2D Kickers::collideWith(Ball& ball, float collisionTime) {

	if (!collidedLastFrame)
	{
		float distanceToBall = distanceToSegment(ball.getCenter(), leftPoint,bottomPoint);
		Vector2D tilt = leftPoint-bottomPoint;
		tilt = tilt / tilt.magnitude();
		Vector2D normal = { tilt.y,-tilt.x };
		if (distanceToBall < ball.getRadius())
		{
			collidedLastFrame = true;
			return Vector2D{ ball.getVelocity() * (-1.f) + normal * ball.getVelocity().magnitude() }/collisionTime;
		}
	}
	collidedLastFrame = false;
	return Vector2D{ 0, 0 };
}

