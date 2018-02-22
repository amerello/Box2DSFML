#include <iostream>
#include "Brick.h"
#include "constants.h"

Brick::Brick(float x, float y, float width, float height, float angle, Type type, b2World &world, bool rigid)
        : PhysicalObject(x, y, angle, world, rigid) {
    b2PolygonShape polygon = b2PolygonShape();             // Now we create a polygon
    polygon.SetAsBox(width / 2.f, height / 2.f);           // and use the shortcut to form the polygon into a box

    createFixture(polygon, rigid);

    // Now we deal with the graphical representation
    shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height));
    resetShape(x, y, angle, sf::Vector2f(width / 2.f, height / 2.f));
    setTexture(type);
}

bool Brick::setTexture(Type type) {
    bool success = true;
    switch(type) {
        case DICE_1:
            PhysicalObject::setTexture("textures/dice_cubes_sd_bit.png", sf::IntRect( 34,  8, 50, 50)); break;
        case DICE_2:
            PhysicalObject::setTexture("textures/dice_cubes_sd_bit.png", sf::IntRect( 104,  8, 50, 50)); break;
        case DICE_3:
            PhysicalObject::setTexture("textures/dice_cubes_sd_bit.png", sf::IntRect( 174,  8, 50, 50)); break;
        case DICE_4:
            PhysicalObject::setTexture("textures/dice_cubes_sd_bit.png", sf::IntRect( 34,  71, 50, 50)); break;
        case DICE_5:
            PhysicalObject::setTexture("textures/dice_cubes_sd_bit.png", sf::IntRect( 104,  71, 50, 50)); break;
        case DICE_6:
            PhysicalObject::setTexture("textures/dice_cubes_sd_bit.png", sf::IntRect( 174,  71, 50, 50)); break;
        case GRASS:
            PhysicalObject::setTexture("textures/platformer/Tiles/grassMid.png", sf::IntRect(0, 0, windowWidth, 70));
            break;
        case BRICK:
            PhysicalObject::setTexture("textures/trak_tile_red.jpg", sf::IntRect(25, 40, 200, 40)); break;
        default:
            success = false;
            break;
    }
    return success;
}