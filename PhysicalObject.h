#ifndef BOX2DSFML_PHYSICALOBJECT_H
#define BOX2DSFML_PHYSICALOBJECT_H
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class PhysicalObject {
public:
    PhysicalObject() = default;
    void update();
    bool isVisible();
    void rotate(float deg);
    void translate(float x, float y);
    const sf::Shape& getShape() { return *shape; }
    b2Body* getBody() { return body; }

protected:
    std::shared_ptr<sf::Shape> shape;   // SFML graphical object representation
    b2Body* body = nullptr;             // Box2D physical object representation
};


#endif //BOX2DSFML_PHYSICALOBJECT_H
