//
//  testnewSet.cpp
//  newSet
//
//  Created by Oscar Cheng on 2020/4/15.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//
#include "newSet.h"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    Set a(1000);   // a can hold at most 1000 distinct items
    Set b(5);      // b can hold at most 5 distinct items
    Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
    ItemType v[6] = {"one","two","three","four","five","six"};

      // No failures inserting 5 distinct items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(v[k]));

      // Failure if we try to insert a sixth distinct item into b
    assert(!b.insert(v[5]));

      // When two Sets' contents are swapped, their capacities are swapped
      // as well:
    a.swap(b);
    
    assert(!a.insert(v[5])  &&  b.insert(v[5]));
    
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
