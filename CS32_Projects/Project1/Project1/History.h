//
//  History.h
//  Project1
//
//  Created by Oscar Cheng on 2020/4/5.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#ifndef History_h
#define History_h

#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_rows;
    int m_cols;
    int m_grid[MAXROWS][MAXCOLS];
};

#endif /* History_h */
