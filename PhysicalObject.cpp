#include "PhysicalObject.h"
#include "constants.h"
#include "helper.h"

PhysicalObject::PhysicalObject(float x, float y, float angle, b2World& world, bool rigid) {
    b2BodyDef bodyDef;                                     // We define a Box2D body
    bodyDef.type = rigid ? b2_staticBody : b2_dynamicBody;
    bodyDef.position.Set(x, y);                            // with an initial position and angle
    bodyDef.angle = -degToRad(angle);                      // Box2D body has no material representation.
    body = world.CreateBody(&bodyDef);                     // The body definition is passed to the world object
}

void PhysicalObject::resetShape(float x, float y, float angle, const sf::Vector2f& origin, const sf::Color& color) {
    shape->setPosition(windowWidth / 2 + x, windowHeight / 2 - y);  // We draw everything displaced so (0,0) is in the
    shape->setFillColor(color);                                     // center.
    shape->setOrigin(origin);
    shape->setRotation(angle);
}

void PhysicalObject::createFixture(const b2Shape& shape, bool rigid) {
    if (rigid) {
        body->CreateFixture(&shape, 0.f);  // We don't need to edit the default fixture.
    } else {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;         // Shape will be cloned, so it's safe to be on the stack
        fixtureDef.density = 1.0f;         // The fixture adds material properties to the Box2D body
        fixtureDef.friction = 0.3f;        // such as shape, density and friction.
        fixtureDef.restitution = 1.0f;
        body->CreateFixture(&fixtureDef);  // We assign this fixture to the Box2D body.
    }
}

// Updates graphical object position from Box2D
void PhysicalObject::update() {
    b2Vec2 position = body->GetPosition();
    shape->setPosition(windowWidth / 2 + position.x, windowHeight / 2 - position.y);
    shape->setRotation(-radToDeg(body->GetAngle()));
}

bool PhysicalObject::isVisible() {
    sf::Vector2f position = shape->getPosition();
    return (position.x >= 0 && position.x < windowWidth && position.y >= 0 && position.y < windowHeight);
}

void PhysicalObject::rotate(float rotDeg) {
    body->SetTransform(body->GetPosition(), body->GetAngle() + degToRad(rotDeg));
    shape->setRotation(-radToDeg(body->GetAngle()));
}

void PhysicalObject::translate(float x, float y) {
    b2Vec2 position = body->GetPosition();
    position.x += x;
    position.y += y;
    body->SetTransform(position, body->GetAngle());
    shape->setPosition(windowWidth / 2 + position.x, windowHeight / 2 - position.y);
}