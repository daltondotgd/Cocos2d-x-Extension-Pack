AnalogControl
=============

###An extension that allows you to put onscreen analogs on your scene.

Example:

In YourScene.h
```cpp
extpack::AnalogControl* analogControl;
```

In YourScene.cpp
```cpp
// Somewhere on top of the file
USING_NS_EP;

// ...

// in your init() method
analogControl = AnalogControl::createLayer();
analogControl->setPosition(200, 200);
addChild(analogControl, 9999);
```

If you want to create an analog that will show up only when player touched the screen,
change your code to this:

```cpp
analogControl = AnalogControl::createLayer();
analogControl->setShowOnlyIfTouched(true);
analogControl->setDeactivateOnRelease(true);
analogControl->deactivate();
addChild(analogControl, 9999); // we don't set the position, becouse it shows just under player's finger
```

You can also set a bounding area for this kind of analog - for example if you want our knob to activate
only on the left half of the screen - use this:

```cpp
Size visibleSize = Director::getInstance()->getVisibleSize();

// ...

// you pass here two points: first is a lower-left corner of the area
// and the second is an upper-right corner
analogControl->setBoundingRect(Vec2::ZERO, Vec2(visibleSize.width / 2, visibleSize.height));
```

Getting value
=============

To get the value of the analog just use getValue() - for example somewhere in your
update(float) method:

```cpp
void YourScene::update(float dt)
{

    // ...

    auto velocity = 10.0f;
    auto value = analogControl->getValue();
    player->setPosition(player->getPosition() + value * velocity * dt);

    // ...

}
```

You can also use the callback:

```cpp
auto velocity = 10.0f;

// ...

analogControl->onChange = [&](const cocos2d::Vec2& value, const float& dt)
{
    player->setPosition(player->getPosition() + value * velocity * dt);
};
```

D-Pad style
===========

To make your analog a directional pad use this:

```cpp
analogControl->setDigital(); // you can also unset this using setDigital(false)
```
this handles 8 directions.

Normalized output
=================

If you don't want player to control the value and only want to get information about
direction, you can set the analog to normalized - it means, the output will only be
0 or 1, nothing between:

```cpp
analogControl->setNormalized(); // again, you can unset this using setNormalized(false)
```

Changing output ease function
=============================

You can change way output is processed. For example, by default ease function is a squared value.
This means, that player will have more control on low values. We can change it to return square root
of the value, so the player will have more control on higher values.

Remember: your function should go through two points: (0, 0) and (1, 1). And usualy you don't want it
to return values greater than one or lower than zero.

```cpp
analogControl->easeFunc = [&](const float& value)
{
    return sqrt(value);
};
```
