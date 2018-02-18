#include "PhysicalObject.h"
#include "constants.h"
#include "helper.h"

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