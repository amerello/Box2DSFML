#include <iostream>
#include <memory>
#include "Ball.h"

Ball::Ball(float x, float y, float radius, Type type, b2World& world, bool rigid)
        : PhysicalObject(x, y, 0.f, world, rigid) {
    b2CircleShape circle = b2CircleShape();
    circle.m_radius = radius;

    createFixture(circle, rigid);

    // Now we deal with the graphical representation
    shape = std::make_shared<sf::CircleShape>(radius);
    resetShape(x, y, 0.f, sf::Vector2f(radius, radius));
    setTexture(type);
}

bool Ball::setTexture(Type type) {
    bool success = true;
    sf::IntRect rect = sf::IntRect(199, 199, 403, 403);
    std::string prefix = "textures/balls/";
    switch(type) {
        case BILLIARD_0:
            PhysicalObject::setTexture(prefix + "ball0.png", rect); break;
        case BILLIARD_1:
            PhysicalObject::setTexture(prefix + "ball1.png", rect); break;
        case BILLIARD_2:
            PhysicalObject::setTexture(prefix + "ball2.png", rect); break;
        case BILLIARD_3:
            PhysicalObject::setTexture(prefix + "ball3.png", rect); break;
        case BILLIARD_4:
            PhysicalObject::setTexture(prefix + "ball4.png", rect); break;
        case BILLIARD_5:
            PhysicalObject::setTexture(prefix + "ball5.png", rect); break;
        case BILLIARD_6:
            PhysicalObject::setTexture(prefix + "ball6.png", rect); break;
        case BILLIARD_7:
            PhysicalObject::setTexture(prefix + "ball7.png", rect); break;
        case BILLIARD_8:
            PhysicalObject::setTexture(prefix + "ball8.png", rect); break;
        case BILLIARD_9:
            PhysicalObject::setTexture(prefix + "ball9.png", rect); break;
        case BILLIARD_10:
            PhysicalObject::setTexture(prefix + "ball10.png", rect); break;
        case BILLIARD_11:
            PhysicalObject::setTexture(prefix + "ball11.png", rect); break;
        case BILLIARD_12:
            PhysicalObject::setTexture(prefix + "ball12.png", rect); break;
        case BILLIARD_13:
            PhysicalObject::setTexture(prefix + "ball13.png", rect); break;
        case BILLIARD_14:
            PhysicalObject::setTexture(prefix + "ball14.png", rect); break;
        case BILLIARD_15:
            PhysicalObject::setTexture(prefix + "ball15.png", rect); break;
        default:
            success = false;
            break;
    }
    return success;
}