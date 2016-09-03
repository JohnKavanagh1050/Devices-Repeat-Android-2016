/*#include "MeteorFactory.h"

USING_NS_CC;

bool MeteorFactory::getRemove(){
	return remove;
}

void MeteorFactory::deleteMeteor(GameScene* world, int i)
{
	world->removeChild(currentMeteors[i]);
	currentMeteors.erase(std::remove(currentMeteors.begin(), currentMeteors.end(), currentMeteors[i]));
}

std::vector<Meteor*> MeteorFactory::getMeteor()
{
	return 	currentMeteors;
}

void MeteorFacotry::updateMeteorFactory(GameScene* world)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	for (int i = 0; i < currentMeteors.size(); i++){
		if (currentMeteors[i]->getRemove()){
			deleteMeteor(world, i);
		}
		else currentMeteors[i]->setPositionX(getPositionX() + 5);
	}

	if (counter % (SECOND) == 0){
		Meteor *meteor = createMeteor();
		currentMeteors.push_back(meteor);
		meteor->setPosition(0, 150);
		world->addChild(meteor, 5);

		counter = 0;
	}

	//setPositionX(getPositionX() + 5);
	timecounter++;
	if (timecounter >= 1000){
		remove = true;
	}
}*/