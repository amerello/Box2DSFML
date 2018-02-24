#ifndef BOX2DSFML_PLAYER_H
#define BOX2DSFML_PLAYER_H


#include <Box2D/Dynamics/b2World.h>
#include "Brick.h"

class Player : public PhysicalObject {
public:
    enum Stance {
        STANDING = 0,
        RUNNING_0,
        RUNNING_1,
        RUNNING_2,
        RUNNING_3,
        RUNNING_4,
        RUNNING_5,
        RUNNING_6,
        RUNNING_7
    };
    enum Direction {
        LEFT = 0,
        RIGHT,
        UP,
        DOWN
    };
    Player(float x, float y, b2World &world);
    bool setStance(Stance stance);
    void setNextRunningSprite();
    void move(Direction direction);

private:
    const int playerWidth = 46;
    const int playerHeight = 50;
    const std::string spritemap = "textures/assets/player/player-spritemap-v9.png";
    unsigned int runningSprite = 0;
};


#endif //BOX2DSFML_PLAYER_H
