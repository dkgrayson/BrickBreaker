#include "HelloWorldScene.h"
#include "game.h"
#include "options.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
	//Game *scene = Game::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
	CCSprite *new_game_button;
	CCSprite *option_button;
	bool sound = true;
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
    // 1. super init first
    if( !CCLayer::init())//RGBA
    {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();

	/*
	CCMenuItemImage *pNewGame = CCMenuItemImage::create("newgame.png", "newgame.png", this, menu_selector(HelloWorld::menuCloseCallback));
	CCMenu *pMenu = CCMenu::create(pNewGame);
	pMenu->setPosition(ccp(winsize.width/2, pMenu->getContentSize().height));
	this->addChild(pMenu);*/
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Brick Breaker", "Syncopate", 36);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + winsize.width/2,
                            origin.y + winsize.height - pLabel->getContentSize().height));
	pLabel->setColor(ccORANGE);

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
	CCLabelTTF* pLabel2 = CCLabelTTF::create("by David Grayson", "Syncopate", 30);
    
    // position the label on the center of the screen
    pLabel2->setPosition(ccp(origin.x + winsize.width/2,
                            origin.y + winsize.height - (pLabel->getContentSize().height)*2));
	pLabel2->setColor(ccORANGE);

    // add the label as a child to this layer
    this->addChild(pLabel2, 1);
	

	new_game_button = CCSprite::create("newgame2.png");
	//new_game_button->setScaleX(visibleSize.width/1000);
	//new_game_button->setScaleY(visibleSize.height/1000);
	new_game_button->setScale(1.0f);
	new_game_button->setPosition(ccp(winsize.width/2, new_game_button->getContentSize().height*4));
	this->addChild(new_game_button);

	option_button = CCSprite::create("options2.png");
	//option_button->setScaleX(visibleSize.width/1000);
	//option_button->setScaleY(visibleSize.height/1000);
	option_button->setScale(1.0f);
	option_button->setPosition(ccp(winsize.width/2, option_button->getContentSize().height*2));
	this->addChild(option_button);
    
    this->setTouchEnabled(true);
    return true;
}
void HelloWorld::update(float dt){
}
void HelloWorld::onEnter(){
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

}
void HelloWorld::onExit(){
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
}
bool HelloWorld::ccTouchBegan(CCTouch* touch, CCEvent* event){
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	 if (new_game_button->boundingBox().containsPoint(location))
	{
		CCScene *pScene = Game::scene();
		CCDirector::sharedDirector()->replaceScene(pScene);	
	}
	if (option_button->boundingBox().containsPoint(location))
	{
		CCScene *pScene2 = Options::scene();
		CCDirector::sharedDirector()->replaceScene(pScene2);
	}

    return true;
}
void HelloWorld::ccTouchMoved(CCTouch* touch, CCEvent* event){
    //do what you want
}
void HelloWorld::ccTouchEnded(CCTouch* touch, CCEvent* event){
//do your job here
}
void HelloWorld::touchDelegateRetain(){
	this->retain();
}
void HelloWorld::touchDelegateRelease(){
	this->release();
}
void HelloWorld::menuCloseCallback(CCObject* pSender)
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

