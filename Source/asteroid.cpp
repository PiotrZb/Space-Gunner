#include "asteroid.h"

Asteroid::Asteroid(){

    if(!texture_.loadFromFile("Textures/Sceneelements/Asteroid.png")){

        std::cout<<"ERROR::ASTEROID::TEXTURE FAILED TO LOAD -> Textures/Sceneelements/Asteroid.png"<<std::endl;
    }

    setTexture(texture_);
    int x = rand()%2850 + 6450;
    velocity_y_ = rand()%100 + 50;
    velocity_x_ = rand()%50;
    angular_velocity_ = 10;
    setPosition(x,0);
    setScale(0.5,0.5);
}


void Asteroid::move_asteroid(sf::Time &elapsed){

    rotate(elapsed.asSeconds()*angular_velocity_);
    move(elapsed.asSeconds()*velocity_x_, elapsed.asSeconds()*velocity_y_);

    if(getPosition().y > 800){

        int x = rand()%2850 + 6450;
        setPosition(x, 0 - getGlobalBounds().height);
    }
}
