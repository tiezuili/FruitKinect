//
//  KinectHelper.cpp
//  KinectGame
//
//  Created by ArcherPeng on 15/5/7.
//
//

#include "KinectHelper.h"

KinectHelper * KinectHelper::sh = nullptr;
void KinectHelper::dispatchKinectData(std::map<std::string, Vec3> vecMap)
{
    cocos2d::EventCustom event("KinectData");
    event.setUserData((void *) &vecMap);
    CCLOG("X  %f Y  %f Z  %f", vecMap["nearstHand"].x,vecMap["nearstHand"].y,vecMap["nearstHand"].z);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    
}
void KinectHelper::analyzeAndDispatchKinectData(std::string str)
{
    do
    {
        
        rapidjson::Document jsonData;
        jsonData.Parse<rapidjson::kParseDefaultFlags>(str.c_str());
        if (jsonData.HasParseError())
        {
            CCLOG("GetParseError : %s",jsonData.GetParseError());
            break;
        }
        if(!jsonData.IsObject())
        {
            CCLOG("not Object");
            break;
        }
        
        
        //是否有此成员
        if(!jsonData.HasMember("methodId"))
        {
            CCLOG("no Member methodId");
            break;
        }
        
        const rapidjson::Value &jMethodId = jsonData["methodId"];
        int methodId = jMethodId.GetInt();      //得到int值
        if (methodId == 1007)
        {           
            Vec3 vec ;
            const rapidjson::Value &jx = jsonData["x"];
            vec.x = jx.GetInt();
            const rapidjson::Value &jy = jsonData["y"];
            vec.y = jy.GetInt();
            const rapidjson::Value &jz = jsonData["z"];
            vec.z = jz.GetInt();
            std::map<std::string,Vec3> handMap;
            handMap["nearstHand"]=vec;           
            this->dispatchKinectData(handMap);
        }     
    } while (false);
}