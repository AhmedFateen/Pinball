
#include "Collectables.h"

Collectables::Collectables(Vector2D center, unsigned int fontSize) : center(center), fontSize(fontSize)
{

}

void Collectables::draw(Interface& interface) {

	interface.drawCollectables(center, character, fontSize, ballSteps,bottomLeft,bottomRight,topLeft,TopRight);
}

Vector2D Collectables::collideWith(Ball& ball, float collisionTime) {

	return { 0,0 };
}

void Collectables::updateScore(Ball& ball, Score& score) {

	for (int i = 0; i < 6; ++i)

	{
		if (!ballSteps[i] && ball.getCenter().x > bottomLeft[i].x&& ball.getCenter().x < bottomRight[i].x && ball.getCenter().y>topLeft[i].y&& ball.getCenter().y < bottomLeft[i].y)
		{
			ballSteps[i] = true;
			score.setScore(score.getScore() + 5);
		}

	}
}

