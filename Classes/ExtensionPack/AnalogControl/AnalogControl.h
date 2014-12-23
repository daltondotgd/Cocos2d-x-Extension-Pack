#ifndef __ANALOG_CONTROL_H__
#define __ANALOG_CONTROL_H__

#include "cocos2d.h"
#include <functional>

class AnalogControl : public cocos2d::LayerColor
{
public:
    AnalogControl() {}

    static AnalogControl* createLayer();

    bool init();
    void addEvents();

    virtual void update(float dt);

    std::function<void(const cocos2d::Vec2& value, const float& dt)> onChange;

    float range{ 50 };
    CREATE_FUNC(AnalogControl);

    cocos2d::Vec2 getValue() { return value; };

    void activate() { active = true; };
    void deactivate() { active = false; };
    bool isActive() { return active; };

    void setNormalized(bool value = true) { normalized = value; }
    bool isNormalized() { return normalized; }

    void setDigital(bool value = true) { digital = value; }
    bool isDigital() { return digital; }

    void setShowOnlyIfTouched(bool value) { showOnlyIfTouched = value; setVisible(!value); };
    bool isShowOnlyIfTouched() { return showOnlyIfTouched; };

    void setDeactivateOnRelease(bool value) { deactivateOnRelease = value; };
    bool isDeactivateOnRelease() { return deactivateOnRelease; };

private:
    cocos2d::Sprite* base;
    cocos2d::Sprite* handle;
    cocos2d::Vec2 value{ 0, 0 };
    cocos2d::EventListenerTouchOneByOne* touchListener;
    bool normalized{ false };
    bool digital{ false };
    bool active{ true };
    bool showOnlyIfTouched{ false };
    bool deactivateOnRelease{ false };

};

#endif // __ANALOG_CONTROL_H__