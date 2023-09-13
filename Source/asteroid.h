#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Asteroid : public sf::Sprite
{
private:

    sf::Texture texture_;

    int velocity_x_;
    int velocity_y_;
    int angular_velocity_;

public:

    Asteroid();

    void move_asteroid(sf::Time &elapsed);
};

#endif // ASTEROID_H
