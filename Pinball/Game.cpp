
#include "Game.h"


Game::Game() : leftFlipper(LEFT, Vector2D{ layout.GAME_WIDTH / 2.0f - (layout.FLIPPER_LENGTH + layout.FLIPPERS_DISTANCE / 2.0f), layout.GAME_HEIGHT - 50.0f }, layout.FLIPPER_LENGTH, layout.FLIPPER_MAJOR_RADIUS, layout.FLIPPER_MINOR_RADIUS),
rightFlipper(RIGHT, Vector2D{ layout.GAME_WIDTH / 2.0f + (layout.FLIPPER_LENGTH + layout.FLIPPERS_DISTANCE / 2.0f), layout.GAME_HEIGHT - 50.0f }, layout.FLIPPER_LENGTH, layout.FLIPPER_MAJOR_RADIUS, layout.FLIPPER_MINOR_RADIUS), score(layout.GAME_WIDTH/10,layout.GAME_HEIGHT/10)
{
    O = new Obstacle * [layout.number_of_obstacles];
    std::string lineRead;
    std::ifstream inputFile("layout.txt");
    std::string dummyLine;
    std::istringstream iss(lineRead);
    for (unsigned i = 0; i < 7; ++i)
    {
        getline(inputFile, dummyLine);
    }

    for (unsigned i = 0; i < layout.number_of_obstacles; ++i)
    {
        getline(layout.inputFile,lineRead);
        std::string name;
        iss.clear(); iss.str(lineRead);
        std::string firstParameter; // might be non-float, like LEFT OR RIGHT;
        float secondParameter = 0.f,thirdParameter=0.f, fourthParameter=0.f;
        iss >> name >> firstParameter >> secondParameter >> thirdParameter >> fourthParameter;
    
    

        if (name == "WALL" || name == "Wall")
        {
            O[i] = new Wall(std::stof(firstParameter));
        }
        else if (name == "POP_BUMPER")
        {
            O[i] = new PopBumper({ std::stof(firstParameter),secondParameter }, thirdParameter);
        }
        else if (name == "VIBRANIUM_BUMPER")
        {
            O[i] = new VibraniumBumper({ std::stof(firstParameter),secondParameter }, thirdParameter);
        }
        else if (name == "CEILING" || name == "Ceiling")
        {
            O[i] = new Ceiling(std::stof(firstParameter));
        }
        else if (name == "SPEED_BOOSTER")
        {
            O[i] = new SpeedBooster({ std::stof(firstParameter),secondParameter }, thirdParameter);
        }
        else if (name == "SCORE_MULTIPLIER")
        {
            O[i] = new ScoreMultiplier({ std::stof(firstParameter),secondParameter }, thirdParameter, static_cast<unsigned>(fourthParameter));
        }
        else if (name == "GATE")
        {
            O[i] = new Gate({ std::stof(firstParameter),secondParameter }, thirdParameter);
        }
        else if (name == "KICKERS" || name == "KICKER")
        {
            O[i] = new Kickers(std::stof(firstParameter));
        }
        else if (name == "SWITCHES" || name == "SWITCH")
        {
            O[i] = new Switches({std::stof(firstParameter),secondParameter}, thirdParameter);
        }
        else if (name == "RAMP")
        {
            FlipperType type;
            if (firstParameter == "RIGHT")
            {
                type = RIGHT;
            }
            else
            {
                type = LEFT;
            }
            O[i] = new Ramp(type, secondParameter);
        }
        else if (name == "COLLECTABLES")
        {
            O[i] = new Collectables({ std::stof(firstParameter),secondParameter }, static_cast<unsigned>(thirdParameter));
        }
        else if (name == "THRUST_BUMPER")
        {
            O[i] = new ThrustBumper({ std::stof(firstParameter),secondParameter }, thirdParameter, fourthParameter);
        }
        else if (name == "BULLSEYE")
        {
            O[i] = new Bullseye({ std::stof(firstParameter),secondParameter }, thirdParameter);
        }

    }


    lastFrame = high_resolution_clock::now();
    exit = left = right = false;
}

void Game::readInterfaceInput()
{
    interface.getControls(exit, left, right);
}

void Game::simulate()
{
    // Measuring time elapsed in-between frames
    high_resolution_clock::time_point thisFrame = high_resolution_clock::now();
    duration<float> timeSpan = duration_cast<duration<float>>(thisFrame - lastFrame);
    lastFrame = thisFrame;
    float deltaTime = timeSpan.count();  // Delta time in seconds

    Vector2D resultantAcceleration = {0, layout.GRAVITY};  // Starting with gravity as the first acceleration contributer
    
    for (unsigned i = 0; i < layout.number_of_obstacles; ++i)
    {
        resultantAcceleration+=O[i]->collideWith(ball,deltaTime);
        O[i]->updateScore(ball, score);
    }
    resultantAcceleration += leftFlipper.collideWith(ball, deltaTime);
    resultantAcceleration += rightFlipper.collideWith(ball, deltaTime);
    ball.move(resultantAcceleration, deltaTime);
}

void Game::updateInterfaceOutput()
{
    interface.clear();

    leftFlipper.draw(interface);
    rightFlipper.draw(interface);
    score.draw(interface);

    for (unsigned i = 0; i < layout.number_of_obstacles;++i)
    {
        O[i]->draw(interface);
    }
    ball.draw(interface); //We need the ball at the end to stay visible
    if (GameOver())
    {
        interface.drawGameOver(score.getScore());
    }
    interface.display();
}

bool Game::exited()
{
    return exit;

}
void Game::moveFlippers()
{
    if (left)
    {
        leftFlipper.moveFlipper();
    }
    if (right)
    {
        rightFlipper.moveFlipper();
    }
    if (!left)
    {
        leftFlipper.resetAngle();
    }
    if (!right)
    {
        rightFlipper.resetAngle();
    }
}
Game::~Game()
{
    for (unsigned i = 0; i < layout.number_of_obstacles; ++i) // delete dynamically allocated objects
    {
        delete O[i];
    }
    delete[] O; 
}
bool Game::GameOver()
{
    if (ball.getCenter().y > layout.GAME_HEIGHT)
    {
        return true;
    }
    else
    {
        return false;
    }
}