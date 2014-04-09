//sprites.cpp
//very simple, just an interface to store and load sprites
//need to include i file read and image reader into this class

//Author: Richard Ellena
#include "gameinclude.h"

//Sprites Constructors
sprites::sprites()
:pos_x(0.0), pos_y(0.0),
scale_x(1.0), scale_y(1.0)
{}

GLuint sprites::getSpriteTex()
{
	return spriteTexture;
}

//load image to opengl texture, filename is the name of the file e.x "Demo.bmp"
void sprites::loadTexture(const char* filename)
{
	spriteTexture = SOIL_load_OGL_texture
		(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_POWER_OF_TWO
		);
}

void sprites::drawSprites()
{
	sprites::drawSprites(sprites::pos_x, sprites::pos_y);
}

void sprites::drawSprites(GLfloat x, GLfloat y)
{
	sprites::drawMenuSprites(x, y, sprites::scale_x, sprites::scale_y);
}

void sprites::drawMenuSprites(GLfloat x, GLfloat y, GLfloat sx, GLfloat sy)
{
	//glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, sprites::spriteTexture);
	sprites::setSpritePos(x, y);
	sprites::setSpriteScale(sx, sy);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glTranslatef(sprites::pos_x, sprites::pos_y, 0.0);
		glScalef(sprites::scale_x, sprites::scale_y, 1.0);
		glBegin( GL_QUADS );
			glTexCoord2d(0.0,0.0); glVertex2d(0.0,0.0);
			glTexCoord2d(1.0,0.0); glVertex2d(1.0,0.0);
			glTexCoord2d(1.0,1.0); glVertex2d(1.0,1.0);
			glTexCoord2d(0.0,1.0); glVertex2d(0.0,1.0);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void sprites::setSpritePos(GLfloat x, GLfloat y)
{
	sprites::pos_x = x;
	sprites::pos_y = y;
}

void sprites::setSpriteScale(GLfloat x, GLfloat y)
{
	sprites::scale_x = x;
	sprites::scale_y = y;
}