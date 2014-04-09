//all important gl functions including display
#include "gameinclude.h"

extern int screenwidth;
extern int screenheight;
extern player mainPlayer;
extern bool _move;
extern Point mouse;
extern Enemy *enemy;
extern bool *en_move;
extern int enemy_size;
extern sprites spr;
extern bool ingame;
extern menu Menu;
extern level currentLevel;
extern bool follow;
extern int chase;
extern bool isWaveDone;
extern int currentWave;
extern bool *enIsRemoved;

clock_t waveCooldownEnd;
bool start_cool_wave;
int waveCooldown = 10000;

extern bool startNewGame;

//resize the window
void resize(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//unsure what this does?
	gluOrtho2D(0.0f, screenwidth, 0, screenheight);//changes the view to the screen ~ IMPORTANT
	
	glScalef(1, -1, 1);//inverts the y axis
	glTranslatef(0, (GLfloat)-height, 0);//changes the xy scale, in opengl, 0,0 is bottom left, this makes it upper left
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
	
	screenwidth = width;
	screenheight = height;
}

void getResolution()
{
   RECT desktop;
   // Get a handle to the desktop window
   const HWND hDesktop = GetDesktopWindow();
   // Get the size of screen to the variable desktop
   GetWindowRect(hDesktop, &desktop);
   // The top left corner will have coordinates (0,0)
   // and the bottom right corner will have coordinates
   // (horizontal, vertical)
   screenwidth = desktop.right;
   screenheight = desktop.bottom;
}

void display(void)
{
	if (!ingame )
	{
		Menu.drawMenu();
	}
	else 
	{
		if (startNewGame == true)
		{
			mainPlayer.setPosition((float)screenwidth/2, (float)screenheight/2);
			loadLevel(0);
			startNewGame = false;
		}
		if (isWaveDone == true)
		{
			clock_t current  = clock();
			if (start_cool_wave == false)
			{
				waveCooldownEnd = clock() + waveCooldown;
				start_cool_wave = true;
				endWave();
			}

			if (currentLevel.getNumWaves() > currentWave && current >= waveCooldownEnd)
				startWave();
		}
		//movements handling
		enemyMovementStart();

		//check all collisions
		if (checkDeath() == true)
			isWaveDone = true;

		Collisions();

		//move enemies
		enemyMovement();
		//move player
		playerMovement();

		//glPushAttrib(GL_CURRENT_BIT);//keeps players color from changing
		glColor4f(1.0,1.0,1.0,1.0);
		//map drawing
		currentLevel.drawMap();

		//enemy drawing
		for (int p =0; p < enemy_size; p++)
		{
			if (enIsRemoved[p] == false)
				drawEnemy(enemy[p].getPosition().x, enemy[p].getPosition().y, enemy[p].getRadius(), p);
		}
		//player drawing
		drawPlayer();
		Menu.drawHUD();
		//glColor3f(0.0, 1.0, 0.0); 
	}

	glutSwapBuffers();//swap bufferes!!!! Important for animation
	glFlush();
	Sleep(8);
}