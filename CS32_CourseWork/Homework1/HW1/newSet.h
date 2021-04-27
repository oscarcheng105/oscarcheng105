//
//  newSet.hpp
//  newSet
//
//  Created by Oscar Cheng on 2020/4/15.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#ifndef newSet_h
#define newSet_h

#include <string>

using ItemType = std::string;
const int DEFAULT_MAX_ITEMS = 240;

class Set
{
public:
    Set();
    Set(int value);
    Set(const Set& s2);
    ~Set();
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const ;
    bool get(int i, ItemType& value) const;
    void swap(Set& other);
private:
    ItemType* m_items;
    int m_max = DEFAULT_MAX_ITEMS;
    int m_size = 0;
};

#endif /* newSet_hpp */
