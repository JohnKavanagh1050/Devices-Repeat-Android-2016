#include "Player.h"
USING_NS_CC;

Player * Player::create()
{
	Player * player = new Player();
	if (player && player->initWithFile("GameScreen/ninja.png", Rect(0, 0, 66, 99)))
	{
		//Create and run animation
		Vector<SpriteFrame*> animFrames(3);
		char str[100] = { 0 };
		for (int i = 0; i < 3; i++)
		{
			sprintf(str, "GameScreen/ninja.png");
			auto frame = SpriteFrame::create(str, Rect(66 * i, 99, 66, 99));
			animFrames.pushBack(frame);
		}
		auto animation = CCAnimation::createWithSpriteFrames(animFrames, 0.15f, 100000);
		auto animate = CCAnimate::create(animation);
		//make body for collisions
		cocos2d::Size size(66, 99);
		auto playerBody = PhysicsBody::createBox(size);
		playerBody->setCollisionBitmask(0x000002);
		playerBody->setContactTestBitmask(true);
		playerBody->setTag(20);
		player->setPhysicsBody(playerBody);

		player->runAction(animate);
		player->initPlayer();
		player->setTag(20);
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::move(float x, float y)
{
	dirX = x;
	dirY = y;
	moving = true;
}

float Player::getLives(){
	return lives;
}

float Player::setLives(){
	lives = 10;
	return lives;
}

void Player::deletePlayerBullet(GameScene* world, int i)
{
	world->removeChild(currentPlayerBullets[i]);
	currentPlayerBullets.erase(std::remove(currentPlayerBullets.begin(), currentPlayerBullets.end(), currentPlayerBullets[i]));
}

std::vector<Bullet*> Player::getBullets()
{
	return currentPlayerBullets;
}

void Player::update(GameScene* world)
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	for (int i = 0; i < currentPlayerBullets.size(); i++){
		if (currentPlayerBullets[i]->getRemove()){
			deletePlayerBullet(world, i);
		}
		else currentPlayerBullets[i]->updatePlayerBullet();
	}
	if (counter % (SECOND) == 0){
		Bullet *playerBullet = Bullet::createPlayerBullet();
		currentPlayerBullets.push_back(playerBullet);
		playerBullet->setPosition(getPosition().x, getPosition().y);
		world->addChild(playerBullet, 3);

		counter = 0;
	}

	if (moving) //check if moving
	{
		setPositionX(getPosition().x + dirX * speed);
		setPositionY(getPosition().y + dirY * speed);
	}

	setRotation(270);
	counter++;
}

void Player::loseLives(){
	lives--;
}

void Player::idle()
{
	moving = false;
}

void Player::initPlayer(){
	speed = 5.f;
	lives = 10;
	dirX = dirY = 0;
}
