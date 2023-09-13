#include "bullet.h"

Bullet::Bullet(std::string gun_direction, float x, float y, std::vector<sf::Texture> &textures){

    if(gun_direction == "right"){
        velocity_x_ = 500;
        setTexture(textures[0]);
    }
    else{
        velocity_x_ = -500;
        setTexture(textures[1]);
    }

    setPosition(x,y);
    setScale(2,2);
}

void Bullet::move_bullet(sf::Time &elapsed){

    move(velocity_x_ * elapsed.asSeconds(), 0);
}
