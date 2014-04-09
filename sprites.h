//sprites.h
//very simple, just an interface to store and load sprites
//need to include i file read and image reader into this class

//this needs a sprite array which will be an array of stored images

//author: Richard Ellena
#pragma once
using namespace std;

class sprites
{
public:
	//constructors
	sprites();
	GLuint getSpriteTex();	//return sprite texture
	void drawSprites();
	void drawSprites(GLfloat, GLfloat);	//draw sprite at position x, y
	void drawMenuSprites(GLfloat, GLfloat, GLfloat, GLfloat);	//position x, y; scale x, y
	void loadTexture(const char*);	//load an image to opengl texture
	void setSpritePos(GLfloat, GLfloat);	//set sprite position x, y
	void setSpriteScale(GLfloat, GLfloat);	//scale sprite x, y
private:

	GLuint spriteTexture;
	GLfloat pos_x, pos_y, scale_x, scale_y;
};
