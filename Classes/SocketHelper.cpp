//
//  SocketHelper.cpp
//  KinectGame
//
//  Created by ArcherPeng on 15/3/9.
//
//

#include "SocketHelper.h"
#include "KinectHelper.h"
SocketHelper * SocketHelper::sh = nullptr;
void SocketHelper::connect()
{
    //创建socket
    this->s_client.Init();
    bool res= this->s_client.Create(AF_INET, SOCK_STREAM,0);
    std::cout << "client socket create"<<res<<std::endl;
    //连接服务器
    res=this->s_client.Connect("127.0.0.1", 9000);
    std::cout << "client socket connect"<<res<<std::endl;
    if(res==1)
    {//启动线程
//        pthread_t tid;
//        bool ok= pthread_create(&tid, NULL, getMessage, NULL);
//        std::cout << "线程启动结果"<<ok<<endl;
        auto t = std::thread(&SocketHelper::receive, this);
        t.detach();
    }

}
void SocketHelper::receive()
{
    this->isConnected = true;
    std::cout<<"线程启动成功"<<endl;
    char buf[1024*64];
    while (this->s_client.Recv(buf, sizeof(buf)))
    {
//        CCLOG("Error ： %d",this->s_client.GetError());
        //接收服务器消息
        
                //s_client.Clean();
        for (int i = 0 ; i<1024*64; ++i)
        {
            if (buf[i]=='\n')
            {
                buf[i]='\0';
            }
        }
//	     std::cout << "recv --> "<<buf<<std::endl;
        std::string str = buf;
        cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([this,str]
        {
        KinectHelper::getInstance()->analyzeAndDispatchKinectData(std::string(str));
        });
    }
    //断开链接了
    this->s_client.Close();
    this->isConnected = false;
}
void SocketHelper::send(std::string str)
{
    const char * cStr = str.c_str();

    this->s_client.Send(cStr,strlen(cStr)+1);
}