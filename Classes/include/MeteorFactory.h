#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameStates.h"
#include "GameScene.h"
#include "Meteor.h"

class MeteorFactory : public cocos2d::Sprite{
public:
	void initMeteor();
	void deleteMeteor(GameScene* world, int i);
	void updateMeteorFactory(GameScene* world);
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