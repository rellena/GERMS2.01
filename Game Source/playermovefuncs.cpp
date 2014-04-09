//functions to handle player movements animations and attacks
#include "gameinclude.h"

extern player mainPlayer;
extern bool _move;
extern Point mouse;
extern Enemy *enemy;
extern int enemy_size;
bool follow, attack_flag = false;
int chase;
int previous, attack_cooldown = 100;
extern bool wasclicked_RB;
float angle = 0;
extern int screenheight;

//variables for animation and attack cooldowns
clock_t start_cool_attack, end_cool_attack, current;
int player_animation_select, player_animation_max;

Point movepoint;
extern bool *col_move;

//initialize player - more to come, for now just animations
void setPlayerSprites()
{
	if (mainPlayer.getCharName().compare("Flu") == 0)
	{
		mainPlayer.loadPlayerSprites(6);
		mainPlayer.getSprites()[0] = SOIL_load_OGL_texture("Textures/Flu.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		mainPlayer.getSprites()[1] = SOIL_load_OGL_texture("Textures/Fluattack1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		mainPlayer.getSprites()[2] = SOIL_load_OGL_texture("Textures/Fluattack2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		mainPlayer.getSprites()[3] = SOIL_load_OGL_texture("Textures/Fluattack3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		mainPlayer.getSprites()[4] = SOIL_load_OGL_texture("Textures/Fluattack4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		mainPlayer.getSprites()[5] = SOIL_load_OGL_texture("Textures/Fluattack5.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	}
}

void initPlayer()
{
	if (mainPlayer.getCharName().compare("Flu") == 0)
	{
		player_animation_max = 6;
	}

	player_animation_select = 0;
	mainPlayer.setXP(0);
}

//attack for player
void attack(int en)
{
	enemy[en].setHealth(enemy[en].getHealth() - mainPlayer.damageDone(enemy[en]));
}

//movement function
void playerMovement () 
{
	if (_move == true)
	{
		//if right clicked in enemy, following enemy
		if (follow == true)
		{
			if (attack_flag == true && clock() >= end_cool_attack)
			{
				attack_flag = false;
				player_animation_select = 0;
				//reset animation
			}
			//take a portion of clock time on cooldown to select animations basically 1 animation per 1/num animtions timeframe
			
			float pre, post;
			current = clock();

			pre = (float)((float)player_animation_select / (float)player_animation_max);
			post = (float)((float)(player_animation_select + 1) / (float)player_animation_max);

			if (current >= start_cool_attack + (attack_cooldown*pre) && current < start_cool_attack + (attack_cooldown*post) && player_animation_select != player_animation_max  - 1 && attack_flag == true)
			{
					player_animation_select++;
			}
			
			mouse.x = enemy[chase].getPosition().x;
			mouse.y = enemy[chase].getPosition().y;

			//if not attacking
			if (attack_flag == false)
			{
				float distance = (float)pow(pow(enemy[chase].getPosition().x - mainPlayer.getPosition().x, 2) + pow(enemy[chase].getPosition().y - mainPlayer.getPosition().y, 2), 0.5);
				//if within range of enemy, rememebr we already checked if the enemy was clicked on
				if (distance <= mainPlayer.getRange())
				{
					//attack the enemy and start the cooldown clock
					cout<<enemy[chase].getHealth()<<cout<<"\n";
					attack(chase);
					start_cool_attack = clock();
					end_cool_attack = attack_cooldown + start_cool_attack;
					attack_flag = true;
					cout<<enemy[chase].getHealth()<<cout<<"\n";
				}
			}

			//stop following if enemy is dead
			if (enemy[chase].getHealth() <= 0 && follow == true)
			{
				follow = false;
				_move = false;
			}
		}

		if (follow == false)
			player_animation_select = 0;
		//move the player to its movepoint
		mainPlayer.move(movepoint.x, movepoint.y);
		
		//if you reach the mouse click, stop moving
		if (mainPlayer.getPosition().x == mouse.x && mainPlayer.getPosition().y == mouse.y)
				_move = false;
	}
}

void drawPlayer()
{
	int x, y, r;
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//get players position
	x = (int)mainPlayer.getPosition().x;
	y = (int)mainPlayer.getPosition().y;
	r = (int)mainPlayer.getRadius();

	//start drawing the player
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	//for rotation
	if (wasclicked_RB == true || follow == true)
	{
		float PI = (float)3.14159265;
		float dy, dx;

		if (follow == true)
		{
			dy = (enemy[chase].getPosition().y - y);
			dx = (enemy[chase].getPosition().x - x);
		}
		else
		{
			dy = (mouse.y - y);
			dx = (mouse.x - x);
		}

		//find angle of rotation, if dx is 0 then you cant divide by 0 so set angle to 180
		if (dx == 0)
		{}
		else
			angle = atan(dy / dx) * 180/PI + 90;

		//if dx is negative then we have to compensate the angle to go left
		if (dx < 0)
			angle += 180;
	
	}
	//draw the player texture
	glBindTexture(GL_TEXTURE_2D, mainPlayer.getSprites()[player_animation_select]);
	//translate the player to the origin
	glTranslatef((GLfloat)x,(GLfloat)y, (GLfloat)0.0f);
	//rotate player
	glRotatef(angle,0,0,1);

	//draw player
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f((GLfloat)(-r), (GLfloat)(r));
    glTexCoord2f(1, 0); glVertex2f((GLfloat)(r), (GLfloat)(r));
    glTexCoord2f(1, 1); glVertex2f((GLfloat)(r), (GLfloat)(-r));
    glTexCoord2f(0, 1); glVertex2f((GLfloat)(-r), (GLfloat)(-r));
	glEnd();

	glDisable(GL_TEXTURE_2D);
	//reset the screen so only player rotated
	glPopMatrix();
	//flush the buffer
	glFlush();
}

bool readPlayerData(string filename)
{
	ifstream fin;

	fin.open(filename.c_str());

	if (!fin.is_open())
		return false;
	
	else
	{
		int n = 0, count = 0, thex = 0;
		string line, play;

		getline(fin,play,'\n');
		fin.close();

		for (unsigned int x=0; x<play.length(); x = 0)
		{
			n = play.find(";",x);
			line = play.substr(0,n);
			play.erase(0,n+1);
		
			switch(count)
			{
			case 0:
				mainPlayer.setRadius((float)atof(line.c_str()));
				break;
			case 1:
				mainPlayer.setArmor((float)atof(line.c_str()));
				break;
			case 2:
				mainPlayer.setMaxHealth((float)atof(line.c_str()));
				mainPlayer.setHealth(mainPlayer.getMaxHealth());
				break;
			case 3:
				mainPlayer.setDamage((float)atof(line.c_str()));
				break;
			case 4:
				mainPlayer.setRange((float)atof(line.c_str()));
				break;
			case 5:
				mainPlayer.setSpeed((float)atof(line.c_str()));
				break;
			case 6:
				mainPlayer.setCharName(line);
				break;
			case 7:
				mainPlayer.setHpRegen((float)atof(line.c_str()));
				break;
			case 8:
				mainPlayer.setEnRegen((float)atof(line.c_str()));
				break;
			}
			count++;
		}

		return true;
	}
}