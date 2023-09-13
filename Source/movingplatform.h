#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "hero.h"

class MovingPlatform : public sf::Sprite
{
private:

    sf::Texture texture_;
    sf::FloatRect movement_bounds_;

    int velocity_x_;
    int velocity_y_;

public:

    MovingPlatform();

    void set_movement_bounds(sf::FloatRect movement_bounds);
    int get_velocity_y();
    int get_velocity_x();
    void set_velocity_y(int velocity_y);
    void set_velocity_x(int velocity_x);
    void move_platform(sf::Time &elapsed);
    void collisions(Hero &hero, sf::Time &elapsed);
};

#endif // MOVINGPLATFORM_H
