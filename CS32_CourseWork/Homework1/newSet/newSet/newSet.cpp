//
//  newSet.cpp
//  newSet
//
//  Created by Oscar Cheng on 2020/4/15.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#include "newSet.h"

Set::Set()
{
    m_items = new ItemType [m_max];
}// Create an empty set (i.e., one with no items).

Set::Set(int value)
{
    m_max = value;
    m_items = new ItemType [m_max];
}

Set::Set(const Set& s2)
{
    m_max = s2.m_max;
    m_items = new ItemType[m_max];
    m_size = s2.m_size;
    for(int i=0; i<m_size;i++)
        *(m_items+i) = *(s2.m_items+i);
}

Set::~Set()
{
    delete[] m_items;
}

bool Set::empty() const
{
    if(m_size == 0)
        return true;
    return false;
}  // Return true if the set is empty, otherwise false.

int Set::size() const
{
    return m_size;
}    // Return the number of items in the set.

bool Set::insert(const ItemType& value)
{
    for(int i=0; i<m_size; i++)
        if(*(m_items+i) == value || m_size == m_max)
            return false;
    *(m_items+m_size) = value;
    m_size++;
    return true;
}
  // Insert value into the set if it is not already present.  Return
  // true if the value is actually inserted.  Leave the set unchanged
  // and return false if the value was not inserted (perhaps because it
  // was already in the set or because the set has a fixed capacity and
  // is full).

bool Set::erase(const ItemType& value)
{
    int i, j;
    for(i=0;i<m_size;i++)
        if(*(m_items+i)==value)
        {
            for(j=i;j<m_size;j++)
                *(m_items+j)=m_items[j+1];
            m_size--;
            return true;
        }
    return false;
}
  // Remove the value from the set if it is present.  Return true if the
  // value was removed; otherwise, leave the set unchanged and
  // return false.
 
bool Set::contains(const ItemType& value) const
{
    for(int i=0;i<m_size;i++)
        if(*(m_items+i) == value)
            return true;
    return false;
}
  // Return true if the value is in the set, otherwise false.
 
bool Set::get(int i, ItemType& value) const
{
    int count, j, k;
    if(i>=0 && i<m_size)
        for(j=0;j<m_size;j++)
        {
            count = 0;
            for(k=0;k<m_size;k++)
                if(*(m_items+j) > *(m_items+k))
                    count++;
            if(count == i)
            {
                value = *(m_items+j);
                return true;
            }
        }
    return false;
}
  // If 0 <= i < size(), copy into value the item in the set that is
  // strictly greater than exactly i items in the set and return true.
  // Otherwise, leave value unchanged and return false.

void Set::swap(Set& other)
{
    ItemType* temp1 = other.m_items;
    other.m_items = m_items;
    m_items = temp1;
    
    int temp2 = other.m_size;
    other.m_size = m_size;
    m_size = temp2;
    
    int temp3 = other.m_max;
    other.m_max = m_max;
    m_max = temp3;
}
  // Exchange the contents of this set with the other one.

