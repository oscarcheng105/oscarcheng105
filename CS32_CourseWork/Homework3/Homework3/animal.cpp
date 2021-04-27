//
//  animal.cpp
//  Homework3
//
//  Created by Oscar Cheng on 2020/5/4.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//
#include <string>
#include <iostream>
using namespace std;

class Animal{
public:
    Animal(string str): m_name(str){};
    virtual ~Animal(){};
    virtual void speak() const = 0;
    virtual string moveAction() const = 0;
    string name() const {return m_name;};
private:
    string m_name;
    
};

class Cat : public Animal{
public:
    Cat(string str):Animal(str){};
    Cat(string str, int weight):
        Animal(str), m_weight(weight){};
    virtual ~Cat()
        {cout<<"Destroying "<< Animal::name() <<" the cat"<<endl;};
    virtual void speak() const
        {cout<<"Meow";};
    virtual string moveAction() const
        {return "walk";};
private:
    int m_weight;
};

class Pig : public Animal{
public:
    Pig(string str):Animal(str){};
    Pig(string str, int weight): Animal(str), m_weight(weight){};
    virtual ~Pig()
        {cout<<"Destroying "<< Animal::name() <<" the pig"<<endl;};
    virtual void speak() const
        {if(m_weight>=160)
            cout<<"Grunt";
        else
            cout<<"Oink";};
    virtual string moveAction() const
        {return "walk";};
private:
    int m_weight;
};

class Duck : public Animal{
public:
    Duck(string str):Animal(str){};
    Duck(string str, int weight): Animal(str), m_weight(weight){};
    virtual ~Duck()
    {cout<<"Destroying "<< Animal::name() <<" the duck"<<endl;};
    virtual void speak() const
        {cout<<"Quack";};
    virtual string moveAction() const
        {return "swim";};
private:
    int m_weight;
};
