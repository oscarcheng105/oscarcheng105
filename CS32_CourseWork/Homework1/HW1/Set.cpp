//
//  Set.cpp
//  Homework1
//
//  Created by Oscar Cheng on 2020/4/15.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#include "Set.h"

Set::Set()
{
};         // Create an empty set (i.e., one with no items).

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
        if(m_arr[i] == value)
            return false;
    m_arr[m_size] = value;
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
        if(m_arr[i]==value)
        {
            for(j=i;j<m_size;j++)
                m_arr[j]=m_arr[j+1];
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
        if(m_arr[i] == value)
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
                if(m_arr[j]>m_arr[k])
                    count++;
            if(count == i)
            {
                value = m_arr[j];
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
    ItemType temp1;
    int temp2;
    int greater_length = m_size;
    if(other.size() > m_size)
        greater_length = other.size();
    for(int i=0;i<greater_length;i++)
    {
        temp1 = other.m_arr[i];
        other.m_arr[i] = m_arr[i];
        m_arr[i] = temp1;
    }
    temp2 = other.m_size;
    other.m_size = m_size;
    m_size = temp2;
}
  // Exchange the contents of this set with the other one.
