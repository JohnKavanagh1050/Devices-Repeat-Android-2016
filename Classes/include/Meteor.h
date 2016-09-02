#pragma once

#include "cocos2d.h"
#include "GameData.h"
#include "GameStates.h"

class Meteor : public cocos2d::Sprite{
public:
	static Meteor * createMeteor(void);
	void initMeteor();
	void updateMeteor();
	bool getRemove();

private:
	int timeAlive;
	int timecounter;
	short const TIMETOLIVE = 60;
	bool remove;
};