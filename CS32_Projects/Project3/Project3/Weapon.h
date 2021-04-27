//
//  Weapon.h
//  Project3
//
//  Created by Oscar Cheng on 2020/5/17.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#ifndef Weapon_h
#define Weapon_h

#include "GameObject.h"
#include "utilities.h"
#include <iostream>
#include <string>

//Abstract Class
class Weapon: public GameObject
{
public:
    Weapon(std::string name, int dex, int dmg): GameObject("Weapon",name), m_dexBonus(dex), m_damage(dmg){}
    int dexterity(){return m_dexBonus;}
    int damage(){return m_damage;}
private:
    int m_dexBonus;
    int m_damage;
};

//------------------------------------------------------------------

class mace: public Weapon
{
public:
    mace():Weapon("mace",0,2){}
    virtual std::string action()
        {return " swings mace at ";}
};

class shortSword: public Weapon
{
public:
    shortSword():Weapon("short sword",0,2){}
    virtual std::string action()
        {return " slashes short sword at ";}
};

class longSword: public Weapon
{
public:
    longSword():Weapon("long sword",2,4){}
    virtual std::string action()
        {return " swings long sword at ";}
};

class magicAxe: public Weapon
{
public:
    magicAxe():Weapon("magic axe",5,5){}
    virtual std::string action()
        {return " chops magic axe at ";}
};

class magicFangs: public Weapon
{
public:
    magicFangs():Weapon("magic fangs of sleep",3,2){}
    virtual std::string action()
        {return " strikes magic fangs at ";}
    bool sleep(){return randInt(5) == 0;} //does sleep
};

#endif /* GameObject_h */
