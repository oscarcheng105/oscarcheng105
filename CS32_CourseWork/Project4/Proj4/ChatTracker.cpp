//
//  ChatTracker.cpp
//  Project4
//
//  Created by Oscar Cheng on 2020/6/4.
//  Copyright © 2020 Oscar Cheng. All rights reserved.
//

#include "ChatTracker.h"
#include <functional>
#include <string>
#include <vector>
#include <list>
#include <iostream>
using namespace std;

  // This class does the real work of the implementation.

class ChatTrackerImpl
{
  public:
    ChatTrackerImpl(int maxBuckets);
    void join(string user, string chat);
    int terminate(string chat);
    int contribute(string user);
    int leave(string user, string chat);
    int leave(string user);

  private:
    struct Chat;
    struct User
    {
        User(string n): m_name(n), m_currentCount(0){}
    
        string m_name;
        string m_currentChat;
        int m_currentCount;
        
        vector<int> m_count;
        vector<Chat*> m_chats;
    };
    
    struct Chat
    {
        Chat(string n): m_name(n), m_count(0){}
        
        string m_name;
        int m_count;
        vector<User*> m_members;
    };

    vector<list<Chat>> m_chats; //keep count current existing chats
    vector<list<User>> m_users; //keep count current existing users
    hash<string> myuserhash;
    hash<string> mychathash;
    int m_maxBuckets;
};

ChatTrackerImpl::ChatTrackerImpl(int maxBuckets):m_maxBuckets(maxBuckets)
{
    for(int i=0; i<m_maxBuckets;i++)
    {
        list<Chat> c;
        list<User> u;
        m_chats.push_back(c);
        m_users.push_back(u);
    }
}

void ChatTrackerImpl::join(string user, string chat)
{
    int userIndex = myuserhash(user)%m_maxBuckets;
    int chatIndex = mychathash(chat)%m_maxBuckets;
    list<Chat>::iterator p_chat = m_chats[chatIndex].begin();
    list<User>::iterator p_user = m_users[userIndex].begin();
    bool chatExist = false;
    bool userExist = false;
    bool userExistInChat = false;
    bool chatExistInUser = false;
    
    //Find Chat
    for(; p_chat!=m_chats[chatIndex].end(); p_chat++)
        if((*p_chat).m_name==chat)
        {
            chatExist = true;
            break;
        }
    if(!chatExist) //Add Chat
    {
        m_chats[chatIndex].push_back(Chat(chat));
        p_chat = m_chats[chatIndex].end();
        p_chat--;
        chatExist = true;
    }
    
    //Find User
    for(; p_user!=m_users[userIndex].end(); p_user++)
        if((*p_user).m_name==user)
        {
            userExist = true;
            break;
        }
    if(!userExist) //Add User
    {
        m_users[userIndex].push_back(User(user));
        p_user = m_users[userIndex].end();
        p_user--;
        userExist = true;
    }
    
    //Find User in Chat
    for(int i=0;i<(*p_chat).m_members.size();i++)
        if((*p_chat).m_members[i]->m_name == user)
        {
            userExistInChat = true;
            break;
        }
    if(!userExistInChat)//Add User to Chat
        (*p_chat).m_members.push_back(&(*p_user));
    
    //Find Chat in User
    for(int j = 0;j<(*p_user).m_chats.size();j++)
        if((*p_user).m_chats[j]->m_name == chat)
        {
            chatExistInUser = true;
            if(chatExistInUser && (*p_user).m_currentChat != chat)
            {
                (*p_user).m_chats.push_back((*p_user).m_chats[j]);
                (*p_user).m_chats.erase((*p_user).m_chats.begin()+j);
                (*p_user).m_count.push_back((*p_user).m_count[j]);
                (*p_user).m_count.erase((*p_user).m_count.begin()+j);
            }
            break;
        }
    if(!chatExistInUser)//Add Chat to User
    {
        (*p_user).m_chats.push_back(&(*p_chat));
        (*p_user).m_count.push_back(0);
    }
    //Change user's current chat to chat
    (*p_user).m_currentChat = (*p_user).m_chats.back()->m_name;
    (*p_user).m_currentCount = (*p_user).m_count.back();
}

int ChatTrackerImpl::terminate(string chat)
{
    int chatIndex = mychathash(chat)%m_maxBuckets;
    list<Chat>::iterator p_chat = m_chats[chatIndex].begin();
    bool chatExist = false;
    int count = 0;
    
    for(; p_chat != m_chats[chatIndex].end();p_chat++)
        if((*p_chat).m_name == chat)
        {
            chatExist = true;
            break;
        }
    if(chatExist)
    {
        for(int i=0;i<(*p_chat).m_members.size();i++)
        {
            for(int j =0; j<(*p_chat).m_members[i]->m_chats.size();j++)
                if((*p_chat).m_members[i]->m_chats[j]->m_name == chat)
                {
                    (*p_chat).m_members[i]->m_chats.erase((*p_chat).m_members[i]->m_chats.begin()+j);
                    (*p_chat).m_members[i]->m_count.erase((*p_chat).m_members[i]->m_count.begin()+j);
                    if((*p_chat).m_members[i]->m_currentChat == chat)
                    {
                        if((*p_chat).m_members[i]->m_chats.size() == 0)
                        {
                            (*p_chat).m_members[i]->m_currentChat.clear();
                            (*p_chat).m_members[i]->m_currentCount = 0;
                        }
                        else
                        {
                            (*p_chat).m_members[i]->m_currentChat = (*p_chat).m_members[i]->m_chats.back()->m_name;
                            (*p_chat).m_members[i]->m_currentCount = (*p_chat).m_members[i]->m_count.back();
                        }
                    }
                    break;
                }
        }
        count = (*p_chat).m_count;
        m_chats[chatIndex].erase(p_chat);
    }
    return count;
}

int ChatTrackerImpl::contribute(string user)
{
    int userIndex = myuserhash(user)%m_maxBuckets;
    list<User>::iterator p_user = m_users[userIndex].begin();
    bool userExist = false;
    
    for(; p_user != m_users[userIndex].end(); p_user++)
        if((*p_user).m_name == user)
        {
            userExist = true;
            break;
        }
    if(userExist)
    {
        if(!(*p_user).m_currentChat.empty())
        {
            for(int i=0;i<(*p_user).m_chats.size();i++)
                if((*p_user).m_chats[i]->m_name == (*p_user).m_currentChat)
                {
                    (*p_user).m_chats[i]->m_count++;
                    (*p_user).m_currentCount++;
                    (*p_user).m_count[i] = (*p_user).m_currentCount;
                    return (*p_user).m_currentCount;
                }
        }
    }
    return 0;
}

int ChatTrackerImpl::leave(string user, string chat)
{
    int chatIndex = mychathash(chat)%m_maxBuckets;
    list<Chat>::iterator p_chat = m_chats[chatIndex].begin();
    bool chatExist = false;
    int count = -1;
    
    for(; p_chat != m_chats[chatIndex].end();p_chat++)
        if((*p_chat).m_name == chat)
        {
            chatExist = true;
            break;
        }
    if(chatExist)
        for(int i=0;i<(*p_chat).m_members.size();i++)
            if((*p_chat).m_members[i]->m_name == user)
            {
                User* temp = (*p_chat).m_members[i];
                for(int j=0;j<temp->m_chats.size();j++)
                {
                    if(temp->m_chats[j]->m_name == chat)
                    {
                        count = temp->m_count[j];
                        if(temp->m_chats[j]->m_name == temp->m_currentChat)
                        {
                            temp->m_chats.erase(temp->m_chats.begin()+j);
                            temp->m_count.erase(temp->m_count.begin()+j);
                            if(temp->m_chats.size()!= 0)
                            {
                                temp->m_currentChat = temp->m_chats.back()->m_name;
                                temp->m_currentCount = temp->m_count.back();
                            }
                            else
                            {
                                temp->m_currentChat.clear();
                                temp->m_currentCount = 0;
                            }
                        }
                        else
                        {
                            temp->m_chats.erase(temp->m_chats.begin()+j);
                            temp->m_count.erase(temp->m_count.begin()+j);
                        }
                        break;
                    }
                }
                break;
            }
    return count;
}

int ChatTrackerImpl::leave(string user)
{
    int userIndex = myuserhash(user)%m_maxBuckets;
    list<User>::iterator p_user = m_users[userIndex].begin();
    bool userExist = false;
    int count = -1;
    
    for(; p_user != m_users[userIndex].end(); p_user++)
        if((*p_user).m_name == user)
        {
            userExist = true;
            break;
        }
    if(userExist)
        if(!(*p_user).m_currentChat.empty())
        {
            for(int i=0;i<(*p_user).m_chats.size();i++)
            {
                if((*p_user).m_chats[i]->m_name == (*p_user).m_currentChat)
                {
                    count = (*p_user).m_count[i];
                    (*p_user).m_chats.erase((*p_user).m_chats.begin()+i);
                    (*p_user).m_count.erase((*p_user).m_count.begin()+i);
                    if((*p_user).m_chats.size() != 0)
                    {
                        (*p_user).m_currentChat = (*p_user).m_chats.back()->m_name;
                        (*p_user).m_currentCount = (*p_user).m_count.back();
                    }
                    else
                    {
                        (*p_user).m_currentChat.clear();
                        (*p_user).m_currentCount = 0;
                    }
                    break;
                }
            }
        }
    return count;
}

//*********** ChatTracker functions **************

// These functions simply delegate to ChatTrackerImpl's functions.
// You probably don't want to change any of this code.

ChatTracker::ChatTracker(int maxBuckets)
{
    m_impl = new ChatTrackerImpl(maxBuckets);
}

ChatTracker::~ChatTracker()
{
    delete m_impl;
}

void ChatTracker::join(string user, string chat)
{
    m_impl->join(user, chat);
}

int ChatTracker::terminate(string chat)
{
    return m_impl->terminate(chat);
}

int ChatTracker::contribute(string user)
{
    return m_impl->contribute(user);
}

int ChatTracker::leave(string user, string chat)
{
    return m_impl->leave(user, chat);
}

int ChatTracker::leave(string user)
{
    return m_impl->leave(user);
}
