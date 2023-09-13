#ifndef AIRLOCK_H
#define AIRLOCK_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class AirLock : public sf::Sprite
{
private:

    sf::Texture texture_;
    sf::Clock clock_;

    int current_frame_;

public:

    AirLock();

    void animate(std::string status);
};

#endif // AIRLOCK_H
