#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <memory>
#include <fstream>
#include <map>
#include <string>

#include "menu.h"
#include "fpscounter.h"
#include "hero.h"
#include "sounds.h"
#include "bullet.h"
#include "scene1.h"
#include "gameover.h"
#include "hud.h"

void load_texture(sf::Texture &texture, std::string file_path);
void load_bullet_textures(std::vector<sf::Texture> &bullet_textures);

int main(){

//--------------------------------------------------------------------------------------------------> initialization

    std::map<std::string,std::string> initial_data;
    std::string line1, line2;
    std::fstream file;
    file.open("Data/initialdata.txt", std::ios::in);
    if(file.is_open()){

        while(getline(file, line1, ' ')){

            getline(file, line2);
            initial_data[line1] = line2;
        }
    }
    else{

        std::cout<<"ERROR::MAIN::FAILED TO OPEN FILE -> initialdata.txt"<<std::endl;
    }
    file.close();

    //window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Space Gunner", sf::Style::Titlebar | sf::Style::Close);
    sf::Image icon;
    if(!icon.loadFromFile( "Textures/icon.png" )){
        std::cout<<"ERROR::MAIN::ICON FAILED TO LOAD -> icon.png"<<std::endl;
    }
    window.setIcon( icon.getSize().x, icon.getSize().y, icon.getPixelsPtr() );
    window.setFramerateLimit(60);

    //camera
    sf::View view(sf::Vector2f(0,0),sf::Vector2f(1200,800));
    sf::View view_menu(sf::Vector2f(600,400),sf::Vector2f(1200,800));

    //background
    sf::Texture background_texture;
    load_texture(background_texture, "Textures/Background/background.png");
    sf::Sprite background;
    background.setTexture(background_texture);
    background.setTextureRect(sf::IntRect(0,0,1200, 800));

    GameOver game_over(1200, 800);

    //sounds
    Sounds sounds;
    if(initial_data["music"] == "on"){sounds.play_main_theme(true, 10);}

    //fps counter
    Fpscounter fpscounter;

    srand(time(NULL));

New_game:
    {
        //menu
        Menu menu(1200, 800);


        //hero
        Hero hero(0,700, initial_data);

        //hud
        HUD hud;

        //bullets
        std::vector<sf::Texture> bullet_textures;
        load_bullet_textures(bullet_textures);
        std::vector<std::unique_ptr<Bullet>> bullets;

        //Scene 1
        Scene1 scene1(initial_data);

        sf::Clock clock;
        sf::Time elapsed;

        while (window.isOpen() && hero.get_hp() > 0){

//--------------------------------------------------------------------------------------------------> update functions

            elapsed = clock.restart();
            sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            menu.contains_mouse(mouse_position);

            //hero and scene updates
            if(!menu.is_active_){

                scene1.animate_elements(hero.getGlobalBounds(), elapsed);
                scene1.update(hero, elapsed, bullets);

                hero.gravity();
                hero.collisions(scene1.objects_bounds(), elapsed);
                hero.move_hero(elapsed);
                hero.animate();
            }

            if(hero.getPosition().y > 800){hero.set_hp(0);}

            //camera update
            view.setCenter(hero.getGlobalBounds().left + hero.getGlobalBounds().width, 400);


            //moving and removing bullets
            std::vector<sf::FloatRect> objects_bounds = scene1.objects_bounds();
            for(size_t i = 0; i < bullets.size(); i++){

                if(!menu.is_active_){bullets[i]->move_bullet(elapsed);}
            }

            for(size_t i = 0; i < bullets.size();){

                bool collision = false;

                if(((bullets[i]->getGlobalBounds().left + bullets[i]->getGlobalBounds().width) < (view.getCenter().x - view.getSize().x))
                        || (bullets[i]->getGlobalBounds().left > (view.getCenter().x + view.getSize().x))){

                    bullets.erase(bullets.begin()+i);
                    break;
                }
                else{

                    for(auto itr = objects_bounds.begin(); itr != objects_bounds.end(); ++itr){

                        if(bullets[i]->getGlobalBounds().intersects(*itr)){

                            bullets.erase(bullets.begin()+i);
                            collision = true;
                            break;
                        }
                    }
                }
                if(!collision){i++;}
            }

            hud.set_energy(hero.get_energy());

//--------------------------------------------------------------------------------------------------> movement

            if(!menu.is_active_){

                //move right
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){

                    hero.set_velocity_x(300);
                    hero.change_last_direction("right");

                    if(hero.jump_is_active()){

                        sounds.play_run_sound();
                    }
                }

                //move left
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){

                    hero.set_velocity_x(-300);
                    hero.change_last_direction("left");

                    if(hero.jump_is_active()){

                        sounds.play_run_sound();
                    }
                }

                //stop
                if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))){

                    hero.set_velocity_x(0);
                    sounds.stop_run_sound();
                }

                //jump
                if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && hero.jump_is_active())
                  || (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && hero.has_jetpack())){

                    if(hero.has_jetpack() && (hero.get_energy() > 0)){

                        hero.set_velocity_y(-300);
                        sounds.play_jetpack_sound(20);
                        hero.set_energy(hero.get_energy()- (10 * elapsed.asSeconds()));
                    }
                    else{

                        hero.set_velocity_y(-600);
                        sounds.play_jump_sound();
                        hero.set_jetpack(false);
                    }
                    sounds.stop_run_sound();
                }
                else{

                    sounds.stop_jetpack_sound();
                }
            }

//--------------------------------------------------------------------------------------------------> events

            sf::Event event;
            while (window.pollEvent(event)) {

                //closing the window
                if (event.type == sf::Event::Closed){

                    std::cout<<"Program was closed properly"<<std::endl;

                    window.close();
                }
                else{

                    //menu onclick events
                    if(menu.is_active_){

                        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){

                            menu.onclick_event_(mouse_position, window);
                        }
                    }
                    else{

                        //opening the menu
                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){

                            menu.is_active_ = true;
                        }
                        else{

                            //shooting
                            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left){

                                sounds.play_shot_sound(10);
                                bullets.emplace_back(std::make_unique<Bullet>(hero.last_direction(), hero.barrel_cords().first, hero.barrel_cords().second, bullet_textures));
                            }
                        }
                    }
                }
            }

//--------------------------------------------------------------------------------------------------> other update functions

            //camera update
            if(menu.is_active_){

                window.setView(view_menu);
                background.setPosition(0,0);
            }
            else{

                if(hero.getGlobalBounds().left + hero.getGlobalBounds().width > 600){

                    window.setView(view);
                    background.setPosition(view.getCenter().x - 600, view.getCenter().y - 400);
                }
            }

            //fps counter update
            fpscounter.update(window.getView().getCenter());

            //hud update
            hud.update(window.getView().getCenter(), hero.get_hp());

//--------------------------------------------------------------------------------------------------> Display

            window.clear(sf::Color::Black);
            window.draw(background);

            if(!menu.is_active_){

                window.draw(scene1);
                scene1.draw_animated_elements(window, hero.has_jetpack());
                window.draw(hero);

                for(size_t i = 0; i < bullets.size(); i++){

                    window.draw(*bullets[i]);
                }

                hud.draw_hud(window);
            }

            menu.draw(window);
            window.draw(fpscounter);

            window.display();
        }
    }

//--------------------------------------------------------------------------------------------------> Game Over

    sounds.play_gameover_sound();

    if(window.isOpen()){game_over.is_active_ = true;}

    while(game_over.is_active_ && window.isOpen()){

        sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        game_over.contains_mouse(mouse_position);

        sf::Event event;
        while (window.pollEvent(event)) {

            //closing the window
            if (event.type == sf::Event::Closed){

                std::cout<<"Program was closed properly"<<std::endl;

                window.close();
            }
            else{

                //game over onclick events
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){

                    game_over.onclick_event_(mouse_position, window);
                }
            }
        }

        window.setView(view_menu);
        background.setPosition(0,0);

        window.clear(sf::Color::Black);

        window.draw(background);
        game_over.draw(window);
        window.draw(fpscounter);

        window.display();
    }

    if(window.isOpen()){
        goto New_game;
    }

    return 0;
}

//--------------------------------------------------------------------------------------------------> functions

void load_texture(sf::Texture &texture, std::string file_path){

    if(!texture.loadFromFile(file_path)){

        std::cout<<"ERROR::MAIN::TEXTURE FAILED TO LOAD -> "<<file_path<<std::endl;
    }
}

void load_bullet_textures(std::vector<sf::Texture> &bullet_textures){

    sf::Texture texture;

    load_texture(texture, "Textures/Bullet/bulletright.png");
    bullet_textures.emplace_back(texture);

    load_texture(texture, "Textures/Bullet/bulletleft.png");
    bullet_textures.emplace_back(texture);
}
