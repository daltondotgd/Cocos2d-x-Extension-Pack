#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "extpack.h"

class AnalogControlScene: public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(AnalogControlScene);

private:
    extpack::AnalogControl* analogControl;

};

#endif // __HELLOWORLD_SCENE_H__
