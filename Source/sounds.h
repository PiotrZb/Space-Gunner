#ifndef SOUNDS_H
#define SOUNDS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Sounds
{
private:

    sf::Music main_theme_;

    sf::SoundBuffer jump_;
    sf::Sound jump_sound_;

    sf::SoundBuffer run_;
    sf::Sound run_sound_;

    sf::SoundBuffer shot_;
    sf::Sound shot_sound_;

    sf::SoundBuffer jetpack_;
    sf::Sound jetpack_sound_;

    sf::SoundBuffer hurt_;
    sf::Sound hurt_sound_;

    sf::SoundBuffer airlock_;
    sf::Sound airlock_sound_;

    sf::SoundBuffer gameover_;
    sf::Sound gameover_sound_;

    bool rs_is_active_;
    bool js_is_active_;
    bool as_is_active_;

public:

    Sounds();

    void play_main_theme(bool loop = true, float volume = 50);
    void play_jump_sound(float volume = 50);
    void play_shot_sound(float volume = 50);
    void play_run_sound(float volume = 50);
    void stop_run_sound();
    void stop_main_theme();
    void play_jetpack_sound(float volume = 50);
    void stop_jetpack_sound();
    void play_hurt_sound(float volume = 50);
    void play_airlock_sound(float volume = 50);
    void stop_airlock_sound();
    void play_gameover_sound(float volume = 50);

    void sound_load(sf::SoundBuffer &sound, std::string file_name);
};

#endif // SOUNDS_H
