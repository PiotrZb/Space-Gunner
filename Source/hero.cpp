#include "hero.h"

Hero::Hero(float x, float y, std::map<std::string, std::string> &init_data){

    sf::Texture texture;

    load_texture(texture, "standright.png");
    standing_.emplace_back(texture);

    load_texture(texture, "standleft.png", sf::IntRect(4,4,37,46));
    standing_.emplace_back(texture);

    load_texture(texture, "jumpright.png");
    jumping_.emplace_back(texture);

    load_texture(texture, "jumpleft.png", sf::IntRect(4,4,37,46));
    jumping_.emplace_back(texture);

    for(int i = 1; i < 9; i++){

        load_texture(texture, "runright" + std::to_string(i) + ".png");
        running_right_.emplace_back(texture);

        load_texture(texture, "runleft" + std::to_string(i) + ".png", sf::IntRect(4,4,37,46));
        running_left_.emplace_back(texture);
    }

    setTexture(standing_[0]);
    setScale(sf::Vector2f(2.5,2.5));
    setPosition(x, y - getGlobalBounds().height);

    velocity_x_ = 0;
    velocity_y_ = 0;
    current_image_right_ = 0;
    current_image_left_ = 0;
    last_direction_ = "right";
    gravity_is_active_ = true;
    hp_ = atoi(init_data["hp"].c_str());
    energy_ = atof(init_data["energy"].c_str());
    if(init_data["has_jetpack"] == "true"){has_jetpack_ = true;}
    else{has_jetpack_ = false;}
}

void Hero::move_hero(sf::Time &elapsed){

    move((velocity_x_ * elapsed.asSeconds()) + (velocity_xx_ * elapsed.asSeconds()),
         (velocity_y_ * elapsed.asSeconds()) + (velocity_yy_ * elapsed.asSeconds()));

    if(last_direction_ == "right"){

        barrel_cords_.first = getPosition().x + 90;
    }
    else{
        barrel_cords_.first = getPosition().x - 20;
    }

    barrel_cords_.second = getPosition().y + 32;
}

void Hero::animate(){

    if(velocity_y_ == 0 && velocity_x_ == 0){

        if(last_direction_ == "right"){

            setTexture(standing_[0]);
        }
        else{

            setTexture(standing_[1]);
        }

        reset_run_animation();
    }
    else{

        if(velocity_y_ != 0 ){

            jump_animation();
            reset_run_animation();
        }
        else{

            run_animation();
        }
    }
}

bool Hero::jump_is_active(){

    if(velocity_y_ == 0){return true;}
    else {return false;}
}

void Hero::set_velocity_x(int velx){

    velocity_x_ = velx;
}

void Hero::set_velocity_y(int vely){

    velocity_y_ = vely;
}

void Hero::set_velocity_xx(int velxx){

    velocity_xx_ = velxx;
}

void Hero::set_velocity_yy(int velyy){

    velocity_yy_ = velyy;
}

void Hero::gravity(){

    if(gravity_is_active_){

        velocity_y_ +=21;
    }
}

void Hero::load_texture(sf::Texture &texture, std::string file_name, sf::IntRect rect){

    if(!texture.loadFromFile("Textures/Hero/" + file_name, rect)){

        std::cout<<"ERROR::HERO::TEXTURE FAILED TO LOAD -> Textures/Hero/" + file_name<<std::endl;
    }
}

void Hero::change_last_direction(std::string direction){

    last_direction_ = direction;
}

void Hero::jump_animation(){

    if(last_direction_ == "right"){

        setTexture(jumping_[0]);
    }
    else{

        setTexture(jumping_[1]);
    }
}

void Hero::run_animation(){

    if(last_direction_ == "right"){

        current_image_left_ = 0;

        if(clock.getElapsedTime().asSeconds() >= 0.07){

            current_image_right_++;
            clock.restart();
        }

        if(current_image_right_ == 8){

            current_image_right_ = 0;
        }

        setTexture(running_right_[current_image_right_]);
    }
    else{

        current_image_right_ = 0;

        if(clock.getElapsedTime().asSeconds() >= 0.07){

            current_image_left_++;
            clock.restart();
        }

        if(current_image_left_ == 8){

            current_image_left_ = 0;
        }

        setTexture(running_left_[current_image_left_]);
    }
}

std::string Hero::last_direction(){

    return last_direction_;
}

std::pair<float,float> Hero::barrel_cords(){

    return barrel_cords_;
}

void Hero::collisions(std::vector<sf::FloatRect> objects_bounds, sf::Time &elapsed){

    sf::FloatRect X = getGlobalBounds();
    sf::FloatRect Y = getGlobalBounds();

    X.left += velocity_x_ * elapsed.asSeconds();
    Y.top += velocity_y_ * elapsed.asSeconds();

    for(size_t i = 0; i < objects_bounds.size(); i++){

        if(X.intersects(objects_bounds[i])){

            if(velocity_x_ > 0 || velocity_xx_ > 0){

                setPosition(objects_bounds[i].left - getGlobalBounds().width, getGlobalBounds().top);
            }
            else{

                setPosition(objects_bounds[i].left + objects_bounds[i].width, getGlobalBounds().top);
            }

            velocity_x_ = 0;
            velocity_xx_ = 0;
            velocity_yy_ = 0;
        }

        else if(Y.intersects(objects_bounds[i])){

            if(velocity_y_ < 0){

                velocity_y_ = 1;
                setPosition(getGlobalBounds().left, objects_bounds[i].top + objects_bounds[i].height);
            }
            else{

                velocity_y_ = 0;
                setPosition(getGlobalBounds().left, objects_bounds[i].top - getGlobalBounds().height);
            }

            velocity_xx_ = 0;
            velocity_yy_ = 0;
        }
    }
}

void Hero::reset_run_animation(){

    current_image_left_ = 0;
    current_image_right_ = 0;
}

int Hero::get_velocity_x(){

    return velocity_x_;
}

int Hero::get_velocity_y(){

    return velocity_y_;
}

int Hero::get_velocity_xx(){

    return velocity_xx_;
}

int Hero::get_velocity_yy(){

    return velocity_yy_;
}

int Hero::get_hp(){

    return hp_;
}

void Hero::set_hp(int hp){

    hp_ = hp;
}

bool Hero::has_jetpack(){

    return has_jetpack_;
}

void Hero::set_jetpack(bool hpk){

    has_jetpack_ = hpk;
}

float Hero::get_energy(){

    return energy_;
}

void Hero::set_energy(float energy){

    energy_ = energy;
}
