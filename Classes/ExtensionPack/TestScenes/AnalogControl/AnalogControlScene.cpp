#include "AnalogControlScene.h"

USING_NS_CC;
USING_NS_EP;

Scene* AnalogControlScene::createScene()
{
    auto scene = Scene::create();
    auto layer = AnalogControlScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool AnalogControlScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // AnalogControl example BEGIN
    analogControl = AnalogControl::createLayer();
    analogControl->setShowOnlyIfTouched(true);
    analogControl->setDeactivateOnRelease(true);
    analogControl->deactivate();

    //analogControl->setBoundingRect(Vec2::ZERO, Vec2(visibleSize.width / 2, visibleSize.height));

    //analogControl->setDigital();
    //analogControl->setNormalized();

    analogControl->onChange = [&](const cocos2d::Vec2& value, const float& dt)
    {
        CCLOG("%f, %f", value.x, value.y);
    };

    analogControl->easeFunc = [&](const float& value)
    {
        return sqrt(value);
    };

    addChild(analogControl, 9999);
    // AnalogControl example END

    auto label = Label::createWithTTF("Touch anywhere to test", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);

    return true;
}