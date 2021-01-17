
#include "ScoreMultiplier.h"

ScoreMultiplier::ScoreMultiplier(Vector2D center, float radius, unsigned multiplier) : center(center), radius(radius), multiplier(multiplier), collidedLastFrame(false) {
}

//Constructor
void ScoreMultiplier::draw(Interface& interface) {

	interface.drawScoreMultiplier(center, radius,multiplier);
}

Vector2D ScoreMultiplier::collideWith(Ball& ball, float collisionTime) {

	if (!collidedLastFrame)
	{
		float distanceToBall = distance2points(center,ball.getCenter());
		if (distanceToBall - radius < ball.getRadius())
		{
			collidedLastFrame = true;

			return Vector2D{ ball.getVelocity() * -2.f } / collisionTime;
		}
	}
	collidedLastFrame = false;
	return Vector2D{ 0, 0 }; // if no collision
}

void ScoreMultiplier::updateScore(Ball& ball, Score& score) {

	if (collidedLastFrame)
	{
		score.setScore(score.getScore() * multiplier);
	}
}

