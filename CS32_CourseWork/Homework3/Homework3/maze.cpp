//
//  maze.cpp
//  Homework3
//
//  Created by Oscar Cheng on 2020/5/7.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//
#include <iostream>
using namespace std;

class Coord
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
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
            cout<<maze[i][j];
    cout<<endl;
    }
    cout<<endl;
    if (maze[sr][sc] != '.')
        return false;

    if (sr == er  &&  sc == ec)
        return true;

    maze[sr][sc] = 'O';  // anything non-'.' will do

    if (pathExists(maze, sr-1, sc, er, ec))
        return true;
    if (pathExists(maze, sr+1, sc, er, ec))
        return true;
    if (pathExists(maze, sr, sc-1, er, ec))
        return true;
    if (pathExists(maze, sr, sc+1, er, ec))
        return true;
    maze[sr][sc]='.';
    return false;
}

int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','X','.','.','.','X' },
        { 'X','.','X','X','.','X','X','.','.','X' },
        { 'X','X','X','.','.','.','.','X','.','X' },
        { 'X','.','X','X','X','.','X','X','X','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','.','.','X','.','X','.','.','X' },
        { 'X','X','X','X','X','.','X','.','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3,5, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
