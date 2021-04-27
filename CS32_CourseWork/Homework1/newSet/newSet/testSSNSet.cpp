//
//  testSSNSet.cpp
//  newSet
//
//  Created by Oscar Cheng on 2020/4/15.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#include <cassert>
#include "SSNSet.h"
using namespace std;

int main()
{
    SSNSet a;
    assert(a.size()==0);
    a.add(1005);
    a.add(1231);
    assert(a.size()==2);
    //  a.print() prints out
    //  1005
    //  1231
    
}
