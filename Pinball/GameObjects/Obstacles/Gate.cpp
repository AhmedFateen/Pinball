
#include "Gate.h"

Gate::Gate(Vector2D center, float length): point(center), length(length) {
}

Vector2D Gate::collideWith(Ball& ball, float collisionTime) {

	static Vector2D p2 = { point.x + length,point.y };
	float distanceToBall = distanceToSegment(ball.getCenter(), point, p2);
	if (distanceToBall < ball.getRadius() && ball.getVelocity().y > 0) // ball moving downwards
	{
		{
			return Vector2D{ 0, ball.getVelocity().y * -2.f } / collisionTime;
		}

	}
	else
	{
		return { 0,0 };
	}


}

void Gate::draw(Interface& interface) {

	interface.drawGate(point, length);
}

