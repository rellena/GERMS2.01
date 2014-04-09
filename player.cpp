//player.cpp
//cpp file for the player

//Author: Richard Ellena

//This class will handle the main player. Only one istance of this class will
//be created into an object in the main and then all other copies will be
//referenced to it

//Add to this class if needed but player is pretty much done
#include "gameinclude.h"
extern Point mouse;
extern int enemy_size;

//player constructors
player::player()
:unit(), playerName("")
{}

player::player(float h, float a,float d,float s,float r,float e, string cn, string cc, string pn)
{
	//see unit decl, for const details
	unit(h,a,d,s,r,e,cn,cc);
	playerName = pn;
}

void player::playerDelete()
{
	deletePlayer();
}

//player member functions
void player::loadPlayerSprites(int x)
{
	playerSprite = new GLuint[x];
}

GLuint* player::getSprites()
{
	return playerSprite;
}
//player operators

void player::deletePlayer()
{
	delete playerSprite;
	delete playerDeath;
}

float player::damageDone(Enemy en)
{
	return (getPlayerDamage() - ( (getPlayerDamage())/en.getArmor() ));
}

void player::setPlayerDamage(float pDamage)
{
	this->setDamage(pDamage);

}

float player::getPlayerDamage()
{
	return this->getDamage();
}

void player::setStartPlayer(float hp, float arm, float dmg, float spd, float rng, float ener, string cN, float x, float y)
{
	this->setHealth(hp);
	this->setArmor(arm);
	this->setDamage(dmg);
	this->setSpeed(spd);
	this->setRange(rng);
	this->setEnergy(ener);
	this->setCharName(cN);
	this->setPosition(x,y);
}