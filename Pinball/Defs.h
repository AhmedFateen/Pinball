#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>


constexpr float PI_f = 3.1415926535898f;

struct Vector2D  // Represents a 2D vector
{
    float x = 0;  // The first coordinate
    float y = 0;  // The second coordinate
    Vector2D operator*(float scale) { return Vector2D{x * scale, y * scale}; }  // Scalar multiplication
    Vector2D operator/(float scale) { return Vector2D{x / scale, y / scale}; }  // Scalar division
    Vector2D operator+(float scale) { return Vector2D{x + scale, y + scale}; }  // Scalar addition
    Vector2D operator-(float scale) { return Vector2D{x - scale, y - scale}; }  // Scalar subtraction
    Vector2D operator*(const Vector2D & v) { return Vector2D{x * v.x, y * v.y}; }  // Element-wise multiplication
    Vector2D operator/(const Vector2D & v) { return Vector2D{x / v.x, y / v.y}; }  // Element-wise division
    Vector2D operator+(const Vector2D & v) { return Vector2D{x + v.x, y + v.y}; }  // Element-wise addition
    Vector2D operator-(const Vector2D & v) { return Vector2D{x - v.x, y - v.y}; }  // Element-wise subtraction
    Vector2D & operator*=(const Vector2D & v) { x *= v.x; y *= v.y; return *this; }  // Element-wise multiplication
    Vector2D & operator/=(const Vector2D & v) { x /= v.x; y /= v.y; return *this; }  // Element-wise division
    Vector2D & operator+=(const Vector2D & v) { x += v.x; y += v.y; return *this; }  // Element-wise addition
    Vector2D & operator-=(const Vector2D & v) { x -= v.x; y -= v.y; return *this; }  // Element-wise subtraction
    
    float magnitude() const { return sqrt(x * x + y * y); }
};

enum FlipperType { LEFT, RIGHT };

class Layout
{
public:
    float GAME_WIDTH=0.f;
    float GAME_HEIGHT=0.f;
    float BALL_RADIUS = 0.f;
    Vector2D INITIAL_CENTER = { 0.f,0.f };
    Vector2D INITIAL_VELOCITY = { 0.f,0.f };
    float FLIPPER_MAJOR_RADIUS=0.f;
    float FLIPPER_MINOR_RADIUS=0.f;
    float FLIPPER_LENGTH=0;
    float FLIPPERS_DISTANCE=0.f;
    float GRAVITY=0.f;
    unsigned number_of_obstacles=0u;

    std::string lineRead;
    std::ifstream inputFile;
    Layout()
    {
        inputFile.open("layout.txt");
        if (inputFile.bad())
        {
            return;
        }
        getline(inputFile, lineRead);
        float GW=0.f, GH=0.f;
        std::istringstream iss(lineRead);
        iss >> GW >> GH;
        GAME_WIDTH = GW;
        GAME_HEIGHT = GH;
        float BR=0.f;
        getline(inputFile, lineRead);
        iss.clear(); iss.str(lineRead);
        iss >> BR;
        BALL_RADIUS = BR;
        getline(inputFile, lineRead);
        iss.clear();iss.str(lineRead);
        float Cx=0.f, Cy=0.f;
        iss >> Cx >> Cy;
        INITIAL_CENTER.x = Cx;
        INITIAL_CENTER.y = Cy;
        getline(inputFile, lineRead);
        iss.clear();iss.str(lineRead);
        float Vx=0.f, Vy=0.f;
        iss >> Vx >> Vy;
        INITIAL_VELOCITY.x = Vx;
        INITIAL_VELOCITY.y = Vy;
        getline(inputFile, lineRead);
        float MR=0.f, mR=0.f, L=0.f, D=0.f;
        iss.clear();iss.str(lineRead);
        iss >> MR >> mR >> L >> D;
        FLIPPER_MAJOR_RADIUS = MR;
        FLIPPER_MINOR_RADIUS = mR;
        FLIPPER_LENGTH = L;
        FLIPPERS_DISTANCE = D;
        float G=0;
        getline(inputFile, lineRead);
        iss.clear(); iss.str(lineRead);
        iss >> G;
        GRAVITY = G;
        unsigned n=0u;
        getline(inputFile, lineRead);
        iss.clear(); iss.str(lineRead);
        iss >> n;
        number_of_obstacles = n;
    }
};
static Layout layout;

// distance between 2 points
inline float distance2points(const Vector2D p1, const Vector2D p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// returns the dot product of two vectors
inline float dotProduct(const Vector2D v1, const Vector2D v2)
{
    return (v1.x * v2.x + v1.y * v2.y);
}

// first parameter is the point from which distance is calculated, second and third are the points that make the line segment
inline float distanceToSegment(Vector2D point, Vector2D v1, Vector2D v2) 
{
     Vector2D point_v1 = point - v1;
     Vector2D v2_v1 = v2 - v1;
    const float dot = dotProduct(point_v1,v2_v1);
    const float lengthSquared = dotProduct(v2_v1,v2_v1);
    if (lengthSquared == 0) // if v1==v2 or there is a negligible difference according to our precision
    {
        return distance2points(point, v1);
    }
    const float t = std::max(0.f, std::min(1.f, dot/lengthSquared));
    const Vector2D projection = v1 + v2_v1 * t; // if dot <= 0 then the nearest point is v1 (t=0), if dot > lengthSquared, then nearest point is v2 (t=1)   
    return distance2points(point, projection);
}


// convert degrees to radians
inline float radians(const float angleInDegrees)
{
    return (angleInDegrees * PI_f / 180.f);
}