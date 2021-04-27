// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.
#include "Arena.h"

const int MAXLEVELS = 5;

class Game
{
public:
    Game(int goblinSmellDistance);
    ~Game();
    void play();
    void goblinDetects();
    Arena generateArena();
private:
    Arena* m_level;
};

#endif // GAME_INCLUDED
