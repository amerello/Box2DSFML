#ifndef BOX2DSFML_BRICK_H
#define BOX2DSFML_BRICK_H
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "PhysicalObject.h"

class Brick  : public PhysicalObject {
public:
    enum Type {
        DICE_1 = 0,
        DICE_2,
        DICE_3,
        DICE_4,
        DICE_5,
        DICE_6,
        GRASS,
        BRICK
    };

    Brick(float x, float y, float width, float height, float angle, Type type, b2World& world, bool rigid=false);
    bool setTexture(Type type);
};


#endif //BOX2DSFML_BRICK_H
