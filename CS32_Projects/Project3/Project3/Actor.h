//
//  Actor.hpp
//  Project3
//
//  Created by Oscar Cheng on 2020/5/18.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#ifndef Actor_h
#define Actor_h

#include "Weapon.h"
#include "Coord.h"

class Actor
{
public:
    //Constructor/Destructor
    Actor(Weapon& w, int r, int c, int h, int a, int s, int d, std::string n): m_weapon(&w),m_position(r,c),m_hitPoints(h), m_armor(a), m_str(s), m_dex(d), m_sleep(0), m_maxHitPoints(h), m_name(n), m_living(true){}
    virtual ~Actor(){delete m_weapon;}
    
    //Accessors
    Weapon* getWeapon(){return m_weapon;}
    Coord getCoord(){return m_position;}
    int hitPoints(){return m_hitPoints;}
    int armor(){return m_armor;}
    int strength(){return m_str;}
    int dexterity(){return m_dex;}
    int maxHitPoints(){return m_maxHitPoints;}
    int sleep(){return m_sleep;}
    bool living(){return m_living;}
    std::string name(){return m_name;}
    
    //Modifiers
    void move(int r,int c){m_position.setCoord(r, c);}
    void switchWeapon(Weapon* w){m_weapon = w;}
    void setHitPoints(int i){if(i<100){m_hitPoints = i;}}
    void setArmor(int i){if(i<100){m_armor = i;}}
    void setStrength(int i){if(i<100){m_str = i;}}
    void setDexterity(int i){if(i<100){m_dex = i;}}
    void setMaxHitPoints(int i){if(i<100){m_maxHitPoints = i;}}
    void setSleep(int i){m_sleep=i;}
    void setLiving(bool i){m_living = i;}
    
private:
    Weapon* m_weapon;
    Coord m_position;
    int m_hitPoints;
    int m_armor;
    int m_str;
    int m_dex;
    int m_sleep;
    int m_maxHitPoints;
    std::string m_name;
    bool m_living;
};

#endif /* Actor_h */
