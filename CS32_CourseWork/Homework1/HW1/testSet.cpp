//
//  testSet.cpp
//  Homework1
//
//  Created by Oscar Cheng on 2020/4/15.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#include "Set.h"
#include <string>
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    ItemType x;
    
    Set s1;
    
    assert(s1.empty());
    
    s1.insert("John");
    
    assert(s1.contains("John"));
    assert(s1.erase("John"));
    assert(s1.get(0, x) == false);
    assert(s1.size() == 0);
    
    s1.insert("John");
    s1.insert("Oliver");
    
    Set s2;
    s2.insert("one");
    s2.insert("two");
    s2.insert("three");
    s2.insert("four");
    assert(s2.get(0, x) && x == "four");
    
    
    s2.swap(s1);
    assert(s1.size() == 4 && s1.contains("one") && s1.contains("two") && s1.contains("three") && s1.contains("four"));
    assert(s2.size() == 2 && s2.contains("John") && s2.contains("Oliver"));
}
