#include "soldier.h"

void Soldier::move_soldier(sf::Time &elapsed){

    if(movement_bounds_.left > getGlobalBounds().left){

        velocity_x_ = abs(velocity_x_);
        last_direction_ = "right";
    }
    else {
        if(movement_bounds_.left + movement_bounds_.width < getGlobalBounds().left + getGlobalBounds().width){

            velocity_x_ = abs(velocity_x_) * (-1);
            last_direction_ = "left";
        }
    }

    if(movement_bounds_.top > getGlobalBounds().top){

        velocity_y_ = abs(velocity_y_);
    }
    else {

        if(movement_bounds_.top + movement_bounds_.height < getGlobalBounds().top + getGlobalBounds().height){

            velocity_y_ = abs(velocity_y_) * (-1);
        }
    }

    move(elapsed.asSeconds() * velocity_x_, elapsed.asSeconds() * velocity_y_);

    if(last_direction_ == "right"){

        barrel_cords_.first = getPosition().x + 90;
    }
    else{
        barrel_cords_.first = getPosition().x - 20;
    }

    barrel_cords_.second = getPosition().y + 32;
}

bool Soldier::shot(std::vector<std::unique_ptr<Bullet> > &bullets, sf::FloatRect hero_rec){

    float x = barrel_cords_.first;
    float y = barrel_cords_.second;
    sf::FloatRect rec(0,0,0,0);

    if(last_direction_ == "left"){

        rec = sf::FloatRect(x - 400, y, 400, 52);
    }
    else if(last_direction_ == "right"){

        rec = sf::FloatRect(x, y, 400, 52);
    }

    if(rec.intersects(hero_rec) && hp_ > 0 && shot_clock_.getElapsedTime().asSeconds() >= 0.4){

        bullets.emplace_back(std::make_unique<Bullet>(last_direction_, barrel_cords_.first, barrel_cords_.second, bullet_textures_));
        shot_clock_.restart();

        return true;
    }
    else{

        return false;
    }
}
