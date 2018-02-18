#include "Brick.h"
#include "constants.h"
#include "helper.h"

Brick::Brick(float x, float y, float width, float height, float angle, sf::Color color, b2World &world, bool rigid) {
    b2BodyDef bodyDef;                                     // We define a Box2D body
    bodyDef.type = rigid ? b2_staticBody : b2_dynamicBody;
    bodyDef.position.Set(x, y);                            // with an initial position and angle
    bodyDef.angle = -degToRad(angle);                      // Box2D body has no material representation.
    body = world.CreateBody(&bodyDef);                     // The body definition is passed to the world object
    b2PolygonShape polygon = b2PolygonShape();             // Now we create a polygon
    polygon.SetAsBox(width / 2.f, height / 2.f);           // and use the shortcut to form the polygon into a box

    if (rigid) {
        body->CreateFixture(&polygon, 0.f);                // We don't need to edit the default fixture.
    } else {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &polygon;                       // Shape will be cloned, so it's safe to be on the stack
        fixtureDef.density = 1.0f;                         // The fixture adds material properties to the Box2D body
        fixtureDef.friction = 0.3f;                        // such as shape, density and friction.
        fixtureDef.restitution = 1.0f;
        body->CreateFixture(&fixtureDef);                  // We assign this fixture to the Box2D body.
    }

    // Now we deal with the graphical representation
    shape.setPosition(windowWidth / 2 + x, windowHeight / 2 - y);  // We draw everything displaced so (0,0) is in the
    shape.setSize({width, height});                                // center.
    shape.setFillColor(color);
    shape.setOrigin(width / 2.f, height / 2.f);
    shape.setRotation(angle);
}

// Updates graphical object position from Box2D
void Brick::update() {
    b2Vec2 position = body->GetPosition();
    shape.setPosition(windowWidth / 2 + position.x, windowHeight / 2 - position.y);
    shape.setRotation(-radToDeg(body->GetAngle()));
}

bool Brick::isVisible() {
    sf::Vector2f position = shape.getPosition();
    return (position.x >= 0 && position.x < windowWidth && position.y >= 0 && position.y < windowHeight);
}

void Brick::rotate(float rotDeg) {
    body->SetTransform(body->GetPosition(), body->GetAngle() + degToRad(rotDeg));
    shape.setRotation(-radToDeg(body->GetAngle()));
}

void Brick::translate(float x, float y) {
    b2Vec2 position = body->GetPosition();
    position.x += x;
    position.y += y;
    body->SetTransform(position, body->GetAngle());
    shape.setPosition(windowWidth / 2 + position.x, windowHeight / 2 - position.y);
}