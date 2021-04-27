//
//  Set.h
//  Project2
//
//  Created by Oscar Cheng on 2020/4/22.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#ifndef Set_h
#define Set_h

#include <string>

using ItemType = std::string;

class Set
{
    struct node {
        ItemType m_value;
        node* m_next;
        node* m_prev;
    };
public:
    Set();
    Set(const Set& other);
    ~Set();
    Set& operator=(const Set& other);
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const ;
    bool get(int i, ItemType& value) const;
    void swap(Set& other);
private:
    node* m_head;
    int m_size;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif /* Set_h */
