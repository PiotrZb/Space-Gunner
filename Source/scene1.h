#ifndef SCENE1_H
#define SCENE1_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <string>
#include <map>

#include "airlock.h"
#include "movingplatform.h"
#include "hero.h"
#include "turret.h"
#include "sounds.h"
#include "soldier.h"
#include "asteroid.h"

class Scene1 : public sf::Sprite
{
private:

    //stationary elements
    std::vector<sf::FloatRect> objects_bounds_;
    sf::Texture scene1_texture_;
    sf::Texture jetpack_texture_;
    sf::Sprite jetpack_;
    sf::Sprite jetpack2_;

    //animated elements
    AirLock air_lock1_;
    AirLock air_lock2_;
    AirLock air_lock3_;
    AirLock air_lock4_;
    MovingPlatform platform1_;
    MovingPlatform platform2_;
    MovingPlatform platform3_;
    std::vector<std::unique_ptr<Asteroid>> asteroids_;

    //enemy bullets
    std::vector<std::unique_ptr<Bullet>> enemy_bullets_;

    Sounds sounds_;
    sf::Text credits_;
    sf::Font font_;
    std::string text_;

    std::map<std::string,std::string> initial_data_;

    //enemies
    Turret turret1_;
    Soldier soldier1_ = Soldier(1150,331,sf::FloatRect(1150,193,400,140), initial_data_);
    Soldier soldier2_ = Soldier(3430,711,sf::FloatRect(3430,571,400,140), initial_data_);

public:

    Scene1(std::map<std::string,std::string> &init_data);

    std::vector<sf::FloatRect> objects_bounds();

    void draw_animated_elements(sf::RenderWindow &window, bool has_jetpack_);
    void animate_elements(sf::FloatRect hero_bounds, sf::Time &elapsed);
    void update(Hero &hero, sf::Time &elapsed, std::vector<std::unique_ptr<Bullet>> &hero_bullets);
};

#endif // SCENE1_H
