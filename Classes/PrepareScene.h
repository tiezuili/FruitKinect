//
//  PrepareScene.h
//  cutfruit
//
//  Created by jiumiao on 15/10/1.
//
//

#ifndef __cutfruit__PrepareScene__
#define __cutfruit__PrepareScene__

#include "cocos2d.h"
#include "SocketHelper.h"
USING_NS_CC;
class PrepareScene:public Layer
{
public:
	void onEnter();
	void onExit();
	void kinectCallback(cocos2d::EventCustom * event);
	//Vec2 point;
    PrepareScene();//添加构造函数
    virtual bool init();
    static Scene *scene();
    CREATE_FUNC(PrepareScene);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    void loadlogo();//加载logo
    void loadtitle();//加载标题
    void loadmenu();//加载菜单
    int index;//条带索引位置
    Array * m_fruitBrokArr;//创建容器保存水果
    void onKeyReleased(EventKeyboard::KeyCode keyCode,Event *event);
    void scle1_rotate();
    void scle2_rotate();
    void scle3_rotate();
    void peach_rotate();
    void sandia_rotate();
    void boom_rotate();
    void update(float delta);//声明要执行的计划任务
    void loadGame();//加载游戏
    void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
    void onDraw(const Mat4 &transform, uint32_t flags );
   CustomCommand  mdd_customCommand;
    private:
    void mydraw();//声明绘画的方法
    //CustomCommand cCommad;
    MotionStreak *streak;//创建拖尾效果
    float angel;//旋转角度
    bool ifstart;//触摸开始标志
    Point pt;//默认点的位置
    Size size;
    Point _point[2];//定义一个长度为2的数组，用于保存点
    bool ifColli(int tag,Point point);//获取触摸后的水果和水果位置
    void Colli(int tag);//获取水果
    
};
#endif /* defined(__cutfruit__PrepareScene__) */
