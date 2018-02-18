#include <iostream>
#include <memory>
#include "Ball.h"
#include "constants.h"

Ball::Ball(float x, float y, float radius, sf::Color color, b2World& world, bool rigid) {
    b2BodyDef bodyDef;                                     // We define a Box2D body
    bodyDef.type = rigid ? b2_staticBody : b2_dynamicBody;
    bodyDef.position.Set(x, y);                            // with an initial position and angle
    body = world.CreateBody(&bodyDef);                     // The body definition is passed to the world object
    b2CircleShape circle = b2CircleShape();
    circle.m_p.Set(0,0);
    circle.m_radius = radius;

    if (rigid) {
        body->CreateFixture(&circle, 0.f);                // We don't need to edit the default fixture.
    } else {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circle;                       // Shape will be cloned, so it's safe to be on the stack
        fixtureDef.density = 1.0f;                         // The fixture adds material properties to the Box2D body
        fixtureDef.friction = 0.3f;                        // such as shape, density and friction.
        fixtureDef.restitution = 1.0f;
        body->CreateFixture(&fixtureDef);                  // We assign this fixture to the Box2D body.
    }

    // Now we deal with the graphical representation
    shape = std::make_shared<sf::CircleShape>(radius) ;
    shape->setPosition(windowWidth / 2 + x, windowHeight / 2 - y);  // We draw everything displaced so (0,0) is in the
    shape->setFillColor(color);
    shape->setOrigin(radius, radius);
}
