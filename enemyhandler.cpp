//functions to handle enemy move
//and animations and attacks
#include "gameinclude.h"

//variables
Enemy *enemy;
bool *en_move;
int enemy_size;
extern int screenheight, screenwidth;
extern player mainPlayer;
Point *enmovepoint;
float *enangle;
int *enemy_animation_select, *en_attack_cool, *enemy_animation_max;
int *deathDelay;
bool *enattack;

clock_t start_clock;

extern level currentLevel;

extern bool follow;
extern int chase;
extern int currentWave;

GLuint *whiteBCDeathSprites;
GLuint *whiteBCSprites;
GLuint *neutroSprites;
GLuint *neutroDeathSprites;

int *deathSprite;
bool *isDead;
bool *enIsRemoved;

clock_t *en_start_cool, *en_end_cool;
//setup the enemies, very basic

void loadEnemySprites()
{
	whiteBCDeathSprites = new GLuint[11];
	whiteBCSprites = new GLuint[3];
	neutroSprites = new GLuint[10];
	neutroDeathSprites = new GLuint[9];
	
	neutroSprites[0] = SOIL_load_OGL_texture("Textures/Neutrofil.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroSprites[1] = SOIL_load_OGL_texture("Textures/Neutrofilattack1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroSprites[2] = SOIL_load_OGL_texture("Textures/Neutrofilattack2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroSprites[3] = SOIL_load_OGL_texture("Textures/Neutrofilattack3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroSprites[4] = SOIL_load_OGL_texture("Textures/Neutrofilattack4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroSprites[5] = SOIL_load_OGL_texture("Textures/Neutrofilattack5.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroSprites[6] = SOIL_load_OGL_texture("Textures/Neutrofilattack6.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroSprites[7] = SOIL_load_OGL_texture("Textures/Neutrofilattack7.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroSprites[8] = SOIL_load_OGL_texture("Textures/Neutrofilattack8.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroSprites[9] = SOIL_load_OGL_texture("Textures/Neutrofilattack9.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	neutroDeathSprites[0] = SOIL_load_OGL_texture("Textures/NeutroDeath/Neutrofildeath1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroDeathSprites[1] = SOIL_load_OGL_texture("Textures/NeutroDeath/Neutrofildeath2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroDeathSprites[2] = SOIL_load_OGL_texture("Textures/NeutroDeath/Neutrofildeath3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroDeathSprites[3] = SOIL_load_OGL_texture("Textures/NeutroDeath/Neutrofildeath4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroDeathSprites[4] = SOIL_load_OGL_texture("Textures/NeutroDeath/Neutrofildeath5.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroDeathSprites[5] = SOIL_load_OGL_texture("Textures/NeutroDeath/Neutrofildeath6.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroDeathSprites[6] = SOIL_load_OGL_texture("Textures/NeutroDeath/Neutrofildeath7.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroDeathSprites[7] = SOIL_load_OGL_texture("Textures/NeutroDeath/Neutrofildeath8.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	neutroDeathSprites[8] = SOIL_load_OGL_texture("Textures/NeutroDeath/Neutrofildeath9.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	whiteBCSprites[0] = SOIL_load_OGL_texture("Textures/WhiteBloodCellopen.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	whiteBCSprites[1] = SOIL_load_OGL_texture("Textures/WhiteBloodCellopen.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	whiteBCSprites[2] = SOIL_load_OGL_texture("Textures/WhiteBloodCellclosed.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	whiteBCDeathSprites[0] = SOIL_load_OGL_texture("Textures/WhiteBCDeath/WhiteBloodCelldeath1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	whiteBCDeathSprites[1] = SOIL_load_OGL_texture("Textures/WhiteBCDeath/WhiteBloodCelldeath2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	whiteBCDeathSprites[2] = SOIL_load_OGL_texture("Textures/WhiteBCDeath/WhiteBloodCelldeath3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	whiteBCDeathSprites[3] = SOIL_load_OGL_texture("Textures/WhiteBCDeath/WhiteBloodCelldeath4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	whiteBCDeathSprites[4] = SOIL_load_OGL_texture("Textures/WhiteBCDeath/WhiteBloodCelldeath5.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	whiteBCDeathSprites[5] = SOIL_load_OGL_texture("Textures/WhiteBCDeath/WhiteBloodCelldeath6.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	whiteBCDeathSprites[6] = SOIL_load_OGL_texture("Textures/WhiteBCDeath/WhiteBloodCelldeath7.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	whiteBCDeathSprites[7] = SOIL_load_OGL_texture("Textures/WhiteBCDeath/WhiteBloodCelldeath8.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	whiteBCDeathSprites[8] = SOIL_load_OGL_texture("Textures/WhiteBCDeath/WhiteBloodCelldeath9.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	whiteBCDeathSprites[9] = SOIL_load_OGL_texture("Textures/WhiteBCDeath/WhiteBloodCelldeath10.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	whiteBCDeathSprites[10] = SOIL_load_OGL_texture("Textures/WhiteBCDeath/WhiteBloodCelldeath11.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}

GLuint getCurrentSprite(int en, int x)
{
	if (isDead[en] == false)
	{
		if (enemy[en].getCharName().compare("WhiteBC") == 0)
			return whiteBCSprites[x];
		else if (enemy[en].getCharName().compare("Neutro") == 0)
			return neutroSprites[x];
	}
	else
	{
		if (enemy[en].getCharName().compare("WhiteBC") == 0)
			return whiteBCDeathSprites[x];
		else if (enemy[en].getCharName().compare("Neutro") == 0)
			return neutroDeathSprites[x];
	}
}

void enemyInit()
{
	for (int en = 0; en < enemy_size; en++)
	{
		if (enemy[en].getCharName().compare("WhiteBC") == 0)
		{
			enemy[en].setDeathSpriteCount(11);
			enemy_animation_max[en] = 3;
		}
		else if (enemy[en].getCharName().compare("Neutro") == 0)
		{
			enemy[en].setDeathSpriteCount(9);
			enemy_animation_max[en] = 10;
		}
	}
}

void initializeEnemies()
{
	enemy_size = currentLevel.getNumEnemies()[currentWave];
	enemy = new Enemy[enemy_size];
	en_move = new bool[enemy_size];
	enIsRemoved = new bool[enemy_size];

	enemy_animation_select = new int[enemy_size];
	enangle = new float[enemy_size];
	enattack = new bool[enemy_size];
	en_start_cool = new clock_t[enemy_size];
	en_end_cool = new clock_t[enemy_size];
	en_attack_cool = new int[enemy_size];
	enemy_animation_max = new int[enemy_size];
	deathSprite = new int[enemy_size];
	isDead = new bool[enemy_size];
	deathDelay = new int[enemy_size];

	for (int n=0; n<enemy_size;n++)
	{
		enangle[n] = 90;
		enemy_animation_select[n] = 0;
		enattack[n] = false;
		en_attack_cool[n] = 500;
		deathSprite[n] = 0;
		isDead[n] = false;
		deathDelay[n] = 150;
		enIsRemoved[n] = false;
	}

	enmovepoint = new Point[enemy_size];
}

//draw the hp bar of enemies
void drawHealth(float x, float y, float r, int num) {

	//grabs the max health and current health to calculate how long the bar should be
	float maxHealth = enemy[num].getMaxHealth();
	float currentHealth = enemy[num].getHealth();

	if (currentHealth < 0)
	{
		currentHealth = 0;
	}

	//variable to store decimal percentage ex) .8 = 80% of bar left
	float percent = (currentHealth/maxHealth);
	
	//set the x coordinates of the hp bar x1 is the x coordinate on the left and x2 is the x coordinate on the right
	float x1 = x - r;
	float x2 = x1+ (2*r*percent);

	glBegin(GL_QUADS);
		if (percent > .65)
		{
			glColor3f(0, 1, 0);
		}
		else if (percent <=.65 && percent > .30)
		{
			glColor3f(1, 1, 0);
		}
		else
		{
			glColor3f(1, 0, 0);
		}
		glVertex2f(x1, y-(r+1));
		glVertex2f(x2, y-(r+1));
		glVertex2f(x2, y-(r+5));
		glVertex2f(x1, y-(r+5));
	glEnd();
}
//set the enemys x, y, radius, enemy num is used
void setEnemy(float x, float y, float r, int en, float armor, float health, float damage, float range, float speed, string name)
{
	enemy[en].setPosition(x,y);
	enemy[en].setRadius(r);
	enemy[en].setArmor(armor);
	enemy[en].setHealth(health);
	enemy[en].setDamage(damage);
	enemy[en].setRange(range);
	enemy[en].setSpeed(speed);
	enemy[en].setCharName(name);
}

//used to draw enemy to screen
void drawEnemy(float x, float y, float r, int p)
{
	clock_t current;
	
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//enemys position
	x = (float)enemy[p].getPosition().x;
	y = (float)enemy[p].getPosition().y;
	r = (float)enemy[p].getRadius();

	//start drawing enemy
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	//for rotation
	if (en_move[p] == true && isDead[p] == false)
	{
		float PI = (float)3.14159265;
		float dy, dx;

		dy = (mainPlayer.getPosition().y - y);
		dx = (mainPlayer.getPosition().x - x);

		//find angle of rotation, if dx is 0 then you cant divide by 0 so set angle to 180
		if (dx == 0)
		{}
		else
			enangle[p] = atan(dy / dx) * 180/PI + 90;

		//if dx is negative then we have to compensate the angle to go left
		if (dx < 0)
			enangle[p] += 180;
	
	}

	//enemy texture
	if (isDead[p] == false)
		glBindTexture(GL_TEXTURE_2D, getCurrentSprite(p, enemy_animation_select[p]));
	else
	{
		if (enemy[p].getCharName().compare("Neutro") == 0)
			enangle[p] = 0;

		float pre, post;
		current = clock();

		pre = (float)((float)deathSprite[p] / (float)enemy[p].getDeathSpriteCount());
		post = (float)((float)(deathSprite[p] + 1) / (float)enemy[p].getDeathSpriteCount());

		if (current >= en_end_cool[p] && deathSprite[p] != enemy[p].getDeathSpriteCount() - 1)
		{
			deathSprite[p]++;
			en_end_cool[p] = clock() + deathDelay[p];
		}

		glBindTexture(GL_TEXTURE_2D,  getCurrentSprite(p, deathSprite[p]));
	}
			
	//translate the enemy to the origin
	glTranslatef((GLfloat)x,(GLfloat)y, (GLfloat)0.0f);
	//rotate enemy
	glRotatef(enangle[p],0,0,1);

	//draw enemy
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f((GLfloat)(-r), (GLfloat)(r));
	glTexCoord2f(1, 0); glVertex2f((GLfloat)(r), (GLfloat)(r));
	glTexCoord2f(1, 1); glVertex2f((GLfloat)(r), (GLfloat)(-r));
	glTexCoord2f(0, 1); glVertex2f((GLfloat)(-r), (GLfloat)(-r));
	glEnd();

	glDisable(GL_TEXTURE_2D);
	//reset the screen so only enemy rotated
	glPopMatrix();
	drawHealth(x, y, r, p);
	//flush the buffer
	glFlush();

	if (isDead[p] == true && deathSprite[p] == enemy[p].getDeathSpriteCount() - 1 && current >= en_end_cool[p])
		enIsRemoved[p] = true;
}

//enemy attacks
void enemyAttack(int x)
{
	mainPlayer.setHealth(mainPlayer.getHealth() - enemy[x].damageDone(mainPlayer.getArmor()));
}

void enemyMovement()
{
	//this function behaves virtually identically to the player move function
	//the difference is th for loop and not using the mouse to move but the player position
	//animations work the same
	clock_t current;
	for (int y =0; y<enemy_size; y++)
	{
		if (en_move[y] == true && isDead[y] == false)
		{
			if (enattack[y] == true && clock() >= en_end_cool[y])
			{
				enattack[y] = false;
				enemy_animation_select[y] = 0;
				//reset animation
			}
			//take a portion of clock time on cooldown to select animations basically 1 animation per 1/num animtions timeframe
			
			float pre, post;
			current = clock();

			pre = (float)((float)enemy_animation_select[y] / (float)enemy_animation_max[y]);
			post = (float)((float)(enemy_animation_select[y] + 1) / (float)enemy_animation_max[y]);

			if (current >= en_start_cool[y] + (en_attack_cool[y]*pre) && current < en_start_cool[y] + (en_attack_cool[y]*post) && enemy_animation_select[y] != enemy_animation_max[y] -1 && enattack[y] == true)
			{
				enemy_animation_select[y]++;
			}

			//if not attacking
			if (enattack[y] == false)
			{
				float distance = (float)pow(pow(enemy[y].getPosition().x - mainPlayer.getPosition().x, 2) + pow(enemy[y].getPosition().y - mainPlayer.getPosition().y, 2), 0.5);
				//if within range of player
				if (distance <= enemy[y].getRange())
				{
					//attack the player and start the cooldown clock
					cout<<"MP Health Before: "<<mainPlayer.getHealth()<<"\n";
					enemyAttack(y);
					en_start_cool[y] = clock();
					en_end_cool[y] = en_attack_cool[y] + en_start_cool[y];
					enattack[y] = true;
					cout<<"MP Health After: "<<mainPlayer.getHealth()<<"\n";
				}
			}

			if (isDead[y] == false)
				enemy[y].move(enmovepoint[y].x, enmovepoint[y].y);
		}
	}
}

void enemyMovementStart()
{
	clock_t current = clock();

	for (int x=0; x<enemy_size; x++)
	{
		if (en_move[x] == false && enemy[x].getStartDelay() + start_clock <= current && isDead[x] == false)
			en_move[x] = true;
	}
}

void enemyMovementSet()
{
	srand(time(NULL));
	int pos;

	for (int x=0; x<enemy_size; x++)
	{
		pos = rand() % 100;
		if (pos >= 50)
		{
			pos = rand() % screenheight;
			if (pos % 2 == 0)
				enemy[x].setPosition(-enemy[x].getRadius(), (float)pos);
			else
				enemy[x].setPosition(screenwidth + enemy[x].getRadius(), (float)pos);
		}
		else
		{
			pos = rand() % screenwidth;
			if (pos % 2 == 0)
				enemy[x].setPosition((float)pos, -enemy[x].getRadius());
			else
				enemy[x].setPosition((float)pos, screenheight + enemy[x].getRadius());
		}

		enmovepoint[x] = mainPlayer.getPosition();
		en_move[x] = false;
	}

	start_clock = clock();
}

bool checkDeath()
{
	bool allDead = true;
	for (int x=0; x<enemy_size; x++)
	{
		if(enemy[x].getHealth() <= 0 && isDead[x] == false)	//enemy died
		{//if hp start
			if (chase == x)
			{
				chase = -1;
				follow = false;
			}
			//get "rid" of a dead enemy
			isDead[x] = true;
			en_end_cool[x] = clock() + deathDelay[x] + 20;
			mainPlayer.setXP(mainPlayer.getXP() + enemy[x].getXP());
		}//if hp end
		if (enIsRemoved[x] == false)
			allDead = false;
	}
	return allDead;
}

//float x, float y, float r, int en, float armor, float health, float damage, float range, float speed, string name
void setEnemyData(string en)
{
	string line = ";";
	int n, count = 0;
	int ennum;
	float thex = 0;

	for (unsigned int x=0; x<en.length(); x=0)
	{
		n = en.find(";",x);
		line = en.substr(0,n);
		en.erase(0,n+1);

		switch(count)
		{
		case 0:
			ennum = atoi(line.c_str());
			break;
		case 1:
			thex = (float)atof(line.c_str());
			break;
		case 2:
			enemy[ennum].setPosition(thex, (float)atof(line.c_str()));
			break;
		case 3:
			enemy[ennum].setRadius((float)atof(line.c_str()));
			break;
		case 4:
			enemy[ennum].setArmor((float)atof(line.c_str()));
			break;
		case 5:
			enemy[ennum].setMaxHealth((float)atof(line.c_str()));
			enemy[ennum].setHealth(enemy[ennum].getMaxHealth());
			break;
		case 6:
			enemy[ennum].setDamage((float)atof(line.c_str()));
			break;
		case 7:
			enemy[ennum].setRange((float)atof(line.c_str()));
			break;
		case 8:
			enemy[ennum].setSpeed((float)atof(line.c_str()));
			break;
		case 9:
			enemy[ennum].setCharName(line);
			break;
		case 10:
			enemy[ennum].setStartDelay((float)atof(line.c_str()));
			break;
		case 11:
			enemy[ennum].setXP((float)atof(line.c_str()));
			break;
		default:
			break;
		}
		count++;
	}
}