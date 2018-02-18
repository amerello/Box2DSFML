#ifndef BOX2DSFML_BRICK_H
#define BOX2DSFML_BRICK_H
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "PhysicalObject.h"

class Brick  : public PhysicalObject {
public:
    Brick(float x, float y, float width, float height, float angle, const sf::Color& color, b2World& world, bool rigid=false);
};


#endif //BOX2DSFML_BRICK_H
