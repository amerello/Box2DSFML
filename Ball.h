#ifndef BOX2DSFML_BALL_H
#define BOX2DSFML_BALL_H
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "PhysicalObject.h"

class Ball : public PhysicalObject {
public:
    Ball(float x, float y, float radius, sf::Color color, b2World& world, bool rigid=false);
};


#endif //BOX2DSFML_BALL_H
