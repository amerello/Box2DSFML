#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

constexpr int windowWidth{800}, windowHeight{600};
constexpr float blockWidth{5.f}, blockHeight{5.f};

struct Brick {
    sf::RectangleShape shape;
    b2Body* body;
    Brick(float mX, float mY) {
        shape.setPosition(mX, mY);
        shape.setSize({blockWidth, blockHeight});
        shape.setFillColor(sf::Color::Yellow);
        shape.setOrigin(blockWidth/2.f, blockHeight/2.f);
    }
    Brick(float mX, float mY, float width, float height, sf::Color color) {
        shape.setPosition(mX, mY);
        shape.setSize({width, height});
        shape.setFillColor(color);
        shape.setOrigin(width/2.f, height/2.f);
    }
    Brick(float mX, float mY, float width, float height, sf::Color color, b2World& world) : Brick(mX, mY, width, height, color) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(mX, mY);
        body = world.CreateBody(&bodyDef);
        b2PolygonShape* dynamicBox = new b2PolygonShape;  // Needs to be destructed
        dynamicBox->SetAsBox(width/2.f, height/2.f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 1.0f;
        body->CreateFixture(&fixtureDef);
    }
    void update() {
        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();
        shape.setPosition(windowWidth/2 + position.x, windowHeight/2 - position.y);
        shape.setRotation(-angle*180.f/3.1415f);
    }
};

int main(int argc, char** argv) {
    B2_NOT_USED(argc);
    B2_NOT_USED(argv);

    b2Vec2 gravity(0.0f, -10.f);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    groundBodyDef.angle = -3.1415f/6.f;
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    Brick groundBrick{windowWidth/2, windowHeight/2 + 10, 100, 20, sf::Color::Green};
    groundBrick.shape.setRotation(30);

    std::vector<Brick> bricks;
    bricks.emplace_back(0.f, 50.f, 2, 2, sf::Color::Yellow, world);


    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    sf::RenderWindow window{{windowWidth, windowHeight}, "Box2D / SFML"};
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    float xPos = (float) event.mouseButton.x - windowWidth/2;
                    float yPos = (float) -event.mouseButton.y + windowHeight/2;
                    bricks.emplace_back(xPos, yPos, 2, 2, sf::Color::Yellow, world);
                }
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        world.Step(timeStep, velocityIterations, positionIterations);

        window.clear(sf::Color::Black);

        for(auto& brick: bricks) {
            brick.update();
            window.draw(brick.shape);
        }

        window.draw(groundBrick.shape);
        window.display();
    }
    return 0;
}