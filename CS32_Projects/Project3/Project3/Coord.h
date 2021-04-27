//
//  Coord.hpp
//  Project3
//
//  Created by Oscar Cheng on 2020/5/17.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#ifndef Coord_h
#define Coord_h

#include <iostream>
class Coord
{
public:
    Coord(int row, int col): m_row(row), m_col(col){}
    void setCoord(int r,int c){m_row = r; m_col = c;}
    int row() {return m_row;}
    int col() {return m_col;}
private:
    int m_row;
    int m_col;
};

#endif /* Coord_h */
