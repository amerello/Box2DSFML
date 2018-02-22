#ifndef BOX2DSFML_BALL_H
#define BOX2DSFML_BALL_H
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "PhysicalObject.h"

class Ball : public PhysicalObject {
public:
    enum Type {
        BILLIARD_0 = 0,
        BILLIARD_1,
        BILLIARD_2,
        BILLIARD_3,
        BILLIARD_4,
        BILLIARD_5,
        BILLIARD_6,
        BILLIARD_7,
        BILLIARD_8,
        BILLIARD_9,
        BILLIARD_10,
        BILLIARD_11,
        BILLIARD_12,
        BILLIARD_13,
        BILLIARD_14,
        BILLIARD_15
    };

    Ball(float x, float y, float radius, Type type, b2World& world, bool rigid=false);

    bool setTexture(Type type);
};


#endif //BOX2DSFML_BALL_H
