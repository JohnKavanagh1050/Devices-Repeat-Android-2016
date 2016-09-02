#include "Meteor.h"

USING_NS_CC;

Meteor * Meteor::createMeteor()
{
	Meteor * meteor = new Meteor();

	if (meteor && meteor->initWithFile("GameScreen/Meteor.png", Rect(0, 0, 67, 67)))
	{
		cocos2d::Size size(67, 67);
		auto meteorBody = PhysicsBody::createBox(size);
		meteorBody->setCollisionBitmask(0x000001);
		meteorBody->setContactTestBitmask(true);
		meteorBody->setTag(10);
		meteor->setPhysicsBody(meteorBody);
		meteor->initMeteor();
		meteor->setTag(10);

		return meteor;
	}
	CC_SAFE_DELETE(meteor);
	return NULL;
}


bool Meteor::getRemove(){
	return remove;
}

void Meteor::initMeteor(){
	timecounter = timeAlive = 0;
	remove = false;
}

void Meteor::updateMeteor()
{
	setPositionX(getPositionX() + 5);
	timecounter++;
	if (timecounter >= 1000){
		remove = true;
	}
}