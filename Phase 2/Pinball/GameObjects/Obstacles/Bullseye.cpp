#include "Bullseye.h"

void Bullseye::resetBools() {

	justEntered[0] = false;
	justEntered[1] = false;
	justEntered[2] = false;
	justEntered[3] = false;
	justEntered[4] = false;
	justEntered[5] = false;
}

Bullseye::Bullseye(Vector2D center, float radius) : center(center), radius(radius)
{


}

//Constructor
void Bullseye::draw(Interface& interface) {

	interface.drawBullseye(center, radius);
}

Vector2D Bullseye::collideWith(Ball& ball, float collisionTime) {

	return Vector2D{ 0, 0 }; // no effect on ball
}

void Bullseye::updateScore(Ball& ball, Score& score) {

	float distanceToBall = distance2points(center, ball.getCenter());
	for (int i = 0; i < 6; ++i)
	{
		if (!justEntered[i] && (distanceToBall - radius * (4.f + 3*i) / 19.f) < ball.getRadius()) // ratio according to some dartboard standards
		{
			score.setScore(score.getScore() + increaser[i]);
			justEntered[i] = true;
		}
	}
	if (distanceToBall-ball.getRadius() > radius)
	{
		resetBools();
	}
}

