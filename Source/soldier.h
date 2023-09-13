#ifndef SOLDIER_H
#define SOLDIER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <map>

#include "hero.h"
#include "bullet.h"

class Soldier : public Hero
{
private:

    sf::FloatRect movement_bounds_;
    std::vector<sf::Texture> bullet_textures_;

public:

    Soldier(float x, float y, sf::FloatRect rec, std::map<std::string,std::string> &init_data):Hero(x,y, init_data){

        setColor(sf::Color::Red);
        movement_bounds_ = rec;
        velocity_x_ = 300;

        sf::Texture texture;

        if(!texture.loadFromFile("Textures/Bullet/bulletright.png")){

            std::cout<<"ERROR::TURRET::TEXTURE FAILED TO LOAD -> Textures/Bullet/bulletright.png"<<std::endl;
        }

        bullet_textures_.emplace_back(texture);

        if(!texture.loadFromFile("Textures/Bullet/bulletleft.png")){

            std::cout<<"ERROR::TURRET::TEXTURE FAILED TO LOAD -> Textures/Bullet/bulletleft.png"<<std::endl;
        }

        bullet_textures_.emplace_back(texture);
        hp_ = 100;
    }

    void set_movement_bounds(sf::FloatRect movement_bounds);
    void move_soldier(sf::Time &elapsed);
    bool shot(std::vector<std::unique_ptr<Bullet>> &bullets, sf::FloatRect hero_rec);
};

#endif // SOLDIER_H
