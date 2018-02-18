#include <iostream>
#include <memory>
#include "Ball.h"

Ball::Ball(float x, float y, float radius, sf::Color color, b2World& world, bool rigid)
        : PhysicalObject(x, y, 0.f, world, rigid) {
    b2CircleShape circle = b2CircleShape();
    circle.m_radius = radius;

    createFixture(circle, rigid);

    // Now we deal with the graphical representation
    shape = std::make_shared<sf::CircleShape>(radius) ;
    resetShape(x, y, 0.f, sf::Vector2f(radius, radius), color);
}
