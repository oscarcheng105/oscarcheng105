//
//  Player.hpp
//  Project3
//
//  Created by Oscar Cheng on 2020/5/17.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#ifndef Player_h
#define Player_h


#include "Actor.h"
#include "GameObject.h"
#include "Scroll.h"
#include "Weapon.h"
#include <vector>

const int MAXINVENTORY = 25;

class Player: public Actor
{
public:
    Player(int r, int c);
    virtual ~Player();
    void cheat();
    bool getItems(GameObject &g);
    void inventory();
    void useScroll(char maze[][70], std::vector<std::string>& message);
    void equipWeapon(std::vector<std::string>& message);
private:
    std::vector<GameObject*> m_bag;
};
#endif /* Player_h */
