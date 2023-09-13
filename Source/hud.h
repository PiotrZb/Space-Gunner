#ifndef HUD_H
#define HUD_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>

class HUD
{
private:

    sf::Sprite hp_bar_;
    sf::Texture hp_bar_texture_;
    sf::Sprite energy_bar_;
    sf::Texture energy_bar_texture_;
    sf::Texture black_heart_texture_;
    sf::RectangleShape black_rec_;
    std::vector<std::unique_ptr<sf::Sprite>> black_hearts_;

    int hp_;
    float energy_;

public:

    HUD();

    void set_hp(int &val);
    int get_hp();
    void set_energy(float val);
    float get_energy();

    void draw_hud(sf::RenderWindow &window);
    void update(sf::Vector2f view, int hp);
};

#endif // HUD_H
