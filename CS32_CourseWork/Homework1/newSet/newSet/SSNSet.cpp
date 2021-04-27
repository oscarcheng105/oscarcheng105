//
//  SSNSet.cpp
//  newSet
//
//  Created by Oscar Cheng on 2020/4/15.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//
#include "SSNSet.h"
#include <iostream>
using namespace std;

SSNSet::SSNSet()
{
}// Create an empty SSN set.
bool SSNSet::add(ItemType ssn)
{
    return m_set.insert(ssn);;
}
    // Add an SSN to the SSNSet.  Return true if and only if the SSN
    // was actually added.
int SSNSet::size() const
{
    return m_set.size();
}// Return the number of SSNs in the SSNSet.
void SSNSet::print() const
{
    ItemType item;
    for(int i=0;i<size();i++)
    {
        m_set.get(i, item);
        cout<<item<<endl;
    }
}
    // Write to cout every SSN in the SSNSet exactly once, one per
    // line.  Write no other text.
