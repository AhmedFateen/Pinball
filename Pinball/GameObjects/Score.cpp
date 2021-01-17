
#include "Score.h"

Score::Score(float width, float height): width(width), height(height) {
}

int Score::getScore() {

	return liveScore;
}

void Score::setScore(unsigned newScore) {

	liveScore = newScore;
}

void Score::draw(Interface& interface) {

	interface.drawLiveScore(width, height, liveScore);
}

