//
//  Monsters.cpp
//  Project3
//
//  Created by Oscar Cheng on 2020/5/20.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#include "Monsters.h"
#include <stack>
#include <cmath>
using namespace std;

void Monster::pathFind(char maze[][70], int sr, int sc, int er, int ec, int maxSteps)
{
    bool up = false, down = false ,left = false ,right = false;
    int row = sr; int col = sc; int rowDist = abs(sr-er); int colDist = abs(sc-ec); int steps = rowDist+colDist; //check the necessary steps to find the player
    if(steps > maxSteps || steps == 1) //if necessary steps exceeds 5 then exit;
        return;
    
    //check if player is up, down, right, or left of the monster
    if(er>sr) //row
        down = true;
    else if (er<sr)
        up = true;
    
    if(ec>sc) //col
        right = true;
    else if (ec<sc)
        left = true;

    //Check player's position relative to the monster, then check if monster should go up,down,right,or left
    if(down && left)
    {
        if(rowDist<colDist)
            row++;
        else if(colDist<rowDist)
            col--;
        else
        {
            if(maze[row+1][col] == '.')
                row++;
            else
                col--;
        }
    }
    else if(down && right)
    {
        if(rowDist<colDist)
            row++;
        else if (colDist<rowDist)
            col++;
        else
        {
            if(maze[row+1][col] == '.')
                row++;
            else
                col++;
        }
    }
    else if(up && left)
    {
        if(rowDist<colDist)
            row--;
        else if (colDist<rowDist)
            col--;
        else
        {
            if(maze[row-1][col] == '.')
                row--;
            else
                col--;
        }
    }
    else if(up && right)
    {
        if(rowDist<colDist)
            row--;
        else if (colDist<rowDist)
            col++;
        else
        {
            if(maze[row-1][col] == '.')
                row--;
            else
                col++;
        }
    }
    else if(up)
        row--;
    else if(down)
        row++;
    else if(left)
        col--;
    else if(right)
        col++;
    if(maze[row][col] == '.') //make monster move if the path is not blocked
    {
        char t = maze[sr][sc];
        maze[sr][sc] = '.';
        maze[row][col] = t;
        move(row, col);
    }
}

bool Goblin::pathFind(char maze[][70], char temp[][70], int sr, int sc, int er, int ec, int steps, int maxSteps)
{
    //check if goblin's current position is acceptable, not blocked by wall or monsters, and hasn't step more than the maximum steps it should take
    if((temp[sr][sc]!='.' && temp[sr][sc]!=')' && temp[sr][sc]!='?' && temp[sr][sc]!='G' && temp[sr][sc]!='>' && temp[sr][sc]!='&')|| steps>maxSteps)
        return false;
    if(sr == er && sc == ec) //base case
        return true;
    temp[sr][sc] = 'O'; //mark walked paths
        
    if(sr+1<18 && pathFind(maze,temp,sr+1,sc,er,ec,steps+1,maxSteps)) //if goblin can walk down, then recursive to continue explore
    {
        if(steps == 0 && maze[sr+1][sc] == '.') //if there's a path available, trace back to the initial step and move goblin's location
        {
            char t = maze[sr][sc];
            maze[sr][sc] = '.';
            maze[sr+1][sc] = t;
            move(sr+1,sc);
        }
        temp[sr][sc] = '.'; //
        return true;
    }
    if(sr-1>=0 && pathFind(maze,temp,sr-1,sc,er,ec,steps+1,maxSteps)) //if goblin can walk up, then recursive to continue explore
    {
        if(steps == 0 && maze[sr-1][sc] == '.')//if there's a path available, trace back to the initial step and move goblin's location
        {
            char t = maze[sr][sc];
            maze[sr][sc] = '.';
            maze[sr-1][sc] = t;
            move(sr-1,sc);
        }
        temp[sr][sc] = '.';
        return true;
    }
    if(sc+1<70 && pathFind(maze,temp,sr,sc+1,er,ec,steps+1,maxSteps)) //if goblin can walk right, then recursive to continue explore
    {
        if(steps == 0 && maze[sr][sc+1] == '.')//if there's a path available, trace back to the initial step and move goblin's location
        {
            char t = maze[sr][sc];
            maze[sr][sc] = '.';
            maze[sr][sc+1] = t;
            move(sr,sc+1);
        }
        temp[sr][sc] = '.';
        return true;
    }
    if(sc-1>=0 && pathFind(maze,temp,sr,sc-1,er,ec,steps+1,maxSteps)) //if goblin can walk left, then recursive to continue explore
    {
        if(steps == 0 && maze[sr][sc-1] == '.') //if there's a path available, trace back to the initial step and move goblin's location
        {
            char t = maze[sr][sc];
            maze[sr][sc] = '.';
            maze[sr][sc-1] = t;
            move(sr,sc-1);
        }
        temp[sr][sc] = '.';
        return true;
    }
    temp[sr][sc] = '.'; //erace goblin's traversed path after a step's possibility is fully explored
    return false;
}
