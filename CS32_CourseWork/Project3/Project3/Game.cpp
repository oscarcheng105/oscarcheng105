// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>

using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
: m_level(new Arena(goblinSmellDistance)) // Create the initial dungeon level
{}

Game::~Game()
{
    delete m_level;
}

void Game::play()
{
    clearScreen();
    m_level->display();
    char input = '.';
    do{
        input = getCharacter(); //Check input, all available input should be under the following
        clearScreen();
        if(input == 'h' || input == 'j' || input == 'k' || input == 'l' || input == 'g' ||
           input == 'r' || input == 'w' || input == 'c' || input == '>')
        {
            m_level->action(input);
        }
        else if(input == 'i')
        {
            m_level->getPlayer()->inventory();
        }
        else
        {
            m_level->display();
        }
    }while(m_level->getPlayer()->living() && !m_level->getWin());
    cout << "Press q to exit game." << endl;
    while (getCharacter() != 'q')
        ;
}
// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
