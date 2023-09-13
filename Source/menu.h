#ifndef MENU_H
#define MENU_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu
{
protected:

    sf::Font font_;

    sf::Text menu_;

    sf::RectangleShape play_rec_; 
    sf::Text play_text_;

    sf::RectangleShape options_rec_;
    sf::Text options_text_;

    sf::RectangleShape exit_rec_;
    sf::Text exit_text_;

public:

    Menu() = default;
    Menu(const int &width, const int &height);

    void draw(sf::RenderWindow &window);

    void contains_mouse(sf::Vector2f &mouse_coordinates);
    void onclick_event_(sf::Vector2f &mouse_coordinates, sf::RenderWindow &window);

    bool is_active_ = true;
};

#endif // MENU_H
