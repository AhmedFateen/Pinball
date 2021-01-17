#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Defs.h"

// Represents the game interface
// This class is the ONLY one that interacts with the user
// This class is also the ONLY one aware of the graphics library being used
// That is, if the graphics library was to be changes, this class is the only thing to be changed
class Interface
{
private:
    sf::RenderWindow window;  // Represents the game window
    const sf::Color  // Colors used for drawing (can change the whole theme of the game)
        backgroundColor = sf::Color::Black,
        outlineColor = sf::Color::Black,
        ballFillColor = sf::Color::White,
        flipperFillColor = sf::Color::White;
    const float outlineThickness = -2.0f;  // Negative sign means inwards

public:
    Interface();  // Constructor
    void getControls(bool & exit, bool & left, bool & right);  // Detects the buttons pressed

    void clear();  // Clears the frame (first step in rendering a new frame)

    void drawPopBumper(Vector2D center, float radius); // Draws a Pop Bumper
    void drawSpeedBooster(Vector2D center, float radius); // Draws a Speed Booster
    void drawScoreMultiplier(Vector2D center, float radius, unsigned multiplier); // Draws a Score Multiplier
    void drawGate(Vector2D point, float length); //Draws a Gate
    void drawRamp(FlipperType type, Vector2D center, float height);

    void drawThrustBumper(Vector2D center, float radius); // drawing the thrust bumper
    void drawCollectables(Vector2D center,const char character[], unsigned fontSize,bool ballSteps[],Vector2D* bottomLeft, Vector2D* bottomRight, Vector2D* topLeft,Vector2D* topRight);

    void drawLiveScore(float width, float height, int liveScore);

    void drawVibraniumBumper(Vector2D position, float radius);
    void drawKickers(Vector2D cornerPoint, Vector2D leftPoint, Vector2D bottomPoint);

    void drawSwitches(Vector2D position, float length);

    void drawCeiling(float position);

    void drawBullseye(Vector2D center, float radius);

    void drawGameOver(int score);




    void display();  // Displays the frame (last step in rendering a new frame)

    void drawBall(Vector2D center, float radius);  // Draws a ball
    void drawFlipper(FlipperType type, Vector2D center, float length, float angle, float majorRadius, float minorRadius);  // Draws a flipper
    void drawWall(float position);  // Draws a vertical wall





};
