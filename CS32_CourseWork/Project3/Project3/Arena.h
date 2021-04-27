//
//  Arena.h
//  Project3
//
//  Created by Oscar Cheng on 2020/5/16.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#ifndef Arena_h
#define Arena_h

#include "Monsters.h"
#include "Player.h"
#include "Weapon.h"
#include "Scroll.h"
#include <vector>

const int MAXROWS = 18;
const int MAXCOLS = 70;
const int MAXMON = 10;

class Arena{
public:
    Arena(int g);
    ~Arena();
    
    Player* getPlayer();
    bool getWin();
    
    void action(char &d);
    void pickUp();
    
    bool playerMove(char &d, int &r, int &c);
    void playerHits(const int &r,const  int &c);
    
    void monsterMove();
    void monsterHits();
    
    std::string hit(Actor& a1, Actor& a2);
    void monsterDead(Actor& m);
    void loot(Actor& m);
    
    void display();
    
private:
    void createLevel();
    void nextLevel();
    void addPlayer();
    void addMonsters();
    void addObjects();
    
    char m_grid[MAXROWS][MAXCOLS];
    Player* m_player;
    std::vector<Monster*> m_monsters;
    std::vector<GameObject*> m_objects;
    std::vector<Coord> m_objectLocation;
    std::vector<std::string> m_messages;
    Coord m_stairs;
    int m_currentLevel;
    int m_goblinSmell;
    bool m_win;
};

#endif /* Arena_h */
