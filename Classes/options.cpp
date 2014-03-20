#include "HelloWorldScene.h"
#include "options.h"

USING_NS_CC;
CCScene* Options::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Options *layer = Options::create();
	//Game *scene = Game::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
	CCSprite *enable_button;
	CCSprite *disable_button;
	//bool sound = true;
// on "init" you need to initialize your instance
bool Options::init()
{
	//////////////////////////////
    // 1. super init first
    if( !CCLayer::init())//RGBA
    {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    
    CCLabelTTF* pLabel4 = CCLabelTTF::create("Brick Breaker", "Syncopate", 36);
    
    // position the label on the center of the screen
    pLabel4->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel4->getContentSize().height));
	pLabel4->setColor(ccORANGE);

    // add the label as a child to this layer
    this->addChild(pLabel4);

	CCLabelTTF* pLabel5 = CCLabelTTF::create("by David Grayson", "Syncopate", 30);
    
    // position the label on the center of the screen
    pLabel5->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel5->getContentSize().height*2));
	pLabel5->setColor(ccORANGE);

    // add the label as a child to this layer
    this->addChild(pLabel5);
	
	if(!sound){
		enable_button = CCSprite::create("enable_sound2.png");
		//enable_button->setScaleX(visibleSize.width/1000);
		//enable_button->setScaleY(visibleSize.height/1000);
		enable_button->setScale(1.0f);
		enable_button->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
		this->addChild(enable_button);
	}
	else{
		disable_button = CCSprite::create("disable_sound2.png");
		//disable_button->setScaleX(visibleSize.width/1000);
		//disable_button->setScaleY(visibleSize.height/1000);
		disable_button->setScale(1.0f);
		disable_button->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
		this->addChild(disable_button);
	}
    
    
    return true;
}
void Options::update(float dt){
}
void Options::onEnter(){
    CCDirector* pDirector = CCDirector::sharedDirector();
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(Options::update),this,0,false);
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

}
void Options::onExit(){
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
}
bool Options::ccTouchBegan(CCTouch* touch, CCEvent* event){
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	if(!sound){
		 if (enable_button->boundingBox().containsPoint(location))
		{
			sound = true;
			CCScene *pScene = HelloWorld::scene();
			CCDirector::sharedDirector()->replaceScene(pScene);	
		}
	}
	else{
		 if (disable_button->boundingBox().containsPoint(location))
		{
			sound = false;
			CCScene *pScene = HelloWorld::scene();
			CCDirector::sharedDirector()->replaceScene(pScene);
		}
	}

    return true;
}
void Options::ccTouchMoved(CCTouch* touch, CCEvent* event){
    //do what you want
}
void Options::ccTouchEnded(CCTouch* touch, CCEvent* event){
//do your job here
}
void Options::touchDelegateRetain(){
	this->retain();
}
void Options::touchDelegateRelease(){
	this->release();
}
void Options::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

