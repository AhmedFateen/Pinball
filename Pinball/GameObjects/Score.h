#pragma once

#include "Drawable.h"

class Score : public Drawable {
  private:
    unsigned liveScore= 0u;

    float width;

    float height;


  public:
    Score(float width, float height);

    int getScore();

    void setScore(unsigned newScore);

    void draw(Interface & interface) override;

};
