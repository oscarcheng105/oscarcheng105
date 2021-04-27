//
//  Scroll.h
//  Project3
//
//  Created by Oscar Cheng on 2020/5/17.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#ifndef Scroll_h
#define Scroll_h

#include "GameObject.h"
#include "utilities.h"
#include "Coord.h"
#include <iostream>
#include <string>

//Abstract Class
class Scroll: public GameObject
{
public:
    Scroll(std::string name):GameObject("Scroll", name){}
    virtual int effect(){return 0;}
private:
};

//------------------------------------------------------------------

class Teleportation: public Scroll
{
public:
    Teleportation():Scroll("scroll of teleportation"){}
    virtual int effect(){return 99;} // require fix
    virtual std::string action(){return "You feel your body wrenched in space and time.";}
    Coord teleport(){return Coord(randInt(18),randInt(70));}
};

class Armor: public Scroll
{
public:
    Armor():Scroll("scroll of improve armor"){}
    virtual int effect(){return randInt(1,4);}
    virtual std::string action(){return "Your armor glows blue.";}
};

class Strength: public Scroll
{
public:
    Strength():Scroll("scroll of raise strength"){}
    virtual int effect(){return randInt(1,4);}
    virtual std::string action(){return "Your muscles bulge.";}
};

class Health: public Scroll
{
public:
    Health():Scroll("scroll of enhance health"){}
    virtual int effect(){return randInt(3,9);}
    virtual std::string action(){return "You feel your heart beating stronger.";}
};

class Dexterity: public Scroll
{
public:
    Dexterity():Scroll("scroll of enhance dexterity"){}
    virtual int effect(){return 1;}
    virtual std::string action(){return "You feel like less of a klutz.";}
};

#endif /* Scroll_h */
