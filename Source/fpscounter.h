#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Fpscounter : public sf::Text
{
private:

    sf::Clock fps_clock_;
    sf::Font font;

    int counter_ = 0;

public:

    Fpscounter();

    void update(sf::Vector2f view);
};

#endif // FPSCOUNTER_H
