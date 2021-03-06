#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto pauseItem = MenuItemImage::create("GameScreen/Pause_Button.png",
		"GameScreen/Pause_Button(Click).png", CC_CALLBACK_1(GameScene::activatePauseScene, this));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	pauseItem->setPosition(Point(pauseItem->getContentSize().width -
		(pauseItem->getContentSize().width / 10) + origin.x,
		visibleSize.height - pauseItem->getContentSize().height +
		(pauseItem->getContentSize().width / 10) + origin.y));

	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 6);

	//scrolling background
	bk1 = CCSprite::create("GameScreen/Background.png");
	bk1->setAnchorPoint(ccp(0, 0));
	bk1->setPosition(ccp(0, 0));

	bk2 = CCSprite::create("GameScreen/Background.png");
	bk2->setAnchorPoint(ccp(0, 0));
	bk2->setPosition(ccp(-bk1->boundingBox().size.width + 1, 0));

	this->addChild(bk1, 0);
	this->addChild(bk2, 0);

	player = Player::create();
	player->setPosition(Vec2(300, 100));
	this->addChild(player, 5);

	meteorFactory = MeteorFactory::createMeteorFactory();

	this->scheduleUpdate();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

void GameScene::addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin)
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();

	auto backgroundSprite = Sprite::create
		(ptr->m_backgroundTextureFile);
	backgroundSprite->setPosition(Point((visibleSize.width / 2) +
		origin.x, (visibleSize.height / 2) + origin.y));
	this->addChild(backgroundSprite, -1);
}

void GameScene::scrollBk()
{
	bk1->setPosition(ccp(bk1->getPosition().x + 1, bk1->getPosition().y));
	bk2->setPosition(ccp(bk2->getPosition().x + 1, bk2->getPosition().y));

	if (bk1->getPosition().x > bk1->boundingBox().size.width){
		bk1->setPosition(ccp(bk2->getPosition().x - bk2->boundingBox().size.width, bk1->getPosition().y));
	}
	if (bk2->getPosition().x > bk2->boundingBox().size.width){
		bk2->setPosition(ccp(bk1->getPosition().x - bk1->boundingBox().size.width, bk2->getPosition().y));
	}
}

void GameScene::update(float dt)
{
	player->update(this);
	meteorFactory->updateMeteorFactory(this);
	
	scrollBk();
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	//get location of my touch event for player movement
	float x = touch->getLocation().x - player->getPosition().x;
	float y = touch->getLocation().y - player->getPosition().y;
	float magnitude = sqrtf(powf(x, 2) + powf(y, 2));
	x /= magnitude;
	y /= magnitude;

	player->move(x, y);

	return true;
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
	player->idle();
}

void GameScene::activatePauseScene(Ref *pSender)
{
	auto scene = PauseMenu::createScene();
	//auto scene = GameOver::createScene();
	Director::getInstance()->pushScene(scene);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("GameMusic.wav");

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("bossHit.wav");
}

void GameScene::activateGameOverScene(Ref *pSender)
{
	auto scene = GameOver::createScene();
	Director::getInstance()->replaceScene(scene);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	return true;
}