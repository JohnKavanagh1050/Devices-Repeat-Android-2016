#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include "GameData.h"
#include "GameStates.h"
#include "TowerBase.h"
#include "TowerGun.h"

#include <string>

class GameScene : public cocos2d::Layer
{
private:
	GameStates m_gameState;
	std::vector<TowerBase *> m_towerBases;
	std::string const TOWERS_SPRITE_BATCH = "TowerBases";
	TowerGun * m_towerGun;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void addBackGroundSprite(cocos2d::Size const & visibleSize, cocos2d::Point const & origin);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	// Called when user pauses gameplay.
	void activatePauseScene(Ref *pSender);
	// Called at game over 
	void activateGameOverScene(Ref *pSender);
	void addEvents();
	void createTowerBases();
	void update(float dt);
	void destroyBases();
	void showTower();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
