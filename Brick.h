#ifndef BOX2DSFML_BRICK_H
#define BOX2DSFML_BRICK_H
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height, float angle, sf::Color color, b2World& world, bool rigid=false);
    void update();
    bool isVisible();
    void rotate(float rotDeg);
    void translate(float x, float y);
    const sf::RectangleShape& getShape() { return shape; }
    b2Body* getBody() { return body; }

private:
    sf::RectangleShape shape;  // SFML graphical object representation
    b2Body* body;              // Box2D physical object representation
};


#endif //BOX2DSFML_BRICK_H
