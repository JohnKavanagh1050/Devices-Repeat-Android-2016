#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{

	if (!Layer::init())
	{
		return false;
	}
	m_gameState = GameStates::PlaceGunTower;

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
	this->addChild(menu);

	addBackGroundSprite(visibleSize, origin);

	createTowerBases(); 

	this->scheduleUpdate();
	

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

void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameScene::update(float dt)
{
	switch (m_gameState)
	{
	case GameStates::GameInit:
		showTower();        
		destroyBases();  
		addEvents();
		break;
	case GameStates::GameRunning:
		m_towerGun->update(dt);
		break;
	default:
		break;
	}
}

void GameScene::addEvents()
{
	//Create a "one by one" touch event listener (processes one touch at a time)
	auto listener1 = EventListenerTouchOneByOne::create();
	// When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
	listener1->setSwallowTouches(true);

	// Example of using a lambda expression to implement onTouchBegan event callback function
	listener1->onTouchBegan = [this](Touch* touch, Event* event){
		Vec2 pos = touch->getLocation();
		this->m_towerGun->m_fireRequest = true;
		this->m_towerGun->rotateTowerToPoint(pos);
		return true;
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener1, 30);
}

void GameScene::destroyBases()
{
	cocos2d::Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	this->removeChildByName(TOWERS_SPRITE_BATCH, true);
	m_towerBases.clear();
	m_towerBases.shrink_to_fit();
}

void GameScene::showTower()
{
	Vec2 loc(0, 0);
	for (int i = 0; i < m_towerBases.size(); i++)
	{
		if (m_towerBases.at(i)->isTouched())
		{
			loc = m_towerBases.at(i)->getPosition();
		}
	}
	m_towerGun = TowerGun::create(loc);
	this->addChild(m_towerGun);
	m_gameState = GameStates::GameRunning;
}

void GameScene::createTowerBases()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_textureAtlasImageFile);

	for (int i = 0; i < ptr->m_numberOfTowerBases; i++)
	{
		TowerBase * base = TowerBase::create(Vec2(ptr->m_towerBaseX[i], ptr->m_towerBaseY[i]), m_gameState);
		m_towerBases.push_back(base);
		spritebatch->addChild(base, 1);
	}
	this->addChild(spritebatch, 1, TOWERS_SPRITE_BATCH);
}

void GameScene::activatePauseScene(Ref *pSender)
{
	//auto scene = PauseMenu::createScene();
	auto scene = GameOver::createScene();
	Director::getInstance()->pushScene(scene);
}

void GameScene::activateGameOverScene(Ref *pSender)
{
	auto scene = GameOver::createScene();
	Director::getInstance()->replaceScene(scene);
}
