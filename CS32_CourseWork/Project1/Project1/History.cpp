//
//  History.cpp
//  Project1
//
//  Created by Oscar Cheng on 2020/4/5.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    for(int r=0;r<MAXROWS;r++)
        for(int c=0;c<MAXCOLS;c++)
            m_grid[r][c]=0;
}

bool History::record(int r, int c)
{
    if((r>m_rows || r<1 || c>m_cols || c<1))
        return false;
    m_grid[r-1][c-1] += 1;
    return true;
}

void History::display() const
{
    clearScreen();
    char displaygrid[MAXROWS][MAXCOLS];
    for(int r=0; r<m_rows; r++)
        for(int c=0; c<m_cols; c++)
            switch(m_grid[r][c])
            {
                case 0: displaygrid[r][c] = '.'; break;
                case 1: displaygrid[r][c] = 'A'; break;
                case 2: displaygrid[r][c] = 'B'; break;
                case 3: displaygrid[r][c] = 'C'; break;
                case 4: displaygrid[r][c] = 'D'; break;
                case 5: displaygrid[r][c] = 'E'; break;
                case 6: displaygrid[r][c] = 'F'; break;
                case 7: displaygrid[r][c] = 'G'; break;
                case 8: displaygrid[r][c] = 'H'; break;
                case 9: displaygrid[r][c] = 'I'; break;
                case 10: displaygrid[r][c] = 'J'; break;
                case 11: displaygrid[r][c] = 'K'; break;
                case 12: displaygrid[r][c] = 'L'; break;
                case 13: displaygrid[r][c] = 'M'; break;
                case 14: displaygrid[r][c] = 'N'; break;
                case 15: displaygrid[r][c] = 'O'; break;
                case 16: displaygrid[r][c] = 'P'; break;
                case 17: displaygrid[r][c] = 'Q'; break;
                case 18: displaygrid[r][c] = 'R'; break;
                case 19: displaygrid[r][c] = 'S'; break;
                case 20: displaygrid[r][c] = 'T'; break;
                case 21: displaygrid[r][c] = 'U'; break;
                case 22: displaygrid[r][c] = 'V'; break;
                case 23: displaygrid[r][c] = 'W'; break;
                case 24: displaygrid[r][c] = 'X'; break;
                case 25: displaygrid[r][c] = 'Y'; break;
                default: displaygrid[r][c] = 'Z'; break;
            }
    for(int r=0; r<m_rows; r++)
    {
        for(int c=0; c<m_cols; c++)
            cout << displaygrid[r][c];
        cout<<endl;
    }
    cout<<endl;
}
