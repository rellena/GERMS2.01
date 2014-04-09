//player.h

//this class is pretty done. 

//Author: Richard Ellena
#pragma once
#include "sprites.h"
#include <string>
#include "Enemy.h"

using namespace std;

class player : public unit
{
public:
	//constructors
	player();
	player(float,float,float,float,float,float,string,string,string);
	void playerDelete();
	void loadPlayerSprites(int);//stores sprite
	GLuint* getSprites();//returns sprite
	bool targetEnemyWithMouse(Enemy *enemyUnit, float x, float y);
	void setPlayerDamage(float pDamage);
	float getPlayerDamage();
	float damageDone(Enemy);
	void setStartPlayer(float, float, float, float, float, float, string, float, float);

private:
	void deletePlayer();
	GLuint *playerSprite;
	GLuint *playerDeath;
	string playerName;//name of player to be printed to screen for graphics
};
