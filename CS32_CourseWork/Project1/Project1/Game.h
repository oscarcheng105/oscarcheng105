//
//  Game.h
//  Project1
//
//  Created by Oscar Cheng on 2020/4/5.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include "Arena.h"

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nVampires);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    std::string takePlayerTurn();
};

#endif /* Game_h */
