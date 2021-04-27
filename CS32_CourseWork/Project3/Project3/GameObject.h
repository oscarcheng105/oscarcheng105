//
//  GameObject.hpp
//  Project3
//
//  Created by Oscar Cheng on 2020/5/17.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#ifndef GameObject_h
#define GameObject_h

#include <string>

class GameObject
{
public:
    GameObject(std::string type, std::string name):m_type(type), m_name(name), m_picked(false){}
    virtual ~GameObject(){}
    virtual std::string action(){return "";}
    std::string type(){return m_type;}
    std::string name(){return m_name;}
    bool picked(){return m_picked;}
    void setPicked(bool i){m_picked = i;}
private:
    std::string m_type;
    std::string m_name;
    bool m_picked;
};

class GoldenIdol: public GameObject
{
public:
    GoldenIdol():GameObject("Prize","the golden idol"){}
};

#endif /* GameObject_h */
