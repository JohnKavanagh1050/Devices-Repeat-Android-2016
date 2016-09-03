#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameStates.h"
#include "GameScene.h"

class Meteor : public cocos2d::Sprite{
public:
	static Meteor * createMeteor(void);
	void initMeteor();
	void deleteMeteor(GameScene* world, int i);
	void updateMeteor(GameScene* world);
	bool getRemove();

	std::vector<Meteor*> getMeteor();

private:
	int timeAlive;
	int timecounter;
	short const TIMETOLIVE = 60;
	bool remove;

	short counter;
	const short SECOND = 60;

	std::vector<Meteor*> currentMeteors;
};