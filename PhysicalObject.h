#ifndef BOX2DSFML_PHYSICALOBJECT_H
#define BOX2DSFML_PHYSICALOBJECT_H
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class PhysicalObject {
public:
    PhysicalObject() = default;
    PhysicalObject(float x, float y, float angle, b2World& world, bool rigid);
    void resetShape(float x, float y, float angle, const sf::Vector2f& origin, const sf::Color& color);
    void update();
    bool isVisible();
    void rotate(float deg);
    void translate(float x, float y);
    void setTexture(const std::string& filename, const sf::IntRect& rect);
    const sf::Shape& getShape() { return *shape; }
    b2Body* getBody() { return body; }

protected:
    void createFixture(const b2Shape& shape, bool rigid);

    std::shared_ptr<sf::Shape> shape;   // SFML graphical object representation
    b2Body* body = nullptr;             // Box2D physical object representation
    sf::Texture texture;
};


#endif //BOX2DSFML_PHYSICALOBJECT_H
