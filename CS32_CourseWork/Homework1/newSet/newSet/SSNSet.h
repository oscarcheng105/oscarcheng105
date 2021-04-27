//
//  SSNSet.hpp
//  newSet
//
//  Created by Oscar Cheng on 2020/4/15.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#ifndef SSNSet_h
#define SSNSet_h

#include "newSet.h"

class SSNSet
{
  public:
    SSNSet();
    bool add(ItemType ssn);
    int size() const;
    void print() const;
  private:
    Set m_set;
};
#endif /* SSNSet_hpp */
