#include "Interface.h"

void resizeImage(const sf::Image original, sf::Image& resized)
{
    const sf::Vector2u originalSize = original.getSize();
    const sf::Vector2u newSize = resized.getSize();
    for (unsigned y = 0u; y < newSize.y; ++y)
    {
        for (unsigned x = 0u; x < newSize.x; ++x)
        {
            unsigned originalX = static_cast<unsigned>(static_cast<float>(x) / newSize.x * originalSize.x); // basically x * widthA/widthB
            unsigned originalY = static_cast<unsigned>(static_cast<float>(y) / newSize.y * originalSize.y); //  y * widthA/widthB
            resized.setPixel(x, y, original.getPixel(originalX, originalY));
        }
    }
}

Interface::Interface()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 2;  // Remove this line if the game was too laggy //
    window.create(sf::VideoMode(static_cast<unsigned>(layout.GAME_WIDTH), static_cast<unsigned>(layout.GAME_HEIGHT)), "Pinball", sf::Style::Titlebar, settings);
    window.setVerticalSyncEnabled(true);
}

void Interface::getControls(bool & exit, bool & left, bool & right)
{
    sf::Event event;
    while (window.pollEvent(event));
    exit = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}

void Interface::clear()
{
    window.clear(backgroundColor);

    sf::RectangleShape screenClearer;
    screenClearer.setSize(sf::Vector2f(layout.GAME_WIDTH, layout.GAME_HEIGHT));
    screenClearer.setFillColor(backgroundColor);
    window.draw(screenClearer);

}

void Interface::display()
{
    window.display();
}

void Interface::drawBall(Vector2D center, float radius)
{
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setOutlineThickness(outlineThickness);
    circle.setOutlineColor(outlineColor);
    circle.setFillColor(ballFillColor);
    circle.setPosition(center.x, center.y);
    window.draw(circle);
}

void Interface::drawFlipper(FlipperType type, Vector2D center, float length, float angle, float majorRadius, float minorRadius)
{
    float flip = type == LEFT ? 1.0f : -1.0f;

    // Draw the major circle outline
    sf::CircleShape majorCircleOutline(majorRadius);
    majorCircleOutline.setOutlineThickness(outlineThickness);
    majorCircleOutline.setOutlineColor(outlineColor);
    majorCircleOutline.setFillColor(flipperFillColor);
    majorCircleOutline.setOrigin(majorRadius, majorRadius);
    majorCircleOutline.setPosition(center.x, center.y);
    window.draw(majorCircleOutline);

    // Draw the minor circle outline
    sf::CircleShape minorCircleOutline(minorRadius);
    minorCircleOutline.setOutlineThickness(outlineThickness);
    minorCircleOutline.setOutlineColor(outlineColor);
    minorCircleOutline.setFillColor(flipperFillColor);
    minorCircleOutline.setOrigin(minorRadius - length, minorRadius);
    minorCircleOutline.setPosition(center.x, center.y);
    minorCircleOutline.rotate(angle);
    minorCircleOutline.setScale(flip, 1.0f);
    window.draw(minorCircleOutline);

    // Draw the convex shape connecting the two circles
    sf::ConvexShape convexBody(4);
    convexBody.setPoint(0, sf::Vector2f(0, -outlineThickness));
    convexBody.setPoint(1, sf::Vector2f(0, 2 * majorRadius + outlineThickness));
    convexBody.setPoint(2, sf::Vector2f(length, majorRadius + minorRadius + outlineThickness));
    convexBody.setPoint(3, sf::Vector2f(length, majorRadius - minorRadius - outlineThickness));
    convexBody.setFillColor(flipperFillColor);
    convexBody.setOrigin(0, majorRadius);
    convexBody.setPosition(center.x, center.y);
    convexBody.setRotation(angle);
    convexBody.setScale(flip, 1.0f);
    window.draw(convexBody);

    // Draw the inside circle
    sf::CircleShape insideCircle(minorRadius);
    insideCircle.setFillColor(outlineColor);
    insideCircle.setOrigin(minorRadius, minorRadius);
    insideCircle.setPosition(center.x, center.y);
    window.draw(insideCircle);

    // Draw the top line
    sf::ConvexShape topLine(4);
    topLine.setPoint(0, sf::Vector2f(0, -outlineThickness));
    topLine.setPoint(1, sf::Vector2f(0, 0));
    topLine.setPoint(2, sf::Vector2f(length, majorRadius - minorRadius));
    topLine.setPoint(3, sf::Vector2f(length, majorRadius - minorRadius - outlineThickness));
    topLine.setFillColor(outlineColor);
    topLine.setOrigin(0, majorRadius);
    topLine.setPosition(center.x, center.y);
    topLine.setRotation(angle);
    topLine.setScale(flip, 1.0f);
    window.draw(topLine);

    // Draw the bottom line
    sf::ConvexShape bottomLine(4);
    bottomLine.setPoint(0, sf::Vector2f(0, 2 * majorRadius));
    bottomLine.setPoint(1, sf::Vector2f(0, 2 * majorRadius + outlineThickness));
    bottomLine.setPoint(2, sf::Vector2f(length, majorRadius + minorRadius + outlineThickness));
    bottomLine.setPoint(3, sf::Vector2f(length, majorRadius + minorRadius));
    bottomLine.setFillColor(outlineColor);
    bottomLine.setOrigin(0, majorRadius);
    bottomLine.setPosition(center.x, center.y);
    bottomLine.setRotation(angle);
    bottomLine.setScale(flip, 1.0f);
    window.draw(bottomLine);
}

void Interface::drawWall(float position)
{
    sf::Vertex line[] =
            {
                    sf::Vertex(sf::Vector2f(position, 0), outlineColor),
                    sf::Vertex(sf::Vector2f(position, layout.GAME_HEIGHT), outlineColor)
            };
    window.draw(line, 2, sf::Lines);
}
void Interface::drawPopBumper(Vector2D center, float radius)
{
    sf::CircleShape outerCircle(radius);
    sf::CircleShape innerCircle(radius / 2.f);
    outerCircle.setFillColor(sf::Color::Cyan);
    outerCircle.setOutlineThickness(1.0);
    outerCircle.setOutlineColor(sf::Color::Black);
    outerCircle.setOrigin(outerCircle.getRadius(), outerCircle.getRadius());
    outerCircle.setPosition(center.x, center.y);

    window.draw(outerCircle);
    innerCircle.setFillColor(sf::Color::Magenta);
    innerCircle.setOutlineThickness(1.0);
    innerCircle.setOutlineColor(sf::Color::Black);
    innerCircle.setOrigin(innerCircle.getRadius(), innerCircle.getRadius());
    innerCircle.setPosition(center.x, center.y);
    window.draw(innerCircle);
}
void Interface::drawSpeedBooster(Vector2D center, float radius)
{
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(242, 125, 12));
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(center.x, center.y);
    window.draw(circle);

    static sf::Image resized;
    static bool initialized = false;
    const unsigned size = static_cast<unsigned>(radius * 1.5f);

    if (!initialized)
    {
        sf::Image original;
        resized.create(size, size);
        if (original.loadFromFile("Images/bolt.png"))
        {
            resizeImage(original, resized);
        }
        initialized = true;
    }
    sf::Texture texture;
    texture.loadFromImage(resized);
    sf::Sprite sprite(texture);
    sprite.setOrigin(size / 2.f, size / 2.f);
    sprite.setPosition(center.x, center.y);
    window.draw(sprite);
          
}
void Interface::drawScoreMultiplier(Vector2D center, float radius,unsigned multiplier)
{
    sf::CircleShape special(radius, 7);
    special.setFillColor(sf::Color::Yellow);
    special.setOrigin(special.getRadius(), special.getRadius());
    special.setPosition(center.x, center.y);
    window.draw(special);
    sf::Font arial;

    if (!arial.loadFromFile("Fonts/arial.ttf"))
    {
        return;
    }
    sf::Text text;
    text.setFont(arial);
    text.setString("x"+ std::to_string(multiplier));
    text.setCharacterSize(static_cast<unsigned>(radius/1.2f));
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(center.x,center.y);
    window.draw(text);
}
void Interface::drawGate(Vector2D point, float length)
{
    sf::ConvexShape polygon1,polygon2,polygon3;
    polygon1.setPointCount(4);
    polygon2.setPointCount(4);
    polygon3.setPointCount(4);

    polygon1.setPoint(0, sf::Vector2f(point.x, point.y));
    polygon1.setPoint(1, sf::Vector2f(point.x , point.y + length/4.f));
    polygon1.setPoint(2, sf::Vector2f(point.x + length, point.y + length / 4.f));
    polygon1.setPoint(3, sf::Vector2f(point.x + length, point.y)); 

    polygon2.setPoint(0, sf::Vector2f(point.x, point.y + length/4.f));
    polygon2.setPoint(1, sf::Vector2f(point.x, point.y + length / 2.f));
    polygon2.setPoint(2, sf::Vector2f(point.x + 1.f / 6.f * length, point.y + length / 2.f));
    polygon2.setPoint(3, sf::Vector2f(point.x + 1.f / 6.f * length, point.y + length / 4.f));

    polygon3.setPoint(0, sf::Vector2f(point.x + 5.f / 6.f * length, point.y + length / 4.f));
    polygon3.setPoint(1, sf::Vector2f(point.x + 5.f / 6.f * length, point.y + length / 2.f));
    polygon3.setPoint(2, sf::Vector2f(point.x + length, point.y + length / 2.f));
    polygon3.setPoint(3, sf::Vector2f(point.x + length, point.y + length / 4.f));

    polygon1.setFillColor(sf::Color(128, 128, 128));
    polygon2.setFillColor(sf::Color(128, 128, 128));
    polygon3.setFillColor(sf::Color(128, 128, 128));

    window.draw(polygon1);
    window.draw(polygon2);
    window.draw(polygon3);

}

void Interface::drawRamp(FlipperType type, Vector2D center, float height)
{
    if (type == LEFT)
    {

        sf::ConvexShape leftTriangle;
        leftTriangle.setPointCount(3);

        leftTriangle.setPoint(0, sf::Vector2f(center.x, center.y));
        leftTriangle.setPoint(1, sf::Vector2f(0, center.y));
        leftTriangle.setPoint(2, sf::Vector2f(0, center.y - height));

        leftTriangle.setFillColor(sf::Color(169, 169, 169));

        window.draw(leftTriangle);
    }
    else if (type == RIGHT)
    {

        sf::ConvexShape rightTriangle;
        rightTriangle.setPointCount(3);

        rightTriangle.setPoint(0, sf::Vector2f(center.x, center.y));
        rightTriangle.setPoint(1, sf::Vector2f(layout.GAME_WIDTH, center.y));
        rightTriangle.setPoint(2, sf::Vector2f(layout.GAME_WIDTH, center.y - height));

        rightTriangle.setFillColor(sf::Color(169, 169, 169));

        window.draw(rightTriangle);
    }
}
    void Interface::drawThrustBumper(Vector2D center, float radius)
    {
        sf::CircleShape circle(radius);
        circle.setOrigin(radius, radius);
        circle.setPosition(center.x, center.y);
        circle.setOutlineThickness(0.3f * radius);
        circle.setOutlineColor(sf::Color(128, 128, 128));
        circle.setFillColor(sf::Color(85, 74, 60));

        window.draw(circle);
    }

    void Interface::drawCollectables(Vector2D center, const char character[], unsigned fontSize, bool ballSteps[], Vector2D* bottomLeft, Vector2D* bottomRight, Vector2D* topLeft, Vector2D* topRight) 
    {
        sf::Font arial;

        if (!arial.loadFromFile("Fonts/arial.ttf"))
        {
            return;
        }
        sf::Text T[6];
        for (int i = 0; i < 6; ++i)
        {
            T[i].setFont(arial);
            T[i].setString(character[i]);
            T[i].setCharacterSize(fontSize);
            for (int j = 0; j < 6; ++j)
            {

                if (ballSteps[j])
                {
                    T[j].setFillColor(sf::Color(255, 197, 143)); // Resembles Light
                    T[j].setOutlineThickness(2.f);
                    T[j].setOutlineColor(sf::Color::White);
                }
                else
                {
                    T[j].setFillColor(sf::Color::Blue);
                }
            }
            T[i].setOutlineColor(sf::Color::White);
            T[i].setStyle(sf::Text::Bold);
            sf::FloatRect textRect = T[i].getLocalBounds();
            T[i].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            T[i].setPosition(center.x+layout.GAME_WIDTH/10*(i-2.5f), center.y);
            sf::FloatRect bounds = T[i].getGlobalBounds();
            bottomLeft[i] = { bounds.left,bounds.top + bounds.height };
            topLeft[i] = { bounds.left,bounds.top };
            topRight[i] = { bounds.left + bounds.width,bounds.top };
            bottomRight[i] = { bounds.left + bounds.width,bounds.top + bounds.height };
            window.draw(T[i]);
        }
    }  

    void Interface::drawVibraniumBumper(Vector2D center, float radius) {
        
                sf::CircleShape circle(radius); // circle of certain radius
            circle.setOrigin(radius, radius); // makes the center of the circle to be its origin, where position is set. 
            circle.setPosition(center.x,center.y);
            circle.setOutlineThickness(-0.4f * radius); //Negative means inside
            circle.setOutlineColor(sf::Color(40, 40, 40)); // dark grey
            circle.setFillColor(sf::Color(0,0,60)); // dark blue
        
            window.draw(circle);
        
            static sf::Image resized;

            static bool initialized = false;

            if (!initialized)
            {
                sf::Image original;
                resized.create(static_cast<unsigned>(radius), static_cast<unsigned>(radius));
                if (original.loadFromFile("Images/mask.png"))
                {
                    resizeImage(original, resized);
                }
                initialized = true;
            }
            sf::Texture texture;
            texture.loadFromImage(resized);
            sf::Sprite sprite(texture);
            sprite.setOrigin(radius / 2.f, radius / 2.f);
            sprite.setPosition(center.x, center.y);
            window.draw(sprite);
                
        
    }


    void Interface::drawKickers(Vector2D cornerPoint, Vector2D leftPoint, Vector2D bottomPoint)
    {

        sf::VertexArray triangle(sf::Triangles, 3);

        //// define the position of the triangle's points
        triangle[0].position = sf::Vector2f(cornerPoint.x, cornerPoint.y);
        triangle[1].position = sf::Vector2f(leftPoint.x,leftPoint.y);
        triangle[2].position = sf::Vector2f(bottomPoint.x, bottomPoint.y);


        //// define the color of the triangle's points
        triangle[0].color = sf::Color::Blue;
        triangle[1].color = sf::Color::Yellow;
        triangle[2].color = sf::Color::Green;

        window.draw(triangle);
    }

    void Interface::drawSwitches(Vector2D position, float length)
    {
        sf::RectangleShape line;
        line.setSize(sf::Vector2f(length, 10.f));
        line.setRotation(180.f);
        line.setPosition(position.x , position.y);
        line.setFillColor(sf::Color::Magenta);
        line.setOutlineThickness(-5.0f);
        line.setOutlineColor(sf::Color(6, 249, 249));

        window.draw(line);

    }


    void Interface::drawCeiling(float position)
    {
        sf::Vertex line[] =
        {
                sf::Vertex(sf::Vector2f(0, position), outlineColor),
                sf::Vertex(sf::Vector2f(layout.GAME_WIDTH, position), outlineColor)
        };
        window.draw(line, 2, sf::Lines);
    }
    
    void Interface::drawLiveScore(float width,float height, int liveScore)
    {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(width, height));
        rectangle.setPosition(0, 0); // This time we actually want the origin to be the top left corner!
        rectangle.setFillColor(sf::Color(160, 82, 45));
        window.draw(rectangle);
        sf::Font arial;

        if (!arial.loadFromFile("Fonts/arial.ttf"))
        {
            return;
        }
        sf::Text text;
        text.setFont(arial);
        text.setString(std::to_string(liveScore));
        if (liveScore <= 99)
        {
            text.setCharacterSize(static_cast<unsigned>(height / 1.5f));
        }
        else if (liveScore<=999)// so that the number can be contained within the box
        {
            text.setCharacterSize(static_cast<unsigned>(height / 2.f)); 

        }
        else
        {
            text.setCharacterSize(static_cast<unsigned>(height / 3.f));

        }
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Bold);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(width / 2, height / 2);
        window.draw(text);
    }

    void Interface::drawGameOver(int score)
    {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(layout.GAME_WIDTH/1.2f, layout.GAME_HEIGHT/5.f));
        rectangle.setOrigin(rectangle.getLocalBounds().width / 2,rectangle.getLocalBounds().height/2);
        rectangle.setPosition(layout.GAME_WIDTH/2.f, layout.GAME_HEIGHT / 2.f); // This time we actually want the origin to be the top left corner!
        rectangle.setFillColor(sf::Color(160, 82, 45)); 
        window.draw(rectangle);
        sf::Font arial;

        if (!arial.loadFromFile("Fonts/arial.ttf"))
        {
            return;
        }
        sf::Text text;
        text.setFont(arial);
        text.setCharacterSize(static_cast<unsigned>(layout.GAME_WIDTH / 20));
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Bold);
        text.setString("Game Over! Your score is "+std::to_string(score));
 
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(layout.GAME_WIDTH / 2, layout.GAME_HEIGHT / 2);
        window.draw(text);
    }

    void Interface::drawBullseye(Vector2D center, float radius)
    {
        sf::CircleShape whiteCircle(radius);
        whiteCircle.setOrigin(whiteCircle.getRadius(), whiteCircle.getRadius());
        whiteCircle.setPosition(center.x, center.y);
        whiteCircle.setFillColor(sf::Color::White);
        whiteCircle.setOutlineColor(sf::Color::Black);
        whiteCircle.setOutlineThickness(-2.f);
        window.draw(whiteCircle);

        sf::CircleShape blackCircle(radius*(16.f)/19.f); 
        blackCircle.setOrigin(blackCircle.getRadius(), blackCircle.getRadius());
        blackCircle.setPosition(center.x, center.y);
        blackCircle.setFillColor(sf::Color::Black);
        window.draw(blackCircle);

        sf::CircleShape cyanCircle(radius * (13.f) / 19.f); 
        cyanCircle.setOrigin(cyanCircle.getRadius(), cyanCircle.getRadius());
        cyanCircle.setPosition(center.x, center.y);
        cyanCircle.setFillColor(sf::Color::Cyan);
        window.draw(cyanCircle);

        sf::CircleShape redCircle(radius * (10.f) / 19.f);
        redCircle.setOrigin(redCircle.getRadius(), redCircle.getRadius());
        redCircle.setPosition(center.x, center.y);
        redCircle.setFillColor(sf::Color::Red);
        window.draw(redCircle);

        sf::CircleShape orangeCircle(radius * (7.f) / 19.f);
        orangeCircle.setOrigin(orangeCircle.getRadius(), orangeCircle.getRadius());
        orangeCircle.setPosition(center.x, center.y);
        orangeCircle.setFillColor(sf::Color(255, 165, 0));
        window.draw(orangeCircle);

        sf::CircleShape bullseye(radius * 4.f / 19.f);
        bullseye.setOrigin(bullseye.getRadius(), bullseye.getRadius());
        bullseye.setPosition(center.x, center.y);
        bullseye.setFillColor(sf::Color::Yellow);
        window.draw(bullseye);


    }