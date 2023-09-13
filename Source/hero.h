#ifndef HERO_H
#define HERO_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>

class Hero : public sf::Sprite
{
protected:

    std::vector<sf::Texture> standing_;
    std::vector<sf::Texture> running_right_;
    std::vector<sf::Texture> running_left_;
    std::vector<sf::Texture> jumping_;

    sf::Clock clock;
    sf::Clock shot_clock_;

    std::string last_direction_;

    int velocity_x_;
    int velocity_y_;
    int velocity_yy_;
    int velocity_xx_;

    int current_image_right_;
    int current_image_left_;

    int hp_;
    float energy_;
    bool has_jetpack_;

    std::pair<float,float> barrel_cords_;

public:

    Hero(float x, float y, std::map<std::string,std::string> &init_data);

    void animate();
    void run_animation();
    void jump_animation();
    void reset_run_animation();

    void load_texture(sf::Texture &texture, std::string file_name, sf::IntRect rect = sf::IntRect(9,4,37,46));

    void move_hero(sf::Time &elapsed);
    void gravity();
    void collisions(std::vector<sf::FloatRect> objects_bounds, sf::Time &elapsed);

    void set_velocity_x(int velx);
    void set_velocity_y(int vely);
    int get_velocity_x();
    int get_velocity_y();
    int get_velocity_xx();
    int get_velocity_yy();
    void set_velocity_xx(int velxx);
    void set_velocity_yy(int velyy);
    bool jump_is_active();
    bool has_jetpack();
    void set_jetpack(bool hpk);

    void set_hp(int hp);
    int get_hp();
    void set_energy(float energy);
    float get_energy();

    void change_last_direction(std::string direction);

    std::string last_direction();

    std::pair<float,float> barrel_cords();

    bool gravity_is_active_;
};

#endif // HERO_H
