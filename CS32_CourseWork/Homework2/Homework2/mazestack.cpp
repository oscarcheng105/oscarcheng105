//
//  mazestack.cpp
//  Homework2
//
//  Created by Oscar Cheng on 2020/4/30.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#include <stack>
#include <iostream>
using namespace std;

/*class Coord
{
  public:
    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
  private:
    int m_row;
    int m_col;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    std::stack<Coord> mazeCoord;
    mazeCoord.push(Coord(sr,sc));
    maze[sr][sc] = 'O';
    int row,col;
    while(!mazeCoord.empty())
    {
        row = mazeCoord.top().r();
        col = mazeCoord.top().c();
        mazeCoord.pop();
        if(row == er && col == ec)
            return true;
        if(row+1 <= 9 && maze[row+1][col] == '.')
        {
            mazeCoord.push(Coord(row+1,col));
            maze[row+1][col] = 'O';
        }
        if (col-1 >= 0 && maze[row][col-1] == '.')
        {
            mazeCoord.push(Coord(row,col-1));
            maze[row][col-1] = 'O';
        }
        if (row-1 >= 0 && maze[row-1][col] == '.')
        {
            mazeCoord.push(Coord(row-1,col));
            maze[row-1][col] = 'O';
        }
        if (col+1 <= 9 && maze[row][col+1] == '.')
        {
            mazeCoord.push(Coord(row,col+1));
            maze[row][col+1] = 'O';
        }
    }
    return false;
}*/

