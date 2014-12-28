Cocos2d-x-Extension-Pack
========================

Extension pack for Cocos2d-x (starting from v3.3 final), made by KNTG Polygon - a students organization on computer games. Everybody is welcome to contribute.

This pack is created to make some time consuming tasks or hard-to-find classes/algorithms easily avalible in this repository. Also all of the extensions avalible here will be tested and confirmed working with specific versions of Cocos2d-x.

List of extensions
==================

1. [AnalogControl](Classes/ExtensionPack/AnalogControl) - compound on-screen analogs for your game
1. A\* Path Finding - **COMMING SOON**
1. Actor helper class for better scene maintenance - **COMMING SOON**
1. AnimatedSprite helper class and animation utils - **COMMING SOON**
1. Box2d Debug Draw - **COMMING SOON**
1. Configuration Files Support - **COMMING SOON**
1. HealthBar UI item - **COMMING SOON**
1. Physical scene and sprites for box2d - **COMMING SOON**
1. QuickMenu scenes templates - **COMMING SOON**
1. Slider UI item - **COMMING SOON**
1. XBox Gamepad Supprot - **COMMING SOON**

How to?
=======

Just clone this repo to any Cocos2d-x v3.3 final project and start using.

All extensions are included in ```extpack.h``` file and they use ```extpack``` namespace. There is a macro ```USING_NS_EP``` that may be used in ```.cpp``` files - that is simply putting ```using namespace extpack``` to your code.

Contribution guide
==================

###Coding style

To make our code clear and unified, Cocos2d-x Extension Pack uses [Google C++ Coding Style Guide](http://google-styleguide.googlecode.com/svn/trunk/cppguide.html). This is really important, so if you pull request won't meet this condition, I'll send you back to this guide.

###Directory structure

Pick a name for your extension (for example 'YourExtension') and create a directory ```Classes/ExtensionPack/YouExtension``` - this is place for all of your classes. If your extension need some resources - you can also create a directory ```Resources/ExtensionPack/YourExtension```, where you'll put all your resources. Your plugin should also have a directory ```Classes/ExtensionPack/TestScenes/YourExtension``` - there you should create a demo scene, where your extension can be tested and other users can see an example use of it.

Directory tree of the Extension Pack will is meant to look like this:

```txt
Classes
  ExtensionPack
    ExtensionOne
    ExtensionTwo
    ExtensionThree

    TestScenes
      ExtensionOne
      ExtensionTwo
      ExtensionThree

Resources
  ExtensionPack
    ExtensionOne
    ExtensionTwo
    ExtensionThree
```

Why this structure? Because this project is meant to be easily added to any cocos project and easily managed by users - so it needs clean structure, so everybody can remove anythig he won't use or include just one desired extension.

###Namespace

All extensions should be created within namespace called ```extpack```

###Comments

Comments are required in header files - but only to documment non-trivial methods/fields or so. Don't write too much comments, but if something may not be clear, try tu explain it.

###Readme

Your extension should contain a ```Readme.md``` file, placed under ```Classes/ExtensionPack/YourExtension/```. The ```Readme.md``` file should contain a description and explain how to use your extension and provide all necessary information, so everybody can start using your classes after reading the file. This may be a tutorial or any kind of doc, but should contain all information one could desire.
