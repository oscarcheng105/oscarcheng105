//
//  eval.cpp
//  Homework2
//
//  Created by Oscar Cheng on 2020/4/30.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//
#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int evaluate(string infix, string& postfix, bool& result);
bool isOperator(char c);
bool isOperand(char c);
bool precedence(char c1, char c2);
bool valid(string& infix);
bool check(string postfix);
char operation1(char operand);
char operation2(char operand1, char operand2, char symbol);

int evaluate(string infix, string& postfix, bool& result)
{
    if(!valid(infix))
        return 1;
    postfix = "";
    stack<char> s;
    for(int i=0; i<infix.size();i++)
    {
        if(isOperand(infix[i]))
        {
            postfix += infix[i];
        }
        else if(infix[i] == '(')
        {
            s.push(infix[i]);
        }
        else if(infix[i] == ')')
        {
            while(s.top() != '(')
            {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else if(isOperator(infix[i]))
        {
            while(!s.empty() && s.top() != '(' && precedence(infix[i],s.top()))
            {
                postfix += s.top();
                s.pop();
            }
            s.push(infix[i]);
        }
    }
    while(!s.empty())
    {
        postfix+=s.top();
        s.pop();
    }
    result = check(postfix);
    return 0;
}
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.
    
bool isOperator(char c)
{
    switch(c)
    {
        case '&':
        case '^':
        case '!':
            return true;
    }
    return false;
}

bool isOperand(char c)
{
    switch(c)
        case 'T':
        case 'F':
            return true;
    return false;
}

bool precedence(char c1, char c2)
{
    if((c1 == '!' && c2 == '!') ||
       (c1 == '&' && (c2 =='!' || c2 == '&')) ||
       (c1 == '^' && (c2 == '!' || c2 == '&' || c2 == '^')))
        return true;
    return false;
}

bool valid(string& infix)
{
    if(infix == "")
        return false;
    
    int count = 0;
    string str = infix;
    infix = "";
    
    for(int j=0; j<str.size(); j++)
    {
        if(str[j]!=' ')
            infix+=str[j];
        if(str[j] == '(')
            count++;
        else if(str[j] == ')')
            count--;
    }
    
    if(count!=0)
        return false;
    
    for(int i=0; i<infix.size(); i++)
    {
        if(!isOperator(infix[i]) && !isOperand(infix[i]) && infix[i] != '(' && infix[i] != ')')
            return false;
        if(i != infix.size()-1)
        {
            if(isOperand(infix[i]) && isOperand(infix[i+1]))
                return false;
            if(isOperand(infix[i]) && infix[i+1]=='(')
                return false;
            if(isOperator(infix[i]) && infix[i] == ')') // ^)
                return false;
            if(infix[i] == '(') // (), (&, (^
                if(infix[i+1] == ')' || infix[i+1] == '&' || infix[i+1] == '^')
                    return false;
        }
        else
        {
            if(isOperator(infix[i]))
                return false;
        }
    }
    return true;
}

bool check(string postfix)
{
    char operand2,operand1;
    stack<char> s;
    for(int i=0; i<postfix.size();i++)
    {
        if(isOperand(postfix[i]))
            s.push(postfix[i]);
        else if(isOperator(postfix[i]))
        {
            if(postfix[i] == '&' || postfix[i] == '^')
            {
                operand2 = s.top();
                s.pop();
                operand1 = s.top();
                s.pop();
                s.push(operation2(operand1,operand2,postfix[i]));
            }
            else
            {
                operand1 = s.top();
                s.pop();
                s.push(operation1(operand1));
            }
        }
    }
    if(s.top() == 'T')
        return true;
    return false;
}

char operation1(char operand)
{
    if(operand == 'T')
        return 'F';
    return 'T';
}

char operation2(char operand1, char operand2, char symbol)
{
    if(symbol == '&')
    {
        if((operand1 == 'T' && operand2 == 'F') || (operand1 == 'F' && operand2 == 'T') || (operand1 == 'F' && operand2 == 'F'))
            return 'F';
    }
    else if (symbol == '^')
    {
        if((operand1 == 'F' && operand2 == 'F') || (operand1 == 'T' && operand2 == 'T'))
            return 'F';
    }
    return 'T';
}
