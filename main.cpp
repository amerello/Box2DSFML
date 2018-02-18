#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

constexpr int windowWidth{800}, windowHeight{600};

inline float32 degToRad(float deg) { return deg * (float32) M_PI / 180.f; }
inline float32 radToDeg(float rad) { return rad * 180.f / (float32) M_PI; }

struct Brick {
    sf::RectangleShape shape;  // SFML graphical object representation
    b2Body* body;              // Box2D physical object representation
    b2PolygonShape polygon;
    Brick(float x, float y, float width, float height, float angle, sf::Color color, b2World& world, bool rigid=false) {
        b2BodyDef bodyDef;                                     // We define a body
        bodyDef.type = rigid ? b2_staticBody : b2_dynamicBody;
        bodyDef.position.Set(x, y);                            // with an initial position
        bodyDef.angle = -degToRad(angle);                      // and angle.
        body = world.CreateBody(&bodyDef);                     // The body definition is passed to the world object
        polygon = b2PolygonShape();                            // We create a polygon
        polygon.SetAsBox(width/2.f, height/2.f);               // and use the shortcut to form the polygon into a box

        if(rigid) {
            body->CreateFixture(&polygon, 0.f);                // We don't need to edit the default fixture.
        } else {
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &polygon;
            fixtureDef.density = 1.0f;
            fixtureDef.friction = 0.3f;
            fixtureDef.restitution = 1.0f;
            body->CreateFixture(&fixtureDef);
        }
        shape.setPosition(windowWidth/2 + x, windowHeight/2 - y);  // We draw everything displaced so (0,0) is in the
        shape.setSize({width, height});                            // center.
        shape.setFillColor(color);
        shape.setOrigin(width/2.f, height/2.f);
        shape.setRotation(angle);
    }
    void update() {
        b2Vec2 position = body->GetPosition();
        shape.setPosition(windowWidth/2 + position.x, windowHeight/2 - position.y);
        shape.setRotation(-radToDeg(body->GetAngle()));
    }
    bool isVisible() {
        sf::Vector2f position = shape.getPosition();
        return (position.x >= 0 && position.x < windowWidth && position.y >=0 && position.y < windowHeight);
    }
    void rotate(float rotDeg) {
        body->SetTransform(body->GetPosition(), body->GetAngle() + degToRad(rotDeg));
        shape.setRotation(-radToDeg(body->GetAngle()));
    }
    void translate(float x, float y) {
        b2Vec2 position = body->GetPosition();
        position.x += x;
        position.y += y;
        body->SetTransform(position, body->GetAngle());
        shape.setPosition(windowWidth/2 + position.x, windowHeight/2 - position.y);
    }
};

int main(int argc, char** argv) {
    B2_NOT_USED(argc);
    B2_NOT_USED(argv);

    b2Vec2 gravity(0.0f, -10.f);  // First, we define the gravity vector.
    b2World world(gravity);       // Now we create the world object. Note that we are creating it in the stack, so it
                                  // must remain in scope.

    // We create a static brick and add it to the world.
    Brick groundBrick(0.f, -10.f, 100.f, 20.f, 30.f, sf::Color::Red, world, true);

    std::vector<Brick> bricks;
    bricks.emplace_back(0.f, 50.f, 2.f, 2.f, 0.f, sf::Color::Yellow, world);

    // Simulation parameters
    float32 timeStep = 1.0f / 60.0f;
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
                    bricks.emplace_back(xPos, yPos, 2.f, 2.f, 0.f, sf::Color::Yellow, world);
                }
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            groundBrick.rotate(1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
            groundBrick.rotate(-1.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            groundBrick.translate(0, 1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            groundBrick.translate(-1.f, 0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            groundBrick.translate(0, -1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            groundBrick.translate(1.f, 0);
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