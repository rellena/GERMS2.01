//menu.cpp
//class with global function to draw menu
//Author: Hao Vo


#include "gameinclude.h"

extern Point mouseP;
extern bool wasclicked_LB, ingame;
extern int screenheight, screenwidth;
extern player mainPlayer;

bool inMainMenu = true, inExitMenu, inLoadMenu, inOptionMenu, inGameMenu, startNewGame;

menu::menu(): orgHeight(720), orgWidth(1280)
{}

void menu::menuInit()
{
	menuBackground.loadTexture("Textures/menuBackground.jpg");
	menuLogo.loadTexture("Textures/menuLogo.png");
	hudBack.loadTexture("Textures/hudBack.png");
}

void menu::drawMainMenu()
{

	//each char has height of around 20 pixel
	text newGame = text((const unsigned char*) "Newgame",(GLfloat)100,(GLfloat)350,(GLfloat)0.2,(GLfloat)0.2);
	text cont = text((const unsigned char*) "Continue",(GLfloat)100,(GLfloat)400,(GLfloat)0.2,(GLfloat)0.2);
	text opt = text((const unsigned char*) "Option",(GLfloat)100,(GLfloat)450,(GLfloat)0.2,(GLfloat)0.2);
	text ext = text((const unsigned char*) "Exit",(GLfloat)100,(GLfloat)620,(GLfloat)0.2,(GLfloat)0.2);


	glColor4f(1.0,1.0,1.0,1.0);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2.0);
	newGame.drawText();
	cont.drawText();
	opt.drawText();
	ext.drawText();

	if (isMouseInside(90,320,200,40,xOffset,yOffset))
	{
		newGame.drawTextBox(90,320,200,40);
		if (wasclicked_LB)
		{
			ingame = true;
			inMainMenu = false;
			startNewGame = true;
		}
	}
	
	if (isMouseInside(90,370,200,40,xOffset,yOffset))
		cont.drawTextBox(90,370,200,40);

	if (isMouseInside(90,420,200,40,xOffset,yOffset))
		opt.drawTextBox(90,420,200,40);

	if (isMouseInside(90,590,200,40,xOffset,yOffset))
	{
		ext.drawTextBox(90,590,200,40);
		if (wasclicked_LB)
			inExitMenu = true;
	}
}

void menu::drawLoadMenu()
{

}

void menu::drawExitMenu()
{
	text exitM = text((const unsigned char*) "EXIT GAME?",
		(GLfloat)orgWidth/2-100,(GLfloat)orgHeight/2-30,(GLfloat)0.2,(GLfloat)0.2);
	text yes = text((const unsigned char*) "YES",
		(GLfloat)orgWidth/2-150,(GLfloat)orgHeight/2+30,(GLfloat)0.2,(GLfloat)0.2);
	text no = text((const unsigned char*) "NO",
		(GLfloat)orgWidth/2+60,(GLfloat)orgHeight/2+30,(GLfloat)0.2,(GLfloat)0.2);


	//Draw text for Exit Menu
	glColor4f(1.0,1.0,1.0,1.0);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2.0);
	exitM.drawText();
	yes.drawText();
	no.drawText();

	//Exit Yes textbox
	if (isMouseInside(orgWidth/2-170,orgHeight/2,100,40,xOffset,yOffset))
	{
		yes.drawTextBox((GLfloat)orgWidth/2-170,(GLfloat)orgHeight/2,(GLfloat)100,(GLfloat)40);
		if (wasclicked_LB)
		{
			//theDelete();
			exit(0);
		}
	}

	// Exit No textbox
	if (isMouseInside(orgWidth/2+40,orgHeight/2,100,40,xOffset,yOffset))
	{
		no.drawTextBox((GLfloat)orgWidth/2+40,(GLfloat)orgHeight/2,(GLfloat)100,(GLfloat)40);
		if (wasclicked_LB)
			inExitMenu = false;
	}
	
}

void menu::drawInGameMenu()
{
	text resume = text((const unsigned char*) "Resume",(GLfloat)100,(GLfloat)250,(GLfloat)0.2,(GLfloat)0.2);
	text save = text((const unsigned char*) "Save",(GLfloat)100,(GLfloat)300,(GLfloat)0.2,(GLfloat)0.2);
	text load = text((const unsigned char*) "Load",(GLfloat)100,(GLfloat)350,(GLfloat)0.2,(GLfloat)0.2);
	text opt = text((const unsigned char*) "Option",(GLfloat)100,(GLfloat)400,(GLfloat)0.2,(GLfloat)0.2);
	text ext = text((const unsigned char*) "Exit",(GLfloat)100,(GLfloat)600,(GLfloat)0.2,(GLfloat)0.2);

	glColor4f(1.0,1.0,1.0,1.0);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2.0);
	resume.drawText();
	save.drawText();
	load.drawText();
	opt.drawText();
	ext.drawText();

	if (isMouseInside(90,220,200,40,xOffset,yOffset))
	{
		resume.drawTextBox(90,220,200,40);
		if (wasclicked_LB)
		{
			ingame = true;
			inGameMenu = false;
		}
	}
	
	if (isMouseInside(90,270,200,40,xOffset,yOffset))
	{
		save.drawTextBox(90,270,200,40);
	}
	
	if (isMouseInside(90,320,200,40,xOffset,yOffset))
	{
		load.drawTextBox(90,320,200,40);
	}
	
	if (isMouseInside(90,370,200,40,xOffset,yOffset))
	{
		opt.drawTextBox(90,370,200,40);
	}
	
	if (isMouseInside(90,570,200,40,xOffset,yOffset))
	{
		ext.drawTextBox(90,570,200,40);
		if (wasclicked_LB)
			inExitMenu = true;
	}
	
}

bool menu::isMouseInside(int x, int y, int w, int h, float xOffset, float yOffset)
{
	float xCoor = (float) x * xOffset;
	float yCoor = (float) y * yOffset;
	float xFarCoor = (float) (x+w) * xOffset;
	float yFarCoor = (float) (y+h) * yOffset;

	if ((xCoor < mouseP.x) && (mouseP.x < xFarCoor) 
			&& (yCoor < mouseP.y) && (mouseP.y < yFarCoor))
		return true;
	else
		return false;
}

void menu::drawMenu()
{
	xOffset = (float) screenwidth/orgWidth;
	yOffset = (float) screenheight/orgHeight;
	
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable( GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	glColor4f((GLfloat)0,(GLfloat)0,(GLfloat)0,(GLfloat)0.4);
	menuBackground.drawMenuSprites((GLfloat)0,(GLfloat)0, (GLfloat)screenwidth, (GLfloat)screenheight);
	glPushMatrix();
		glScalef(xOffset,yOffset,0);

		menuLogo.drawMenuSprites(300,10,700,200);

		if(inMainMenu)
		{
			if (inExitMenu)
				drawExitMenu();
			else
				drawMainMenu();

		}
		else if (inGameMenu)
		{
			if (inExitMenu)
				drawExitMenu();
			else
				drawInGameMenu();	
		}
	glPopMatrix();
	glFlush();

}

void menu::drawHUD()
{
	glColor4f((GLfloat)1,(GLfloat)1,(GLfloat)1,(GLfloat)0.3);
	hudBack.drawMenuSprites((GLfloat)0,(GLfloat)screenheight-100,(GLfloat) screenwidth,(GLfloat)100);
	
	text menu = text((const unsigned char*) "Menu",(GLfloat)screenwidth-110,(GLfloat)screenheight-35,(GLfloat)0.3,(GLfloat)0.3);
	menu.setTextBoxColor(0,0,0,1);
	menu.drawTextBox((GLfloat)screenwidth-120,(GLfloat)screenheight-80,(GLfloat)115,(GLfloat)60);
	glColor4f(1,1,1,1);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(3.0);
	menu.drawText();
	if (isMouseInside(screenwidth-120,screenheight-80,115,60,1,1))
	{
		menu.setTextBoxColor(1,1,1,1);
		menu.drawTextBox((GLfloat)screenwidth-120,(GLfloat)screenheight-80,(GLfloat)115,(GLfloat)60);
		glColor4f(0,0,0,1);
		menu.drawText();
		if(wasclicked_LB)
		{
			ingame = false;
			inGameMenu = true;
			drawMenu();
		}
	}
	
	float hpbar;
	hpbar = (mainPlayer.getHealth() / mainPlayer.getMaxHealth());
	hpbar = hpbar * 100;

	if (hpbar < 0)
		hpbar = 0;

	drawHpBar(hpbar);
	drawMpBar(100);

}

void menu::drawHpBar(float percent)
{
	glColor4f(1,1,1,1);
	text HP = text((const unsigned char*) "HP",(GLfloat)50,(GLfloat)screenheight-65,(GLfloat)0.2,(GLfloat)0.2); 
	glLineWidth(3.0);
	HP.drawText();

	glColor4f(1,0,0,1);
	drawRectBorder(100,screenheight-85,200,20,3);
	drawRectInside((GLfloat)100,(GLfloat)screenheight-85,(GLfloat)200,(GLfloat)20,percent);

}

void menu::drawMpBar(float percent)
{
	glColor4f(1,1,1,1);
	text MP = text((const unsigned char*) "MP",(GLfloat)50,(GLfloat)screenheight-25,(GLfloat)0.2,(GLfloat)0.2); 
	glLineWidth(3.0);
	MP.drawText();
	glColor4f(0,0,1,1);
	drawRectBorder(100,screenheight-45,200,20,3);
	drawRectInside((GLfloat)100,(GLfloat)screenheight-45,(GLfloat)200,(GLfloat)20,percent);
}

void menu::drawRectBorder(int x, int y, int w, int h, float size)
{
//	glDisable(GL_LINE_SMOOTH);
	glLineWidth(size);
	glBegin(GL_LINE_LOOP);
		glVertex2i(x,y);
		glVertex2i(x+w,y);
		glVertex2i(x+w,y+h);
		glVertex2i(x,y+h);
	glEnd();
}

void menu::drawRectInside(float x, float y, float w, float h, float percent)
{
	float onePer = w/100;
	glBegin( GL_QUADS );
		glVertex2f(x,y);
		glVertex2f(x+(onePer*percent),y);
		glVertex2f(x+(onePer*percent),y+h);
		glVertex2f(x,y+h);
	glEnd();
}