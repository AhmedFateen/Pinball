#pragma once

#include <chrono>
using namespace std::chrono;

#include "Interface.h"
#include "Defs.h"
#include "GameObjects/Ball.h"
#include "GameObjects/Obstacles/Wall.h"
#include "GameObjects/Flipper.h"
#include "GameObjects/Obstacles/PopBumper.h"
#include "GameObjects/Obstacles/SpeedBooster.h"
#include "GameObjects/Obstacles/ScoreMultiplier.h"
#include "GameObjects/Obstacles/Gate.h"
#include "GameObjects/Obstacles/VibraniumBumper.h"
#include "GameObjects/Obstacles/Ramp.h"

#include "GameObjects/Obstacles/Kickers.h"
#include "GameObjects/Obstacles/Switches.h"
#include "GameObjects/Obstacles/Ceiling.h"

#include "GameObjects/Obstacles/ThrustBumper.h"
#include "GameObjects/Obstacles/Collectables.h"

#include "GameObjects/Score.h"
#include "GameObjects/Obstacles/Bullseye.h"

// Represents a game, keeps track of everything relevant to the game and delegates the tasks to their proper objects
class Game
{
private:
    high_resolution_clock::time_point lastFrame;  // Time point of the last rendered frame
    Interface interface;  // An object representing the game interface
    bool exit, left, right;  // Flags about the user's current controls

    Ball ball;
    Flipper leftFlipper, rightFlipper;  // The right and left flippers
    Score score;
    Obstacle** O= NULL;


    
    
public:
    Game();
    void readInterfaceInput();
    void simulate();
    void updateInterfaceOutput();
    bool exited();
    void moveFlippers();
    bool GameOver();
    ~Game();
};
