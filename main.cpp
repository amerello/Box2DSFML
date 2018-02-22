#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <random>
#include "constants.h"
#include "Brick.h"
#include "Ball.h"

typedef std::vector<std::unique_ptr<PhysicalObject>> physical_vector;

int main(int argc, char** argv) {
    B2_NOT_USED(argc);
    B2_NOT_USED(argv);

    //This is for the dice and balls
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dice(0, 5);
    std::uniform_int_distribution<> rd_ball(0, 15);

    b2Vec2 gravity(0.0f, -10.f);  // First, we define the gravity vector.
    b2World world(gravity);       // Now we create the world object. Note that we are creating it in the stack, so it
                                  // must remain in scope.

    // We create a static brick and add it to the world.
    Brick platform(0.f, -10.f, 100.f, 20.f, 30.f, Brick::BRICK, world, true);

    Brick ground(0.f, -300.f, windowWidth, 70.f, 0.f, Brick::GRASS, world, true);

    physical_vector bricks;
    bricks.emplace_back(std::make_unique<Ball>(40.f, 50.f, 10.f,(Ball::Type)rd_ball(gen), world));

    // Simulation parameters
    float32 timeStep = 1.0f / 15.0f;
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
                float xPos = (float) event.mouseButton.x - windowWidth/2;
                float yPos = (float) -event.mouseButton.y + windowHeight/2;
                if(event.mouseButton.button == sf::Mouse::Left) {
                    bricks.emplace_back(std::make_unique<Ball>(xPos, yPos, 10.f,(Ball::Type)rd_ball(gen), world));
                    auto *body = bricks.back().get()->getBody();
                    body->ApplyLinearImpulseToCenter(b2Vec2(0.f,10000.f), true);
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    bricks.emplace_back(std::make_unique<Brick>(xPos, yPos, 10.f, 10.f, 0.f, (Brick::Type) dice(gen),
                                                                world));
                }
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            platform.rotate(1.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            platform.translate(0, 1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
            platform.rotate(-1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            platform.translate(-1.f, 0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            platform.translate(0, -1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            platform.translate(1.f, 0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        world.Step(timeStep, velocityIterations, positionIterations);

        window.clear(sf::Color(30, 144, 255));

        auto brick_it = std::begin(bricks);
        while (brick_it != std::end(bricks)) {
            brick_it->get()->update();
            if(brick_it->get()->isVisible()) {
                window.draw(brick_it->get()->getShape());
                ++brick_it;
            }
            else {
                world.DestroyBody(brick_it->get()->getBody());
                bricks.erase(brick_it);
            }
        }

        window.draw(platform.getShape());
        window.draw(ground.getShape());
        window.display();
    }
    return 0;
}