#include "gameinclude.h"

level currentLevel;
int currentWave;
extern Enemy *enemy;
extern int enemy_size;
extern player mainPlayer;
extern bool ingame;

bool isWaveDone;
extern bool start_cool_wave;

extern int screenheight, screenwidth;

void loadLevel(int lvl)
{
	currentWave = 0;
	switch (lvl)
	{
	case 0:
		currentLevel.loadTheLevel("Levels/Level1.grms");
		setLevelImages();
		break;
	}
	//setup player
	readPlayerData("Germs/Flu.grms");
	initPlayer();
	setPlayerSprites();

	startWave();
}

void setLevelImages()
{
	//load the map image
	currentLevel.loadMapImage();
	//load player sprite
}

void startWave()
{
	isWaveDone = false;
	initializeEnemies();
	for (int x=0; x<currentLevel.getNumEnemies()[currentWave]; x++)
	{
		setEnemyData(currentLevel.getEnemyData()[currentWave][x]);
	}

	enemyInit();
	enemyMovementSet();
	//load enemy sprites
	loadEnemySprites();
	start_cool_wave = false;
}

void endWave()
{
	currentWave++;
	isWaveDone = true;
}