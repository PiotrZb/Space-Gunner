#include "gameover.h"

GameOver::GameOver(const int &width, const int &height){

    if(!font_.loadFromFile("Fonts/Dustismo_Roman_Bold.ttf")){

        std::cout<<"ERROR::MENU::FONT FAILED TO LOAD -> Fonts/Dustismo_Roman_Bold.ttf"<<std::endl;
    }

    menu_.setFont(font_);
    menu_.setString("Game Over");
    menu_.setFillColor(sf::Color::White);
    menu_.setStyle(sf::Text::Style::Bold);
    menu_.setCharacterSize(70);
    menu_.setOrigin(sf::Vector2f(menu_.getGlobalBounds().width/2, menu_.getGlobalBounds().height/2));
    menu_.setPosition(sf::Vector2f(width/2, 100));

    play_text_.setFont(font_);
    play_text_.setString("New Game");
    play_text_.setFillColor(sf::Color::Black);
    play_text_.setStyle(sf::Text::Style::Bold);
    play_text_.setCharacterSize(50);
    play_text_.setOrigin(sf::Vector2f(play_text_.getGlobalBounds().width/2, play_text_.getGlobalBounds().height/2));
    play_text_.setPosition(sf::Vector2f(width/2, height/2 - 100 - options_rec_.getSize().y));
    play_rec_.setSize(sf::Vector2f(options_text_.getGlobalBounds().width + 300, options_text_.getGlobalBounds().height + 100));
    play_rec_.setOrigin(sf::Vector2f(play_rec_.getSize().x/2, play_rec_.getSize().y/2 - 7));
    play_rec_.setPosition(sf::Vector2f(width/2, height/2 - 100 - options_rec_.getSize().y));

    exit_text_.setFont(font_);
    exit_text_.setString("Exit");
    exit_text_.setFillColor(sf::Color::Black);
    exit_text_.setStyle(sf::Text::Style::Bold);
    exit_text_.setCharacterSize(50);
    exit_text_.setOrigin(sf::Vector2f(exit_text_.getGlobalBounds().width/2, exit_text_.getGlobalBounds().height/2));
    exit_text_.setPosition(sf::Vector2f(width/2, height/2 + 100 + options_rec_.getSize().y));
    exit_rec_.setSize(sf::Vector2f(options_text_.getGlobalBounds().width + 300, options_text_.getGlobalBounds().height + 100));
    exit_rec_.setOrigin(sf::Vector2f(exit_rec_.getSize().x/2, exit_rec_.getSize().y/2 - 7));
    exit_rec_.setPosition(sf::Vector2f(width/2, height/2 + 100 + options_rec_.getSize().y));

    is_active_ = false;
}
