//
//  Set.cpp
//  Project2
//
//  Created by Oscar Cheng on 2020/4/22.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#include "Set.h"

Set::Set()
{
    m_head = nullptr;
    m_size = 0;
}      // Create an empty set (i.e., one with no items).

Set::Set(const Set& other)
{
    m_head = nullptr;
    m_size = other.m_size;
    node* other_temp = other.m_head;
    node* temp = nullptr;
    for(int i = 0; i < other.m_size; i++) //run through all items of other
    {
        node* p = new node; //create new node;
        p->m_value = other_temp->m_value;
        if(m_head == nullptr) //assign node to head if head is null, create reference temp for head
        {
            m_head = p;
            temp = m_head;
            temp->m_next= nullptr;
        }
        else //if head is not null, organize links and update temp
        {
            temp->m_next = p;
            temp->m_next->m_prev = temp;
            temp = temp->m_next;
            temp->m_next= nullptr;
        }
        other_temp = other_temp->m_next; //move to next node of other
    }
}

Set::~Set()
{
    m_size = 0;
    while (m_head!=nullptr) //if head is not null, create temproaray and asign head, move pointer of head, and delete temp.
    {
        node* temp = m_head;
        m_head = m_head->m_next;
        delete temp;
    }
}

Set& Set::operator=(const Set& other)
{
    Set temp = other; //create new Set temp that copies other
    swap(temp); //swap the current Set with temp
    return (*this); //return the current Set
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
    node* p = new node; //Create new node
    p->m_value = value;
    
    node* repeat = m_head;
    while(repeat!=nullptr)//Avoid duplicates
    {
        if(repeat->m_value == value)
        {
            delete p;
            return false;
        }
        repeat = repeat->m_next;
    }

    node* end = m_head;
    while(end!= nullptr && end->m_next != nullptr) //move end to position before last nullptr
        end = end->m_next;
    //Arrange links
    p->m_next = nullptr;
    p->m_prev = end;
    if(end!=nullptr)
        end->m_next = p;
    else
        m_head = p;
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
    node* temp = m_head;
    while(temp!=nullptr)
    {
        if(temp->m_value == value)
        {
            if(temp == m_head){ //if value is at head
                if(temp->m_next != nullptr) //if Set has more than one item
                {
                    m_head = temp->m_next;
                    temp->m_next->m_prev = nullptr;
                }
                else if(temp->m_next == nullptr) //if Set only has head
                    m_head = nullptr;
            }
            else if(temp->m_next == nullptr)//if value is at the end
                temp->m_prev->m_next = nullptr;
            else //if value is in between items
            {
                temp->m_prev->m_next = temp->m_next;
                temp->m_next->m_prev = temp->m_prev;
            }
            delete temp;
            m_size--;
            return true;
        }
        temp = temp->m_next;
    }
    return false;
}

  // Remove the value from the set if it is present.  Return true if the
  // value was removed; otherwise, leave the set unchanged and
  // return false.
 
bool Set::contains(const ItemType& value) const
{
    node* temp = m_head;
    while(temp!=nullptr)//goes through Set and see if value matches to each item
    {
        if(temp->m_value == value)
            return true;
        temp = temp->m_next;
    }
    return false;
}
  // Return true if the value is in the set, otherwise false.
 
bool Set::get(int i, ItemType& value) const
{
    int count;
    node* temp = m_head;
    node* temp2;
    do
    {  //goes through the Set, match each item with other items to see if current item is greater than exactly i items in the set
        count = 0;
        temp2 = m_head;
        while(temp2!=nullptr)
        {
            if(temp->m_value > temp2->m_value)
                count++;
            temp2 = temp2->m_next;
        }
        if(count == i)
        {
            value = temp->m_value;
            return true;
        }
        temp = temp->m_next;
    }while(count != i && temp != nullptr);
    return false;
}
  // If 0 <= i < size(), copy into value the item in the set that is
  // strictly greater than exactly i items in the set and return true.
  // Otherwise, leave value unchanged and return false.

void Set::swap(Set& other)
{
    node* temp = m_head;
    m_head = other.m_head;
    other.m_head = temp;
    int t = m_size;
    m_size = other.m_size;
    other.m_size = t;
}
  // Exchange the contents of this set with the other one.

void unite(const Set& s1, const Set& s2, Set& result)
{
    ItemType match;
    for(int i=result.size()-1; i>=0; i--) //clear original items in result
    {
        result.get(i, match); //get each item in result
        result.erase(match); //erase item node
    }
    for(int j=0; j<s1.size();j++) //add s1 to result
    {
        s1.get(j,match); //get each item in s1
        result.insert(match); //add each item in s1 to result
    }
    for(int k=0; k<s2.size();k++) //add s2 to result
    {
        s2.get(k,match); //get each item in s2
        result.insert(match); //add each item in s2 to result
    }
}

void subtract(const Set& s1, const Set& s2, Set& result)
{
    ItemType match;
    for(int i=result.size()-1; i>=0; i--) //clear original items in result
    {
        result.get(i, match); //get each item in result
        result.erase(match); //erase each item
    }
    for(int j=0; j<s1.size(); j++) //add s1 to result
    {
        s1.get(j,match); //get each item in s1
        result.insert(match); //add each item in s1 to result
    }
    for(int k=s2.size(); k>=0; k--) //erase items that overlap with s1
        if(s2.get(k,match)) //get each item in s2
            result.erase(match); //erase item in result
}
