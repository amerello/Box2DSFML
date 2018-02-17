#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

constexpr int windowWidth{800}, windowHeight{600};

struct Brick {
    sf::RectangleShape shape;
    b2Body* body;
    b2PolygonShape polygon;
    Brick(float mX, float mY, float width, float height, float angle, sf::Color color, b2World& world, bool rigid=false) {
        b2BodyDef bodyDef;                                     // We define a body
        bodyDef.type = rigid ? b2_staticBody : b2_dynamicBody;
        bodyDef.position.Set(mX, mY);                          // with an initial position
        bodyDef.angle = -angle * (float)M_PI / 180.f;          // and angle.
        body = world.CreateBody(&bodyDef);                     // The body definition is passed to the world object
        polygon = b2PolygonShape();             // We create a polygon
        polygon.SetAsBox(width/2.f, height/2.f);               // and use the shortcut to form the polygon into a box

        if(rigid) {
            body->CreateFixture(&polygon, 0.f);                 // Since we don't need to edit the default fixture we
        } else {                                                // use the shortcut.
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &polygon;
            fixtureDef.density = 1.0f;
            fixtureDef.friction = 0.3f;
            fixtureDef.restitution = 1.0f;
            body->CreateFixture(&fixtureDef);
        }

        if(rigid)
            shape.setPosition(windowWidth/2 + mX, windowHeight/2 - mY);
        else
            shape.setPosition(mX, mY);
        shape.setSize({width, height});
        shape.setFillColor(color);
        shape.setOrigin(width/2.f, height/2.f);
        shape.setRotation(angle);
    }
    void update() {
        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();
        shape.setPosition(windowWidth/2 + position.x, windowHeight/2 - position.y);
        shape.setRotation(-angle*180.f/(float)M_PI);
    }
    bool isVisible() {
        sf::Vector2f position = shape.getPosition();
        return (position.x >= 0 && position.x < windowWidth && position.y >=0 && position.y < windowHeight);
    }
    ~Brick() {
        b2Fixture* fix = body->GetFixtureList();
        while(fix) {
            body->DestroyFixture(fix);
            fix = fix->GetNext();
        }
    }
};

int main(int argc, char** argv) {
    B2_NOT_USED(argc);
    B2_NOT_USED(argv);

    b2Vec2 gravity(0.0f, -10.f);  // First, we define the gravity vector.
    b2World world(gravity);       // Now we create the world object. Note that we are creating it in the stack, so it
                                  // must remain in scope.

    Brick groundBrick(0.f, -10.f, 100.f, 20.f, 30.f, sf::Color::Green, world, true);

    std::vector<Brick> bricks;
    bricks.emplace_back(0.f, 50.f, 2, 2, 0.f, sf::Color::Yellow, world);

    float32 timeStep = 1.0f / 30.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 1;

    sf::RenderWindow window{{windowWidth, windowHeight}, "Box2D / SFML"};
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    while(window.isOpen()) {
        sf::Event event{};
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    float xPos = (float) event.mouseButton.x - windowWidth/2;
                    float yPos = (float) -event.mouseButton.y + windowHeight/2;
                    bricks.emplace_back(xPos, yPos, 2, 2, 0.f, sf::Color::Yellow, world);
                }
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        world.Step(timeStep, velocityIterations, positionIterations);

        window.clear(sf::Color::Black);

        auto brick_it = std::begin(bricks);
        while (brick_it != std::end(bricks)) {
            brick_it->update();
            if(brick_it->isVisible()) {
                window.draw(brick_it->shape);
                ++brick_it;
            }
            else {
                bricks.erase(brick_it);
            }
        }

        window.draw(groundBrick.shape);
        window.display();
    }
    return 0;
}