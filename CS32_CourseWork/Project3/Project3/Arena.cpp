//
//  Arena.cpp
//  Project3
//
//  Created by Oscar Cheng on 2020/5/16.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#include "Arena.h"
#include <iostream>
using namespace std;
Arena::Arena(int g):m_stairs(0,0)
{
    m_win = false;
    m_currentLevel = 0;
    m_goblinSmell = g;
    createLevel();
    addPlayer();
    addMonsters();
    addObjects();
}

Arena::~Arena()
{
    for(std::vector<Monster*>::iterator p=m_monsters.begin(); p!=m_monsters.end(); p++)
        delete (*p);
    for(std::vector<GameObject*>::iterator h=m_objects.begin(); h!=m_objects.end(); h++)
        delete (*h);
    delete m_player;
}

Player* Arena:: getPlayer()
{
    return m_player;
}

bool Arena:: getWin()
{
    return m_win;
}

void Arena::action(char &d)
{
    Coord temp = m_player->getCoord();
    int r = temp.row();
    int c = temp.col();
    if(trueWithProbability(0.1) && m_player->hitPoints()<m_player->maxHitPoints()) //check player's regeneration condition
        m_player->setHitPoints(m_player->hitPoints()+1);
    if(m_player->sleep() != 0) //check if player is asleep
        m_player->setSleep(m_player->sleep()-1);
    else
    {
        if(!playerMove(d,r,c)) //check if player has moved
        {   //if player doesn't move
            if((m_grid[r][c] == 'B' || m_grid[r][c] == 'S' || m_grid[r][c] == 'G' || m_grid[r][c] == 'D')) //check if player attacks
                playerHits(r, c);
            else if(d=='r') //check if player uses Scroll
                m_player->useScroll(m_grid, m_messages);
            else if(d=='w') //check if player equips weapon
                m_player->equipWeapon(m_messages);
        }
        if(d == 'g')//check if player picks up things
            pickUp();
        if(d == 'c')//check if player uses cheat
            m_player->cheat();
        if(d == '>')//check if player enters stairs and need to initial new dungeon level generation
            nextLevel();
    }
    monsterHits();
    monsterMove();
    display();
}

void Arena::pickUp()
{
    for(int i=0; i<m_objectLocation.size();i++) //Loop through all available yet picked game objects
        if(m_player->getCoord().row()==m_objectLocation[i].row() && m_player->getCoord().col()==m_objectLocation[i].col() && !m_objects[i]->picked())
            if(m_player->getItems(*m_objects[i])) //if player stands on the object's position and picks it up, store the object to player's inventory
            {
                m_messages.push_back("You picked up the "+m_objects[i]->name()+"."); //print the according messages and change object's condition to picked
                m_objects[i]->setPicked(true);
                if(m_objects[i]->name() == "the golden idol" )
                {
                    m_messages.push_back("Congratulations, you won!");
                    m_win = true;
                }
            }
}

bool Arena::playerMove(char &d,int &r, int &c)
{
    switch(d) //Check which input player inputed and update the correct direction
    {
        case 'h': c--; break;
        case 'l': c++; break;
        case 'j': r++; break;
        case 'k': r--; break;
    }
    //if direction directs to a invalid location, then exit function.
    if(m_grid[r][c] != '.' && m_grid[r][c] != ')' && m_grid[r][c] != '?' && m_grid[r][c] != '>' && m_grid[r][c] != '&')
        return false;
    //Update player location
    m_grid[m_player->getCoord().row()][m_player->getCoord().col()] = '.';
    m_player->move(r, c);
    return true;
}

void Arena::playerHits(const int &r, const int &c)
{
    for(std::vector<Monster*>::iterator p = m_monsters.begin(); p!= m_monsters.end();p++) //if player hits any living monsters in the monster list
        if((**p).getCoord().row() == r && (**p).getCoord().col() == c && (**p).living()) // then run the hit() function
        {
            m_messages.push_back(hit(*m_player, (**p)));
            break;
        }
}

void Arena::monsterMove()
{
    char temp[MAXROWS][MAXCOLS];
    for(std::vector<Monster*>::iterator p = m_monsters.begin(); p!= m_monsters.end(); p++) //Go through all living monsters
        if((**p).living() && (**p).sleep() == 0 && ((**p).name() == "the Snakewomen" || (**p).name() == "the Bogeymen"))
        {
            //Run the simple path find if Snakewomen or Bogeymen is alive and awake
            (**p).pathFind(m_grid, (**p).getCoord().row(), (**p).getCoord().col(), m_player->getCoord().row(), m_player->getCoord().col(), 5);
        }
        else if((**p).living() && (**p).name() == "the Dragon")
        {
            //Check if it's health is under its MaxHealth and give it randomized regeneration possibility.
            if(trueWithProbability(0.1) && (**p).hitPoints()<(**p).maxHitPoints())
                (**p).setHitPoints((**p).hitPoints()+1);
        }
        else if((**p).living() && (**p).sleep() == 0 && (**p).name() == "the Goblin")  //Run the goblin pathfind if goblin is alive and awake
        {
            for(int i=0;i<MAXROWS;i++) //Generate a temporary template for the goblin so it can check existance of path
                for(int j=0;j<MAXCOLS;j++)
                    temp[i][j] = m_grid[i][j];
            //calculate necessary steps to get to player
            int dist = abs((**p).getCoord().row()-m_player->getCoord().row())+abs((**p).getCoord().col()-m_player->getCoord().col());
            //if necessary steps is more than one step and under the scope of Goblin's smell Distance, then run goblin PathFind script
            if(dist>1 && dist<=m_goblinSmell)
                dynamic_cast<Goblin*>(*p)->pathFind(m_grid, temp, (**p).getCoord().row(), (**p).getCoord().col(), m_player->getCoord().row(), m_player->getCoord().col(), 0 , dist);
        }
}

void Arena::monsterHits()
{
    int pr = m_player->getCoord().row();
    int pc = m_player->getCoord().col();
    std::vector<Monster*>::iterator p;
    for(p = m_monsters.begin(); p!= m_monsters.end();p++) //go throught the list of monsters
    {
        int mr = (**p).getCoord().row();
        int mc = (**p).getCoord().col();
        //Allow each monsters to check if player is around them (up,down,right,left), then hit player if condition passes
        if(((mr+1 == pr && mc == pc) || (mr-1 == pr && mc == pc) || (mc+1 == pc && mr == pr) || (mc-1 == pc && mr == pr)) && (**p).living())
            m_messages.push_back(hit((**p),*m_player));
    }
}

string Arena::hit(Actor& a1, Actor& a2)
{
    int attackerPoints = a1.dexterity() + a1.getWeapon()->dexterity(); //Generate hit formula
    int defenderPoints = a2.dexterity() + a2.armor();
    if(randInt(1,attackerPoints)>=randInt(1,defenderPoints) && a2.hitPoints()>0) //Check hit formula
    {
        int damagePoints = randInt(0,(a1.strength()+a1.getWeapon()->damage()-1));
        a2.setHitPoints(a2.hitPoints()-damagePoints); //reduce defender health
        if(a2.hitPoints()<=0) //Set living condition if defender dies (both Monster and Player)
        {
            if(a2.name()!="Player")
                monsterDead(a2);
            else
            {
                m_player->setLiving(false);
                m_player->setHitPoints(0);
            }
            return a1.name()+a1.getWeapon()->action()+a2.name()+" dealing the final blow.";
        }
        if(a1.getWeapon()->name() == "magic fangs of sleep" && randInt(5)==0) //Checks magicFangs condition if attacker uses magicFangs
         {
             int sleepTime = randInt(2,6);
             if(a2.sleep() == 0 || (a2.sleep() != 0 && a2.sleep()<sleepTime))
                 a2.setSleep(sleepTime);
             return a1.name()+a1.getWeapon()->action()+a2.name()+" and hits, putting "+a2.name()+" to sleep.";
         }
        return a1.name()+a1.getWeapon()->action()+a2.name()+" and hits."; //If hit formula passes then attacker hits defender
    }
    return a1.name()+a1.getWeapon()->action()+a2.name()+" and misses.";//if hit formula didn't pass then attacker misses the defender
}

void Arena::monsterDead(Actor& m)
{
    m_grid[m.getCoord().row()][m.getCoord().col()] = '.'; //set it's position grid as empty
    loot(m); //Trigger loot. (drop loot)
    for(vector<Monster*>::iterator p = m_monsters.begin(); p!=m_monsters.end();p++) //match the correct monster that died and mark as dead (living = false)
        if(*p == &m)
        {
            (**p).setLiving(false);
            break;
        }
}

void Arena::loot(Actor& m)
{
    for(int i=0;i<m_objects.size();i++) //make sure that the location where monster died doesn't have any gameobjects
        if(!m_objects[i]->picked() && m.getCoord().row() == m_objectLocation[i].row() && m.getCoord().col() == m_objectLocation[i].col())
            return;
    //See which monster died and generate appropriate gameObjects with randomized chances (Except Dragon)
    if(m.name()=="the Goblin" && randInt(3)==0)
    {
        if(randInt(2)==0)
            m_objects.push_back(new magicAxe);
        else
            m_objects.push_back(new magicFangs);
        m_objectLocation.push_back(*new Coord(m.getCoord().row(),m.getCoord().col()));
    }
    else if(m.name()=="the Snakewomen" && randInt(3)==0)
    {
        m_objects.push_back(new magicFangs);
        m_objectLocation.push_back(*new Coord(m.getCoord().row(),m.getCoord().col()));
    }
    else if(m.name()=="the Bogeymen" && randInt(10)==0)
    {
        m_objects.push_back(new magicAxe);
        m_objectLocation.push_back(*new Coord(m.getCoord().row(),m.getCoord().col()));
    }
    else if(m.name()=="the Dragon")
    {
        int scrolls = randInt(5);
        switch(scrolls)
        {
            case 0: m_objects.push_back(new Teleportation()); break;
            case 1: m_objects.push_back(new Strength()); break;
            case 2: m_objects.push_back(new Dexterity()); break;
            case 3: m_objects.push_back(new Armor()); break;
            case 4: m_objects.push_back(new Health()); break;
        }
        m_objectLocation.push_back(*new Coord(m.getCoord().row(),m.getCoord().col()));
    }
}

void Arena::display()
{
    for(int i=0;i<m_objects.size();i++) //Check that all AVAILABLE game objects is properly showed in dungeon
    {
        if(!m_objects[i]->picked() && m_objects[i]->type()=="Weapon" && m_grid[m_objectLocation[i].row()][m_objectLocation[i].col()] == '.')
            m_grid[m_objectLocation[i].row()][m_objectLocation[i].col()] = ')';
        else if(!m_objects[i]->picked() && m_objects[i]->type()=="Scroll" && m_grid[m_objectLocation[i].row()][m_objectLocation[i].col()] == '.')
            m_grid[m_objectLocation[i].row()][m_objectLocation[i].col()] = '?';
        else if(!m_objects[i]->picked() && m_objects[i]->type()=="Prize" && m_grid[m_objectLocation[i].row()][m_objectLocation[i].col()] == '.')
            m_grid[m_objectLocation[i].row()][m_objectLocation[i].col()] = '&';
    }
    
    if(m_grid[m_stairs.row()][m_stairs.col()] == '.' && m_currentLevel<4) //Check that stairs is properly showed in dungeon even after other Actors walk pass it
        m_grid[m_stairs.row()][m_stairs.col()] = '>';
    
    m_grid[m_player->getCoord().row()][m_player->getCoord().col()] = '@'; //Make sure player is appropriatedly printed after it moves;
    
    for(int i=0; i<MAXROWS; i++)
    {
        for(int j=0; j<MAXCOLS; j++)
            std::cout<<m_grid[i][j];
        std::cout<<std::endl;
    }
    
    std::cout<<"Dungeon Level: "<<m_currentLevel<<
    ", Hit points: "<<m_player->hitPoints()<<
    ", Armor: "<<m_player->armor()<<
    ", Strength: "<<m_player->strength()<<
    ", Dexterity: "<<m_player->dexterity()<<std::endl;
    
    std::cout<<std::endl;
    
    for(vector<string>::iterator p=m_messages.begin(); p!=m_messages.end();p++) //print out all message that should be showned
        cout<<(*p)<<endl;
    m_messages.clear();
}


//---------------------------------------------------------------------------------------------PRIVATE HELPERS

void Arena::nextLevel()
{
    if(m_player->getCoord().row() != m_stairs.row() && m_player->getCoord().col() != m_stairs.col()) //check if the player stands on the stairs
        return;
    for(int i=0;i<m_objects.size();i++) //Set all objects from the previous level as picked so Player cannot access them anymore
        if(!m_objects[i]->picked() && m_objects[i]->type()!= "Prize")
            m_objects[i]->setPicked(true);
    for(int j=0;j<m_monsters.size();j++) //Set all monsters from the previous level as dead so Player do not encounter them anymore
        if(m_monsters[j]->living())
            m_monsters[j]->setLiving(false);
    //Create new level
    m_currentLevel++;
    createLevel();
    addPlayer();
    addMonsters();
    addObjects();
}
//Establish dungeon area
void Arena::createLevel()
{
    for(int i=0; i<MAXROWS; i++) //Create a fixed dungeon room
    {
        for(int j=0; j<MAXCOLS; j++)
        {
            if(i>2 && i<15 && j>2 && j<67)
                m_grid[i][j] = '.';
            else
                m_grid[i][j] = '#';
            if((i<10 || i>11) && j>14 && j<22 )
                m_grid[i][j] = '#';
        }
    }
    if(m_currentLevel<4) //Add stairs to the dungeon room until level 4
    {
        int r,c;
        do{
            r=randInt(18);
            c=randInt(70);
        }while(m_grid[r][c] != '.');
        m_grid[r][c]='>';
        m_stairs.setCoord(r, c);
    }
}

//Place player to level
void Arena::addPlayer()
{
    int r,c;
    if(m_currentLevel==0)
    {
        do{
            r = randInt(18);
            c = randInt(70);
            if(m_grid[r][c] == '.')
            {
                m_grid[r][c] = '@';
                if(m_currentLevel == 0)
                    m_player = new Player(r,c); //generate new player object when its the initial level (level 0)
            }
        }while(m_grid[r][c] != '@');
    }
    else
    {
        do{
        r = randInt(18);
        c = randInt(70);
        }while(m_grid[r][c] != '.'); //only place the player on empty spaces;
        m_grid[r][c] = '@';
        m_player->move(r, c);
    }
}

//Place monsters to level
void Arena::addMonsters()
{
    int r,c;
    int monsterAmount = randInt(2, 5*(m_currentLevel+1)+1);
    for(int i=0;i<monsterAmount;i++) //Generate number of monsters based on the given formula randInt(2, 5*(m_currentLevel+1)+1)
    {
        int generate;
        if(m_currentLevel<=1) //Check which kind of monsters can be generated based on current dungeon level
            generate = randInt(2);
        else if(m_currentLevel<3)
            generate = randInt(3);
        else
            generate = randInt(4);
        do{
        r = randInt(18);
        c = randInt(70);
        }while(m_grid[r][c] != '.'); //only place the monster on empty spaces;
        if(generate==0)
        {
            m_monsters.push_back(new Goblin(r,c));
            m_grid[r][c] = 'G';
        }
        else if(generate==1)
        {
            m_monsters.push_back(new Snakewomen(r,c));
            m_grid[r][c] = 'S';
        }
        else if(generate==2 && m_currentLevel>1 )
        {
            m_monsters.push_back(new Bogeymen(r,c));
            m_grid[r][c] = 'B';
        }
        else if(generate==3 && m_currentLevel>2 )
        {
            m_monsters.push_back(new Dragon(r,c));
            m_grid[r][c] = 'D';
        }
    }
}

void Arena::addObjects()
{
    int r, c;
    int objectAmount =randInt(2,3);
    for(int i=0;i<objectAmount;i++) //Generate Gameobjects based on a randomized number of 2 and 3
    {
        int generate = randInt(7); //Randomize probability of each object's generation
        do{ r = randInt(18);
            c = randInt(70);
        }while(m_grid[r][c] != '.'); //only place the object on empty spaces;
        if(generate<3)
        {
            if(generate==0)
                m_objects.push_back(new longSword());
            else if(generate==1)
                m_objects.push_back(new shortSword());
            else if(generate==2)
                m_objects.push_back(new mace());
            m_grid[r][c] = ')';
        }
        else
        {
            if(generate==3)
                m_objects.push_back(new Armor());
            else if(generate==4)
                m_objects.push_back(new Strength());
            else if(generate==5)
                m_objects.push_back(new Dexterity());
            else if(generate==6)
                m_objects.push_back(new Health());
            m_grid[r][c] = '?';
        }
        m_objectLocation.push_back(*new Coord(r,c));
    }
    if(m_currentLevel==4) //if it's the endLevel, place the GoldenIdol
    {
        do{ r = randInt(18);
            c = randInt(70);
        }while(m_grid[r][c] != '.');
        m_objects.push_back(new GoldenIdol());
        m_objectLocation.push_back(*new Coord(r,c));
        m_grid[r][c] = '&';
    }
}
