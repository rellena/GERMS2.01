//map include for background, will change this class
//this class will end up being the include for a level before it starts
//will have its background and data for that level
//
#pragma once
#include <string>

using namespace std;

class level
{
public:
	level();
	void levelDelete();
	void drawMap();
	int loadMapImage();
	GLuint getMap();
	bool loadEnemyData();
	bool loadItemData();
	bool loadTheLevel(string);
	int getNumWaves();
	int* getNumEnemies();
	string** getEnemyData();

private:
	void deleteLevel();
	GLuint mapImage;
	int numWaves;
	string **enemyData, playerdata;
	int *numEnemies;
};

//load #waves
//load #of enemies per wave
//load enemy data, type, locations, stats
//load item data, locations, type
