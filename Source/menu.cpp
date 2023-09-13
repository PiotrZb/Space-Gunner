#include "menu.h"

Menu::Menu(const int &width, const int &height){

    if(!font_.loadFromFile("Fonts/Dustismo_Roman_Bold.ttf")){

        std::cout<<"ERROR::MENU::FONT FAILED TO LOAD -> Fonts/Dustismo_Roman_Bold.ttf"<<std::endl;
    }

    menu_.setFont(font_);
    menu_.setString("MENU");
    menu_.setFillColor(sf::Color::White);
    menu_.setStyle(sf::Text::Style::Bold);
    menu_.setCharacterSize(70);
    menu_.setOrigin(sf::Vector2f(menu_.getGlobalBounds().width/2, menu_.getGlobalBounds().height/2));
    menu_.setPosition(sf::Vector2f(width/2, 100));

    options_text_.setFont(font_);
    options_text_.setString("Options");
    options_text_.setFillColor(sf::Color::Black);
    options_text_.setStyle(sf::Text::Style::Bold);
    options_text_.setCharacterSize(50);
    options_text_.setOrigin(sf::Vector2f(options_text_.getGlobalBounds().width/2, options_text_.getGlobalBounds().height/2));
    options_text_.setPosition(sf::Vector2f(width/2, height/2));
    options_rec_.setSize(sf::Vector2f(options_text_.getGlobalBounds().width + 100, options_text_.getGlobalBounds().height + 30));
    options_rec_.setOrigin(sf::Vector2f(options_rec_.getSize().x/2, options_rec_.getSize().y/2 - 7));
    options_rec_.setPosition(sf::Vector2f(width/2, height/2));

    play_text_.setFont(font_);
    play_text_.setString("Play");
    play_text_.setFillColor(sf::Color::Black);
    play_text_.setStyle(sf::Text::Style::Bold);
    play_text_.setCharacterSize(50);
    play_text_.setOrigin(sf::Vector2f(play_text_.getGlobalBounds().width/2, play_text_.getGlobalBounds().height/2));
    play_text_.setPosition(sf::Vector2f(width/2, height/2 - 50 - options_rec_.getSize().y));
    play_rec_.setSize(sf::Vector2f(options_text_.getGlobalBounds().width + 100, options_text_.getGlobalBounds().height + 30));
    play_rec_.setOrigin(sf::Vector2f(play_rec_.getSize().x/2, play_rec_.getSize().y/2 - 7));
    play_rec_.setPosition(sf::Vector2f(width/2, height/2 - 50 - options_rec_.getSize().y));

    exit_text_.setFont(font_);
    exit_text_.setString("Exit");
    exit_text_.setFillColor(sf::Color::Black);
    exit_text_.setStyle(sf::Text::Style::Bold);
    exit_text_.setCharacterSize(50);
    exit_text_.setOrigin(sf::Vector2f(exit_text_.getGlobalBounds().width/2, exit_text_.getGlobalBounds().height/2));
    exit_text_.setPosition(sf::Vector2f(width/2, height/2 + 50 + options_rec_.getSize().y));
    exit_rec_.setSize(sf::Vector2f(options_text_.getGlobalBounds().width + 100, options_text_.getGlobalBounds().height + 30));
    exit_rec_.setOrigin(sf::Vector2f(exit_rec_.getSize().x/2, exit_rec_.getSize().y/2 - 7));
    exit_rec_.setPosition(sf::Vector2f(width/2, height/2 + 50 + options_rec_.getSize().y));
}

void Menu::draw(sf::RenderWindow &window){

    if(is_active_ == true){

        window.draw(menu_);

        window.draw(options_rec_);
        window.draw(options_text_);

        window.draw(play_rec_);
        window.draw(play_text_);

        window.draw(exit_rec_);
        window.draw(exit_text_);
    }
}

void Menu::contains_mouse(sf::Vector2f &mouse_coordinates){

    sf::FloatRect play_bounds_(play_rec_.getGlobalBounds().left, play_rec_.getGlobalBounds().top,
                               play_rec_.getGlobalBounds().width, play_rec_.getGlobalBounds().height);

    sf::FloatRect options_bounds_(options_rec_.getGlobalBounds().left, options_rec_.getGlobalBounds().top,
                                  options_rec_.getGlobalBounds().width, options_rec_.getGlobalBounds().height);

    sf::FloatRect exit_bounds_(exit_rec_.getGlobalBounds().left,exit_rec_.getGlobalBounds().top,
                               exit_rec_.getGlobalBounds().width, exit_rec_.getGlobalBounds().height);

    if(play_bounds_.contains(mouse_coordinates)){

        play_text_.setFillColor(sf::Color::Red);
    }
    else{

        play_text_.setFillColor(sf::Color::Black);
    }

    if(options_bounds_.contains(mouse_coordinates)){

        options_text_.setFillColor(sf::Color::Red);
    }
    else{

        options_text_.setFillColor(sf::Color::Black);
    }

    if(exit_bounds_.contains(mouse_coordinates)){

        exit_text_.setFillColor(sf::Color::Red);
    }
    else{

        exit_text_.setFillColor(sf::Color::Black);
    }
}

void Menu::onclick_event_(sf::Vector2f &mouse_coordinates, sf::RenderWindow &window){

    sf::FloatRect play_bounds_(play_rec_.getGlobalBounds().left, play_rec_.getGlobalBounds().top,
                               play_rec_.getGlobalBounds().width, play_rec_.getGlobalBounds().height);

    sf::FloatRect options_bounds_(options_rec_.getGlobalBounds().left, options_rec_.getGlobalBounds().top,
                                  options_rec_.getGlobalBounds().width, options_rec_.getGlobalBounds().height);

    sf::FloatRect exit_bounds_(exit_rec_.getGlobalBounds().left,exit_rec_.getGlobalBounds().top,
                               exit_rec_.getGlobalBounds().width, exit_rec_.getGlobalBounds().height);

    if(play_bounds_.contains(mouse_coordinates)){

        is_active_ = false;
    }

    if(options_bounds_.contains(mouse_coordinates)){

    }

    if(exit_bounds_.contains(mouse_coordinates)){

        std::cout<<"Program was closed properly"<<std::endl;
        window.close();
    }
}
