//
//  KinectHelper.h
//  KinectGame
//
//  Created by ArcherPeng on 15/5/7.
//
//
//#pragma once
#ifndef __KinectGame__KinectHelper__
#define __KinectGame__KinectHelper__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
class KinectHelper:public Ref
{
public:
    void analyzeAndDispatchKinectData(std::string str);
    void dispatchKinectData(std::map<std::string, Vec3>);
    static KinectHelper * getInstance()
    {
        if(!sh)
        {
            sh = new KinectHelper();
        }
        return sh;
    }

protected:
    static KinectHelper * sh;
};

#endif /* defined(__KinectGame__KinectHelper__) */
