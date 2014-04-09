
#include "gameinclude.h"

level::level()
{}

extern int screenheight, screenwidth;

int level::loadMapImage()
{
	mapImage = SOIL_load_OGL_texture("Textures/NoseBackground.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    //if(playerSprite[0] == 0) return false;
   // glBindTexture(GL_TEXTURE_2D, playerSprite[0]);
   // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    return true;
}

GLuint level::getMap()
{
	return mapImage;
}

void level::drawMap()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();                           
    glTranslatef(0.0f,0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, getMap());
	glBegin(GL_QUADS);
	glTexCoord2f((GLfloat)0, (GLfloat)0); glVertex2f((GLfloat)0, (GLfloat)0);
	glTexCoord2f((GLfloat)0, (GLfloat)1); glVertex2f((GLfloat)0, (GLfloat)screenheight);
	glTexCoord2f((GLfloat)1, (GLfloat)1); glVertex2f((GLfloat)screenwidth, (GLfloat)screenheight);
    glTexCoord2f((GLfloat)1, (GLfloat)0); glVertex2f((GLfloat)screenwidth, (GLfloat)0);
    
    
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glFlush();
}

//load #waves
//load #of enemies per wave
//load enemy data, type, locations, stats
//load item data, locations, type
//int numWaves;
//string **enemyData;
//int *numEnemies;
bool level::loadTheLevel(string filename)
{
	ifstream fin;
	string line;

	fin.open(filename.c_str());

	if (!fin.is_open())
		return false;
	else
	{
		getline(fin,line,'\n');
		getline(fin,line,'\n');
		numWaves = atoi(line.c_str());

		numEnemies = new int[numWaves];

		for (int x=0; x<numWaves; x++)
		{
			getline(fin,line,';');
			numEnemies[x] = atoi(line.c_str());
		}

		getline(fin,line,'\n');

		enemyData = new string*[numWaves];
		for(int x=0; x<numWaves; x++)
		{
			enemyData[x] = new string[numEnemies[x]];
		}

		for (int x=0; x<numWaves; x++)
		{
			for (int y=0; y<numEnemies[x]; y++)
			{
				getline(fin,line,'\n');
				enemyData[x][y] = line;
			}
		}

		fin.close();
		return true;
	}
}

int level::getNumWaves()
{
	return numWaves;
}

int* level::getNumEnemies()
{
	return numEnemies;
}

string** level::getEnemyData()
{
	return enemyData;
}

void level::levelDelete()
{
	deleteLevel();
}

void level::deleteLevel()
{
	for (int x=0; x<numWaves; x++)
	{
		delete enemyData[x];
	}
	
	delete enemyData;
	delete numEnemies;
}