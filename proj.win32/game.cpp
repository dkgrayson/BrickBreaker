#include "game.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

USING_NS_CC;
	class brick{
		float xCoord;
		float yCoord;
		float xScale;
		float yScale;
		bool visibility;
		CCSprite *RedBrick;
	public:
		void set_xScale(int width);
		void set_yScale(int height);
		float get_xCoord();
		float get_yCoord();
		float get_width();
		float get_height();
		void set_xCoord(int x, int h, int width);
		void set_yCoord(int y, int j, int height);
		void createBrick(int width, int height);
		CCSprite* getBrick();
		void set_visibility(bool visibility);
		bool get_visibility();
	};
	void brick::set_xScale(int width){
		xScale = (float)width/3500;
	}
	void brick::set_yScale(int height){
		yScale = (float)height/1500;
	}
	float brick::get_xCoord(){
		return xCoord;
	}
	float brick::get_yCoord(){
		return yCoord;
	}
	float brick::get_width(){
		return RedBrick->boundingBox().size.width;
	}
	float brick::get_height(){
		return RedBrick->boundingBox().size.height;
	}
	void brick::set_xCoord(int x, int h, int width){
		xCoord = width - x - ( RedBrick->boundingBox().size.width*h );
	}
	void brick::set_yCoord(int y, int j, int height){
		yCoord = height - y - ( (RedBrick->boundingBox().size.height * 1.2) * j );
		
	}
	void brick::createBrick(int width, int height){
		RedBrick = CCSprite::create("Block.jpg");
		//RedBrick->setScaleX((float)width/2000);
		//RedBrick->setScaleY((float)height/1500);
		RedBrick->setScale(0.5f);
		RedBrick->setVisible(visibility);
	}

	CCSprite* brick::getBrick(){
		return RedBrick;
	}
	void brick::set_visibility(bool visibility){
		this->visibility = visibility;
	}

	bool brick::get_visibility(){
		return visibility;
	}

	
	CCSprite *paddle;
	CCSprite *ball;
	CCLabelTTF *score_label;
	CCLabelTTF *lives_label;
	bool down = true;
	bool left = true;
	brick *bricks;
	int brick_index;
	bool touched;
	int score;
	int lives;
	//bool sound;

CCScene* Game::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Game *layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
	CCSprite *new_game_button2;
	CCSprite *option_button2;
// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	score = 0;
	lives = 3;
	down = true;
	left = true;
	bricks = new brick[100];
	brick_index = 0;
	touched = false;

    CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	if(sound){
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("explosion_small.wav"); 
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("laser_ship.wav"); 
	}
	
	char text[256];
	sprintf(text,"Score: %d", score);
	score_label = CCLabelTTF::create();
	score_label->setString(text);
	score_label->setFontSize(20);
	score_label->setPosition(ccp(visibleSize.width/2,score_label->boundingBox().size.height/2));
	this->addChild(score_label);
	sprintf(text,"Lives: %d", lives);
	lives_label = CCLabelTTF::create();
	lives_label->setString(text);
	lives_label->setFontSize(20);
	lives_label->setPosition(ccp(visibleSize.width/2 + score_label->boundingBox().size.width + 8,lives_label->boundingBox().size.height/2));
	this->addChild(lives_label);

	{
		paddle = CCSprite::create("Paddle2.jpg");
		paddle->setScale(.35f);
		paddle->setPosition(ccp(visibleSize.width/2, (visibleSize.height * .1)));
		this->addChild(paddle);
		paddle->setPosition(ccp(visibleSize.width/2 + 20, (visibleSize.height * .1)));
	}
		
	ball = CCSprite::create("Ball2.jpg");
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	ball->setScale(0.3f);
    ball->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2) );
    this->addChild(ball);	


			int x = 50;
			int y = 20;
			int width = visibleSize.width;
			int maxSize = width;
			int height = visibleSize.height;
			int h = 0;
			int j = 0;
			brick _brick;

			while(maxSize >0){
				_brick.createBrick(width, height);
				_brick.set_xScale(width);
				_brick.set_yScale(height);
				_brick.set_visibility(true);
				_brick.set_xCoord(x, h, width);
				_brick.set_yCoord(y, 0, height);
				_brick.getBrick()->setPosition(ccp(_brick.get_xCoord(), _brick.get_yCoord()));
				bricks[brick_index] = _brick;
				brick_index++;
				this->addChild(_brick.getBrick());
				_brick.createBrick(width, height);
				_brick.set_xScale(width);
				_brick.set_yScale(height);
				_brick.set_visibility(true);
				_brick.set_xCoord(x, h, width);
				_brick.set_yCoord(y, 1, height);
				_brick.getBrick()->setPosition(ccp(_brick.get_xCoord(), _brick.get_yCoord()));
				bricks[brick_index] = _brick;
				brick_index++;
				this->addChild(_brick.getBrick());
				h++;
				x += 10;
				maxSize = maxSize - _brick.get_width() - 20;
			}
			new_game_button2 = CCSprite::create("newgame2.png");
			//new_game_button2->setScaleX(visibleSize.width/1000);
			//new_game_button2->setScaleY(visibleSize.height/1000);
			new_game_button2->setScale(1.0f);
			new_game_button2->setPosition(ccp(winsize.width/2, new_game_button2->getContentSize().height*4));
			new_game_button2->setVisible(false);
			this->addChild(new_game_button2);

			option_button2 = CCSprite::create("home2.png");
			//option_button2->setScaleX(visibleSize.width/1000);
			//option_button2->setScaleY(visibleSize.height/1000);
			option_button2->setScale(1.0f);
			option_button2->setPosition(ccp(winsize.width/2, option_button2->getContentSize().height*2));
			option_button2->setVisible(false);
			this->addChild(option_button2);
			this->scheduleUpdate();
			
			this->setTouchEnabled(true);
	return true;
}

void Game::update(float dt){
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();

	float maxX = visibleSize.width - ball->getContentSize().width/2;
	float minX = ball->getContentSize().width/2;
	float maxY = visibleSize.height - ball->getContentSize().height/2;
	float minY = ball->getContentSize().height/2;

	if(touched){
		if(score < 10*(brick_index)){
			if(lives > 0){
				if(down && left){
					if(ball->getPositionX() > minX){
						if(ball->getPositionY() > minY){
							if(ball->boundingBox().intersectsRect(paddle->boundingBox())){
								if(sound){
									CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("laser_ship.wav"); 
								}
								down = false;
							}
							else{
								ball->setPosition(ccp(ball->getPositionX() - 4, ball->getPositionY() - 4));
								for(int n = 0; n < brick_index; n++){
									if(ball->boundingBox().intersectsRect(bricks[n].getBrick()->boundingBox()) && bricks[n].get_visibility()){
										if(sound){
											CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explosion_small.wav"); 
										}
										bricks[n].getBrick()->setVisible(false);
										bricks[n].set_visibility(false);
										left = false;
										score +=10;
										char text[256];
										sprintf(text,"Score: %d", score);
										score_label->setString(text);
										if(score == 10*brick_index){
											new_game_button2->setVisible(true);
											option_button2->setVisible(true);
										}
										break;
									}
								}
							}
						}
						else{
							touched = false;
							lives--;
							if(lives == 0){
								new_game_button2->setVisible(true);
								option_button2->setVisible(true);
							}
							char text[256];
							sprintf(text,"Lives: %d", lives);
							lives_label->setString(text);
							ball->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2) );
						}
					}
					else{
						left = false;
					}

				}
				else if(down && !left){ //down and right
					if(ball->getPositionX() < maxX){
						if(ball->getPositionY() > minY){
							if(ball->boundingBox().intersectsRect(paddle->boundingBox())){
								if(sound){
									CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("laser_ship.wav"); 
								} 
								down = false;
							}
							else{
								ball->setPosition(ccp(ball->getPositionX() + 4, ball->getPositionY() - 4));
								for(int n = 0; n < brick_index; n++){
									if(ball->boundingBox().intersectsRect(bricks[n].getBrick()->boundingBox()) && bricks[n].get_visibility()){
										if(sound){
											CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explosion_small.wav"); 
										} 
										bricks[n].getBrick()->setVisible(false);
										bricks[n].set_visibility(false);
										left = true;
										score +=10;
										char text[256];
										sprintf(text,"Score: %d", score);
										score_label->setString(text);
										if(score == 10*brick_index){
											new_game_button2->setVisible(true);
											option_button2->setVisible(true);
										}
										break;
									}
								}
							}
						}
						else{
							touched = false;
							lives--;
							if(lives == 0){
								new_game_button2->setVisible(true);
								option_button2->setVisible(true);
							}
							char text[256];
							sprintf(text,"Lives: %d", lives);
							lives_label->setString(text);
							ball->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2) );
						}
					}
					else{
						left = true;
					}
				}
				else if(!down && left){ //up and left
					if(ball->getPositionX() > minX){
						if(ball->getPositionY() < maxY){
							ball->setPosition(ccp(ball->getPositionX() - 4, ball->getPositionY() + 4));
							for(int n = 0; n < brick_index; n++){
									if(ball->boundingBox().intersectsRect(bricks[n].getBrick()->boundingBox()) && bricks[n].get_visibility()){
										if(sound){
											CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explosion_small.wav"); 
										} 
										bricks[n].getBrick()->setVisible(false);
										bricks[n].set_visibility(false);
										down = true;
										score +=10;
										char text[256];
										sprintf(text,"Score: %d", score);
										score_label->setString(text);
										if(score == 10*brick_index){
											new_game_button2->setVisible(true);
											option_button2->setVisible(true);
										}
										break;
									}
								}
						}
						else{
							down = true;
						}
					}
					else{
						left = false;
					}
				}
				else if(!down && !left){ //up and right
					if(ball->getPositionX() < maxX){
						if(ball->getPositionY() < maxY){
							ball->setPosition(ccp(ball->getPositionX() + 4, ball->getPositionY() + 4));
							for(int n = 0; n < brick_index; n++){
									if(ball->boundingBox().intersectsRect(bricks[n].getBrick()->boundingBox()) && bricks[n].get_visibility()){
										if(sound){
											CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explosion_small.wav"); 
										}
										bricks[n].getBrick()->setVisible(false);
										bricks[n].set_visibility(false);
										down = true;
										score +=10;
										char text[256];
										sprintf(text,"Score: %d", score);
										score_label->setString(text);
										if(score == 10*brick_index){
											new_game_button2->setVisible(true);
											option_button2->setVisible(true);
										}
										break;
									}
								}
						}
						else{
							down = true;
						}
					}
					else{
						left = true;
					}
				}
			}
			else{
				this->unscheduleAllSelectors();
			}
		}
		else{
			this->unscheduleAllSelectors();
		}
	}
}



void Game::menuCloseCallback(CCObject* pSender)
{
#if (CC_ball_PLATFORM == CC_PLATFORM_WINRT) || (CC_ball_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_ball_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void Game::onEnter(){
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(Game::update),this,0,false);
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

}
void Game::onExit(){
	CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
}

bool Game::ccTouchBegan(CCTouch* touch, CCEvent* event){
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	 if (new_game_button2->boundingBox().containsPoint(location) && new_game_button2->isVisible())
	{
		CCScene *pScene = Game::scene();
		CCDirector::sharedDirector()->replaceScene(pScene);	
	}
	 else if (option_button2->boundingBox().containsPoint(location) && option_button2->isVisible())
	{
		CCScene *pScene2 = HelloWorld::scene();
		CCDirector::sharedDirector()->replaceScene(pScene2);
	}
	int v1 = rand() % 100;
	//random number to determine left or right direction for start of ball movement
	if(v1%2==0 && !touched){
		left = false;
	}
	touched = true;
	return true;
	
}
void Game::ccTouchMoved(CCTouch* touch, CCEvent* event){
	if(touch->getPreviousLocation().x > touch->getLocation().x){
		paddle->setPositionX(paddle->getPositionX() - (touch->getPreviousLocation().x - touch->getLocation().x));
	}
	else if(touch->getPreviousLocation().x < touch->getLocation().x){
		paddle->setPositionX(paddle->getPositionX() + (touch->getLocation().x - touch->getPreviousLocation().x));
	}
}
void Game::ccTouchEnded(CCTouch* touch, CCEvent* event){

}
void Game::touchDelegateRetain(){
	this->retain();
}
void Game::touchDelegateRelease(){
	this->release();
}
