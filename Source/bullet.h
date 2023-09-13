#ifndef BULLET_H
#define BULLET_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Bullet : public sf::Sprite
{
private:

    int velocity_x_;

public:

    Bullet(std::string gun_direction, float x, float y, std::vector<sf::Texture> &textures);

    void move_bullet(sf::Time &elapsed);
};

#endif // BULLET_H
