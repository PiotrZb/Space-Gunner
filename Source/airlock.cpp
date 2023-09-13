#include "airlock.h"

AirLock::AirLock(){

    if(!texture_.loadFromFile("Textures/Sceneelements/Gate.png")){
        std::cout<<"ERROR::SCENE1::TEXTURE FAILED TO LOAD -> Textures/Sceneelements/Gate.png"<<std::endl;
    }

    setTexture(texture_);
    texture_.setRepeated(true);
    current_frame_ = 13;
}

void AirLock::animate(std::string status){

    if(clock_.getElapsedTime().asSeconds() >= 0.07){

        if(current_frame_ > 0 && status == "open"){

            current_frame_--;
        }
        else{

            if(current_frame_ < 13 && status == "close"){

                current_frame_++;
            }
        }

        clock_.restart();
    }

    setTextureRect(sf::IntRect(0,0,15, current_frame_ * 10));
}
