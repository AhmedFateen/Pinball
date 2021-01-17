#pragma once


#include "../Drawable.h"
#include "../Collidable.h"
#include "../Score.h"

// An abstract class representing an obstacle
class Obstacle : public Drawable, public Collidable {
  public:
     virtual void updateScore(Ball & ball, Score & score) {};

};
