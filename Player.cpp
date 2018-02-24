#include "Player.h"

Player::Player(float x, float y, b2World &world) : PhysicalObject(x, y, 0.f, world, false) {
    b2PolygonShape polygon = b2PolygonShape();
    polygon.SetAsBox(playerWidth / 2.f, playerHeight / 2.f);

//    createFixture(polygon, false);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygon;         // Shape will be cloned, so it's safe to be on the stack
    fixtureDef.density = 1.0f;         // The fixture adds material properties to the Box2D body
    fixtureDef.friction = 0.3f;        // such as shape, density and friction.
    fixtureDef.restitution = 0.2f;
    body->CreateFixture(&fixtureDef);  // We assign this fixture to the Box2D body.

    // Now we deal with the graphical representation
    shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(playerWidth, playerHeight));
    resetShape(x, y, 0.f, sf::Vector2f(playerWidth / 2.f, playerHeight / 2.f));
    setStance(STANDING);
}

bool Player::setStance(Player::Stance stance) {
    bool success = true;
    int spriteX = 0, spriteY=0;
    switch(stance) {
        case  STANDING: spriteX = 46*0; spriteY = 50*0; break;
        case RUNNING_0: spriteX = 46*0; spriteY = 50*3; break;
        case RUNNING_1: spriteX = 46*1; spriteY = 50*3; break;
        case RUNNING_2: spriteX = 46*2; spriteY = 50*3; break;
        case RUNNING_3: spriteX = 46*3; spriteY = 50*3; break;
        case RUNNING_4: spriteX = 46*4; spriteY = 50*3; break;
        case RUNNING_5: spriteX = 46*5; spriteY = 50*3; break;
        case RUNNING_6: spriteX = 46*6; spriteY = 50*3; break;
        case RUNNING_7: spriteX = 46*7; spriteY = 50*3; break;
        default: success = false; break;
    }
    PhysicalObject::setTexture(spritemap, sf::IntRect(spriteX, spriteY, playerWidth, playerHeight));
    return success;
}

void Player::move(Player::Direction direction) {
    switch(direction) {
        case LEFT:
            translate(-10.f, 0);
            shape->setScale({ -1, 1 });
            setNextRunningSprite(); break;
        case RIGHT:
            translate(10.f, 0);
            shape->setScale({ 1, 1 });
            setNextRunningSprite(); break;
        case UP: break;
        case DOWN: break;
    }
}

void Player::setNextRunningSprite() {
    PhysicalObject::setTexture(spritemap, sf::IntRect(46*(runningSprite++), 150, playerWidth, playerHeight));
}
