//Enemy.h
//Header for class that handles enemies
#pragma once
#include "sprites.h"
#include <string>
#include "unit.h"
#include "lib/SOIL.h"

using namespace std;

class Enemy : public unit
{
public:
	//constructors
	Enemy();
	Enemy(float,float,float,float,float,float,string,string,string);
	float getDetectRange();
	void setDetectRange(float);
	float damageDone(float);
	float getEnemyDamage();
	int getDeathSpriteCount();
	void setDeathSpriteCount(int);
	void setStartDelay(float);
	float getStartDelay();

private:
	string enName;//name of player to be printed to screen for graphics
	float detectrange;
	float startDelay;
	int deathCount;
};