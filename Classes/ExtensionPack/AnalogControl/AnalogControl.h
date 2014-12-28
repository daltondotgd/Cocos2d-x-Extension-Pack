#ifndef __ANALOG_CONTROL_H__
#define __ANALOG_CONTROL_H__

#include "cocos2d.h"
#include <functional>

namespace extpack {

class AnalogControl
    : public cocos2d::LayerColor
{
public:

    // A helper class for definition of bounds of activation area (if showOnlyIfTouched is set)
    class BoundingRect {
    public:
        BoundingRect(const cocos2d::Vec2& lowerLeftCorner, const cocos2d::Vec2& upperRightCorner);
        BoundingRect() : BoundingRect(cocos2d::Vec2::ZERO, cocos2d::Vec2::ZERO) {}

        bool isSet();
        bool contains(const cocos2d::Vec2& point);

    private:
        cocos2d::Vec2 lowerLeft;
        cocos2d::Vec2 upperRight;

    };

    // a 'Create' function - use this instead of constructor
    static AnalogControl* createLayer();

    // handles updates
    virtual void update(float dt);

    // this is overriden to add touch event to the parent scene while added
    virtual void setParent(Node* parent) override;

    // an change callback that is called everytime the value changes
    std::function<void(const cocos2d::Vec2& value, const float& dt)> onChange;

    // a function that can ease the output - by default set to return squared value (it makes it easier
    // for a player to controll for example character's movement velocity)
    std::function<float(const float& value)> easeFunc = [](const float& value) { return pow(value, 2); };

    // returns current value of analog (from -1 to 1 on X axis and from -1 to 1 on Y axis)
    cocos2d::Vec2 getValue() { return value; };

    void activate() { active = true; };
    void deactivate() { active = false; };
    bool isActive() { return active; };

    // determines how far the knob can move
    void setRange(float r) { range = r; }
    float getRange() { return range; }

    // determines if value should always be normalized it means
    // it will always have a length of 1 - e.g. velocity will not
    // change if player holds his finger further or nearer to the
    // center point
    void setNormalized(bool value = true) { normalized = value; }
    bool isNormalized() { return normalized; }

    // if this is set, analog will go only in 8 directions
    void setDigital(bool value = true) { digital = value; }
    bool isDigital() { return digital; }

    // if this is set, analog will show under player's finger and disappear on released
    void setShowOnlyIfTouched(bool value) { showOnlyIfTouched = value; setVisible(!value); };
    bool isShowOnlyIfTouched() { return showOnlyIfTouched; };

    // id this is set, analog will be deactivated if finger was released - it's useful
    // when you decide to showOnlyIfTouched
    void setDeactivateOnRelease(bool value) { deactivateOnRelease = value; };
    bool isDeactivateOnRelease() { return deactivateOnRelease; };

    // a bounding rect of activation area - works only if showOnlyIfTouched is set
    void setBoundingRect(BoundingRect& rect) { boundingRect = rect; };
    void setBoundingRect(const cocos2d::Vec2& lowerLeft, const cocos2d::Vec2& upperRight) { boundingRect = BoundingRect(lowerLeft, upperRight); };
    BoundingRect& getBoundingRect() { return boundingRect; };

private:
    float range{ 50 };
    cocos2d::Sprite* base;
    cocos2d::Sprite* handle;
    cocos2d::Vec2 value{ 0, 0 };
    cocos2d::EventListenerTouchOneByOne* touchListener;
    bool normalized{ false };
    bool digital{ false };
    bool active{ true };
    bool showOnlyIfTouched{ false };
    bool deactivateOnRelease{ false };

    BoundingRect boundingRect;

    // initializes the analog - it is callet by createLayer()
    bool init();
    // adds touch events to this layer - called by createLayer()
    void addEvents();
};

}

#endif // __ANALOG_CONTROL_H__