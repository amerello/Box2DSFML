#include <iostream>
#include "Brick.h"

Brick::Brick(float x, float y, float width, float height, float angle, const sf::Color& color, b2World &world, bool rigid)
        : PhysicalObject(x, y, angle, world, rigid) {
    b2PolygonShape polygon = b2PolygonShape();             // Now we create a polygon
    polygon.SetAsBox(width / 2.f, height / 2.f);           // and use the shortcut to form the polygon into a box

    createFixture(polygon, rigid);

    // Now we deal with the graphical representation
    shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height));
    resetShape(x, y, angle, sf::Vector2f(width / 2.f, height / 2.f), color);
}