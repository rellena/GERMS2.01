//enemy class cpp
#include "gameinclude.h"

//player constructors
Enemy::Enemy()
:unit(), enName("")
{}

Enemy::Enemy(float h, float a,float d,float s,float r,float e, string cn, string cc, string en)
{
	//see unit decl, for const details
	unit(h,a,d,s,r,e,cn,cc);
	enName = en;
}

float Enemy::getDetectRange()
{
	return detectrange;
}

void Enemy::setDetectRange(float range)
{
	detectrange = range;
}

float Enemy::damageDone(float arm)
{
	return (getEnemyDamage() - ( (getEnemyDamage())/arm ));
}

float Enemy::getEnemyDamage()
{
	return this->getDamage();
}

int Enemy::getDeathSpriteCount()
{
	return deathCount;
}

void Enemy::setDeathSpriteCount(int death)
{
	deathCount = death;
}

void Enemy::setStartDelay(float delay)
{
	startDelay = delay;
}

float Enemy::getStartDelay()
{
	return startDelay;
}