#include "turret.h"

Turret::Turret(){

    if(!texture_.loadFromFile("Textures/Enemy/Turret.png")){

        std::cout<<"ERROR::TURRET::TEXTURE FAILED TO LOAD -> Textures/Enemy/Turret.png"<<std::endl;
    }

    sf::Texture texture;

    if(!texture.loadFromFile("Textures/Bullet/bulletright.png")){

        std::cout<<"ERROR::TURRET::TEXTURE FAILED TO LOAD -> Textures/Bullet/bulletright.png"<<std::endl;
    }

    bullet_textures_.emplace_back(texture);

    if(!texture.loadFromFile("Textures/Bullet/bulletleft.png")){

        std::cout<<"ERROR::TURRET::TEXTURE FAILED TO LOAD -> Textures/Bullet/bulletleft.png"<<std::endl;
    }

    bullet_textures_.emplace_back(texture);

    setTexture(texture_);
    rotate(180);
    setScale(2,2);
    hp_ = 100;
    is_alive_ = true;
}

void Turret::set_hp(int hp){

    hp_ = hp;
}

int Turret::get_hp(){

    return hp_;
}

bool Turret::shot(std::vector<std::unique_ptr<Bullet>> &bullets, sf::FloatRect hero_rec){

    if(getGlobalBounds().top + 24 >= hero_rec.top && getGlobalBounds().top - 24 <= hero_rec.top + hero_rec.height
                                                  && clock_.getElapsedTime().asSeconds() >= 1
                                                  && (getGlobalBounds().left - (hero_rec.left + hero_rec.width)) <= 600
                                                  && getGlobalBounds().left >= hero_rec.left){

        bullets.emplace_back(std::make_unique<Bullet>("left", getGlobalBounds().left - 25, getGlobalBounds().top + 24, bullet_textures_));
        clock_.restart();

        return true;
    }
    else{

        return false;
    }
}
