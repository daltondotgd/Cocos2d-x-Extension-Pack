#include "AnalogControl.h"
#include "../ExtensionPackConfig.h"

#include <cmath>

USING_NS_CC;

AnalogControl* AnalogControl::createLayer()
{
    AnalogControl* analogControl = new AnalogControl();

    analogControl->create();

    analogControl->setColor(cocos2d::Color3B(0, 0, 0));

    analogControl->setContentSize(cocos2d::Size::Size(1, 1));
    analogControl->setAnchorPoint(cocos2d::Vec2(0, 0));

    analogControl->addEvents();

    analogControl->scheduleUpdate();
    analogControl->init();

    return analogControl;
}

bool AnalogControl::init()
{
    if (!LayerColor::init())
    {
        return false;
    }

    base = Sprite::create(EXTP_PATH"AnalogControl/base.png");
    addChild(base);

    handle = Sprite::create(EXTP_PATH"AnalogControl/handle.png");
    addChild(handle);

    return true;
}

void AnalogControl::addEvents()
{
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        if (active) {
            Vec2 touchLocation = base->convertTouchToNodeSpaceAR(touch);
            if (touchLocation.length() <= range + handle->getBoundingBox().size.width / 2) {

                if (showOnlyIfTouched)
                    setVisible(true);

                if (normalized || digital)
                {
                    touchLocation.normalize();
                    touchLocation *= range;
                    if (digital) {
                        float angle = round(round(touchLocation.getAngle() * 180 / M_PI) / 45) * 45 * M_PI / 180;
                        touchLocation = Vec2(cos(angle), sin(angle)) * range;
                    }
                    handle->setPosition(touchLocation);

                    if (base->convertTouchToNodeSpaceAR(touch).length() / range <= 0.5f) {
                        value = Vec2(0, 0);
                        handle->setPosition(value * range);
                        touchLocation = Vec2(0, 0);
                    }

                }

                if (touchLocation.length() <= range) {
                    handle->setPosition(touchLocation);
                    float displacement = touchLocation.length() / range;
                    value = Vec2(displacement * cos(touchLocation.getAngle()), displacement * sin(touchLocation.getAngle()));
                }
                else {
                    value = Vec2(cos(touchLocation.getAngle()), sin(touchLocation.getAngle()));
                    handle->setPosition(value * range);
                }

                if (onChange)
                    onChange(value, 0);

                CC_UNUSED_PARAM(touch);
                CC_UNUSED_PARAM(event);
                return true;
            }
        }
        return false;
    };

    touchListener->onTouchMoved = [this](Touch* touch, Event* event)
    {
        auto touchLocation = base->convertTouchToNodeSpaceAR(touch);
        if (normalized || digital)
        {
            touchLocation.normalize();
            touchLocation *= range;
            if (digital) {
                float angle = round(round(touchLocation.getAngle() * 180 / M_PI) / 45) * 45 * M_PI / 180;
                touchLocation = Vec2(cos(angle), sin(angle)) * range;
            }
            handle->setPosition(touchLocation);

            if (base->convertTouchToNodeSpaceAR(touch).length() / range <= 0.5f) {
                value = Vec2(0, 0);
                handle->setPosition(value * range);
                touchLocation = Vec2(0, 0);
            }

        }

        if (touchLocation.length() <= range) {
            handle->setPosition(touchLocation);
            float displacement = touchLocation.length() / range;
            value = Vec2(displacement * cos(touchLocation.getAngle()), displacement * sin(touchLocation.getAngle()));
        }
        else {
            value = Vec2(cos(touchLocation.getAngle()), sin(touchLocation.getAngle()));
            handle->setPosition(value * range);
        }

    };

    touchListener->onTouchEnded = [this](Touch* touch, Event* event)
    {
        value = Vec2(0, 0);
        if (onChange)
            onChange(value, 0);

        if (showOnlyIfTouched)
            setVisible(false);
        if (deactivateOnRelease)
            deactivate();
        handle->setPosition(0, 0);
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void AnalogControl::update(float dt)
{
    if (active && onChange) {
        auto power = 2; // non linear characteristics. set to 1 for linear
        auto radius = value.length();
        auto vec = Vec2(sin(value.x) * pow(radius, power), sin(value.y) * pow(radius, power));
        if (normalized || digital) {
            vec.normalize();
            if (digital) {
                float angle = round(round(vec.getAngle() * 180 / M_PI) / 45) * 45 * M_PI / 180;
                vec = Vec2(cos(angle), sin(angle)) * range;
            }
        }
        onChange(vec, dt);
    }
}