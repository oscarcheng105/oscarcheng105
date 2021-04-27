//
//  Monster.hpp
//  Project3
//
//  Created by Oscar Cheng on 2020/5/17.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#ifndef Monster_h
#define Monster_h

#include "Actor.h"
#include "utilities.h"

class Monster: public Actor
{
public:
    Monster(Weapon& w, int r, int c , int h, int a, int s, int d, std::string n): Actor(w, r, c, h, a, s, d, n){}
    virtual void pathFind(char maze[][70], int sr, int sc, int er, int ec, int maxSteps);
};

//--------------------------------------------------------------------------------------------------------------------
class Goblin: public Monster
{
public:
    Goblin(int r, int c):Monster(*new shortSword(), r, c, randInt(15,20), 1, 3, 1, "the Goblin"){}
    bool pathFind(char maze[][70], char temp[][70],int sr, int sc, int er, int ec, int steps,int maxSteps);
};

class Snakewomen: public Monster
{
public:
    Snakewomen(int r, int c):Monster(*new magicFangs(), r, c, randInt(3,6), 3, 2, 2, "the Snakewomen"){}
};

class Bogeymen: public Monster
{
public:
    Bogeymen(int r, int c):Monster(*new shortSword(), r, c, randInt(5,10), 2, randInt(2,3), randInt(2,3), "the Bogeymen"){}
};

class Dragon: public Monster
{
public:
    Dragon(int r, int c):Monster(*new longSword(), r, c, randInt(20,25), 4, 4, 4,"the Dragon"){}
};

#endif /* Monster_h */
