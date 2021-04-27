//
//  Player.cpp
//  Project3
//
//  Created by Oscar Cheng on 2020/5/17.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(int r,int c): Actor(*new shortSword, r, c, 20, 2, 2, 2,"Player")
{
    //m_bag.push_back(new shortSword());
    //m_weapon = dynamic_cast<Weapon*>(*m_bag.begin());
    m_bag.push_back(getWeapon());
}

Player::~Player()
{
    vector<GameObject*>::iterator p = m_bag.begin();
    switchWeapon(dynamic_cast<shortSword*>(*p));
    m_bag.clear();
}

void Player::cheat() //set player's stats to CHEAT VALUE
{
    if(maxHitPoints()<50)
        setMaxHitPoints(50);
    if(hitPoints()<50)
        setHitPoints(50);
    if(strength() < 9)
        setStrength(9);
}

bool Player::getItems(GameObject &g)
{
    if(m_bag.size()<=25)
    {
        m_bag.push_back(&g); //add object to inventory
        return true;
    }
    return false;
}

void Player::inventory()
{
    cout<<"Inventory:"<<endl;
    char s = 97;
    for(int i=0;i<m_bag.size();i++) //show all objects in inventory
    {
        cout<<s;
        cout<<". "+m_bag[i]->name()<<endl;
        s++;
    }
}

void Player::useScroll(char maze[][70], std::vector<std::string>& message)
{
    inventory();
    char input = getCharacter();
    int locate = input-97;
    int bonus = 0;
    if(locate<m_bag.size() && m_bag[locate]->type()=="Scroll") //check if player chooses Scroll when inputing r, and its input value is not out of bound
    {
        if(m_bag[locate]->name()=="scroll of teleportation") //use teleportation
        {
            Coord temp = dynamic_cast<Teleportation*>(m_bag[locate])->teleport(); //get teleported position
            while(maze[temp.row()][temp.col()]!='.') //check if teleported position is blocked, then reroll if yes
                temp = dynamic_cast<Teleportation*>(m_bag[locate])->teleport();
            maze[getCoord().row()][getCoord().col()] = '.';
            move(temp.row(),temp.col());
            message.push_back(m_bag[locate]->action());
        }
        else
        {
            if(m_bag[locate]->name()=="scroll of improve armor") // add value to armor
            {
                bonus = dynamic_cast<Armor*>(m_bag[locate])->effect();
                setArmor(armor()+bonus);
                message.push_back(m_bag[locate]->action());
            }
            else if(m_bag[locate]->name()=="scroll of enhance health") // add hitpoints
            {
                bonus = dynamic_cast<Health*>(m_bag[locate])->effect();
                if(hitPoints() == maxHitPoints())
                    setHitPoints(maxHitPoints()+bonus);
                setMaxHitPoints(maxHitPoints()+bonus);
                message.push_back(m_bag[locate]->action());
            }
            else if(m_bag[locate]->name()=="scroll of enhance dexterity") // add value to dexterity
            {
                bonus = dynamic_cast<Dexterity*>(m_bag[locate])->effect();
                setDexterity(dexterity()+bonus);
                message.push_back(m_bag[locate]->action());
            }
            else if(m_bag[locate]->name()=="scroll of raise strength") // add value to strength
            {
                bonus = dynamic_cast<Strength*>(m_bag[locate])->effect();
                setStrength(strength()+bonus);
                message.push_back(m_bag[locate]->action());
            }
        }
        m_bag.erase(m_bag.begin()+locate);
    }
    else if(locate<m_bag.size() && m_bag[locate]->type()=="Weapon") //show error if didn't choose scroll
        message.push_back("You can't read a "+m_bag[locate]->name()+".");
    clearScreen();
}
                                   
void Player::equipWeapon(std::vector<std::string>& message)
{
    inventory();
    char input = getCharacter();
    int locate = input-97;
    if(locate<m_bag.size() && m_bag[locate]->type()=="Weapon")
    {
        //chooses weapon
        if(m_bag[locate]->name()=="mace")
        {
            switchWeapon((dynamic_cast<mace*>(m_bag[locate])));
            message.push_back("You are wielding "+m_bag[locate]->name()+".");
        }
        else if(m_bag[locate]->name()=="short sword")
        {
            switchWeapon((dynamic_cast<shortSword*>(m_bag[locate])));
            message.push_back("You are wielding "+m_bag[locate]->name()+".");
        }
        else if(m_bag[locate]->name()=="long sword")
        {
            switchWeapon((dynamic_cast<longSword*>(m_bag[locate])));
            message.push_back("You are wielding "+m_bag[locate]->name()+".");
        }
        else if(m_bag[locate]->name()=="magic fangs of sleep")
        {
            switchWeapon((dynamic_cast<magicFangs*>(m_bag[locate])));
            message.push_back("You are wielding "+m_bag[locate]->name()+".");
        }
        else if(m_bag[locate]->name()=="magic axe")
        {
            switchWeapon((dynamic_cast<magicAxe*>(m_bag[locate])));
            message.push_back("You are wielding "+m_bag[locate]->name()+".");
        }
    }
    else if(locate<m_bag.size() && m_bag[locate]->type()=="Scroll") //show error if didn't choose weapon
        message.push_back("You can't wield the "+m_bag[locate]->name()+".");
    clearScreen();
}

