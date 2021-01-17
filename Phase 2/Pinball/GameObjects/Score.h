#pragma once

#include "Drawable.h"

class Score : public Drawable {
  private:
    int liveScore= 0;

    float width;

    float height;


  public:
    Score(float width, float height);

    int getScore();

    void setScore(int newScore);

    void draw(Interface & interface) override;

};
