#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  AppDelegate : private cocos2d::CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

typedef struct tagResource  
{  
    cocos2d::CCSize size;  
    char directory[100];  
}Resource;  
   
//���õ���Դ�ߴ�  
static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),   "iphone" };  
static Resource mediumResource =  { cocos2d::CCSizeMake(1024, 768),  "ipad"   };  
static Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "ipadhd" };  
   
//��Ʒ���  
static cocos2d::CCSize smallDesignResolutionSize = cocos2d::CCSizeMake(480.0f, 320.0f);  
static cocos2d::CCSize mediumDesignResolutionSize = cocos2d::CCSizeMake(1024.0f, 768.0f);  
static cocos2d::CCSize largeDesignResolutionSize = cocos2d::CCSizeMake(2048.0f, 1536.0f);  
   
//�������ӣ���Ҫ�����ֱ�ǩʹ��  
#define SCALE_FACTOR  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width)  
   


#endif  // __APP_DELEGATE_H__

