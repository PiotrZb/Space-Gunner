#include "fpscounter.h"

Fpscounter::Fpscounter(){

    if(!font.loadFromFile("Fonts/Dustismo_Roman_Bold.ttf")){
        std::cout<<"ERROR::FPSCOUNTER::FONT FAILED TO LOAD -> Fonts/Dustismo_Roman_Bold.ttf"<<std::endl;
    }

    setFont(font);
    setCharacterSize(15);
    setFillColor(sf::Color::White);
    setPosition(10,10);
    setStyle(sf::Text::Style::Bold);
}

void Fpscounter::update(sf::Vector2f view){

    if(fps_clock_.getElapsedTime().asMilliseconds() >= 999){
        setString("FPS " + std::to_string(counter_));
        counter_ = 0;
        fps_clock_.restart();
    }

    counter_++;

    setPosition(view.x + 500, view.y - 390);
}
