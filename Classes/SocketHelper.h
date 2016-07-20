//
//  SocketHelper.h
//  KinectGame
//
//  Created by ArcherPeng on 15/3/9.
//
//
//#pragma once
#ifndef __KinectGame__SocketHelper__
#define __KinectGame__SocketHelper__
#include "cocos2d.h"
#include <stdio.h>
#include "ODSocket.h"

class SocketHelper
{
private:
    static SocketHelper * sh;
    ODSocket s_client;
    void receive();
    bool isConnected;
public:
    void connect();
    void send(std::string str);
    static SocketHelper * getInstance()
    {
        if(!sh)
        {
            sh = new SocketHelper();
            sh->isConnected = false;
        }
        if (!sh->isConnected ) {
            sh->connect();
        }
        return sh;
    }
};
#endif /* defined(__KinectGame__SocketHelper__) */
