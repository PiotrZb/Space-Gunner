#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "menu.h"

class GameOver : public Menu
{
public:

    GameOver(const int &width, const int &height);
};

#endif // GAMEOVER_H
