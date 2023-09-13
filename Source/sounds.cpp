#include "sounds.h"

Sounds::Sounds(){

    if(!main_theme_.openFromFile("Sounds/maintheme.wav")){

        std::cout<<"ERROR::SOUNDS::SOUND FAILED TO LOAD -> Sounds/maintheme.wav"<<std::endl;
    }

    sound_load(jump_, "jump.wav");
    sound_load(run_, "longrun.wav");
    sound_load(shot_, "shot1.wav");
    sound_load(jetpack_, "jetpack.wav");
    sound_load(hurt_, "hurt.wav");
    sound_load(airlock_, "airlock.wav");
    sound_load(gameover_, "gameover.wav");

    rs_is_active_ = false;
    js_is_active_ = false;
    as_is_active_ = false;
}

void Sounds::play_main_theme(bool loop, float volume){

    main_theme_.setLoop(loop);
    main_theme_.setVolume(volume);
    main_theme_.play();
}

void Sounds::sound_load(sf::SoundBuffer &sound, std::string file_name){

    if(!sound.loadFromFile("Sounds/" + file_name)){

        std::cout<<"ERROR::SOUNDS::SOUND FAILED TO LOAD -> Sounds/" + file_name<<std::endl;
    }
}

void Sounds::play_jump_sound(float volume){

    jump_sound_.setBuffer(jump_);
    jump_sound_.setVolume(volume);
    jump_sound_.play();
    jump_sound_.pause();
    jump_sound_.setPlayingOffset(sf::milliseconds(250));
    jump_sound_.play();
}

void Sounds::play_run_sound(float volume){

    if(!rs_is_active_){

        run_sound_.setBuffer(run_);
        run_sound_.setVolume(volume);
        run_sound_.setLoop(true);
        run_sound_.play();
    }

    rs_is_active_ = true;
}

void Sounds::stop_run_sound(){

    run_sound_.stop();
    rs_is_active_ = false;
}

void Sounds::play_shot_sound(float volume){

    shot_sound_.setBuffer(shot_);
    shot_sound_.setVolume(volume);
    shot_sound_.play();
}

void Sounds::stop_main_theme(){

    main_theme_.stop();
}

void Sounds::play_jetpack_sound(float volume){

    if(!js_is_active_){

        jetpack_sound_.setBuffer(jetpack_);
        jetpack_sound_.setVolume(volume);
        jetpack_sound_.play();
        js_is_active_ = true;
    }
}

void Sounds::stop_jetpack_sound(){

    jetpack_sound_.stop();
    js_is_active_ = false;
}

void Sounds::play_hurt_sound(float volume){

    hurt_sound_.setBuffer(hurt_);
    hurt_sound_.setVolume(volume);
    hurt_sound_.play();
}

void Sounds::play_airlock_sound(float volume){

    if(!as_is_active_){

        airlock_sound_.setBuffer(airlock_);
        airlock_sound_.setVolume(volume);
        airlock_sound_.play();
        as_is_active_ = true;
    }
}

void Sounds::stop_airlock_sound(){

    airlock_sound_.stop();
    as_is_active_ = false;
}

void Sounds::play_gameover_sound(float volume){

    gameover_sound_.setBuffer(gameover_);
    gameover_sound_.setVolume(volume);
    gameover_sound_.play();
}
