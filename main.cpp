//MAIN
//This main is very basic. Only prints a polygon to the screen.
//This was a test for opengl. Anyone feel free to edit this whole thing.
#include "gameinclude.h"

player mainPlayer;
extern bool ingame, wasclicked_LB, wasclicked_RB, wasclicked_MB, _move;
extern Point mouse;
extern Enemy *enemy;
extern int enemy_size;
menu Menu;
extern bool inMainMenu;

int screenwidth, screenheight;

extern bool startNewGame;

int main(int argc, char* argv[])
{
	getResolution();//set resolution to screen
	//set intial game variable
	ingame = false;
	startNewGame = false;

	//openGL HANDLES~~~~~~~~~~~~~~~~
	//initialize window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //disply mode with one buffer and colored
	glutInitWindowPosition(0, 0);//windoww position from upper left corner
	glutInitWindowSize(screenwidth,screenheight);//set size of viewing window
	
	glutCreateWindow("GERMS!");//create window
	//init menu
	Menu.menuInit();
	//funcs to adjust screen and scale to actual pixels of viewing window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//unsure what this does?
	gluOrtho2D(0.0f, screenwidth, 0, screenheight);//changes the view to the screen ~ IMPORTANT
	glScalef(1, -1, 1);//inverts the y axis
	glTranslatef((GLfloat)0, (GLfloat)-screenheight, (GLfloat)0);//changes the xy scale, in opengl, 0,0 is bottom left, this makes it upper left
	glMatrixMode(GL_MODELVIEW);
	glutFullScreen();

	glutMouseFunc(mouseButton);
	glutPassiveMotionFunc(mousePassive);
	glutKeyboardFunc(keypressed);//allows use of special keys such as arrow keys
	glutDisplayFunc(display);//calls display
	glutIdleFunc(display);//when glut is idle
	glutReshapeFunc(resize);//resize

	glutMainLoop();//start the glut loop

	return 0;
}
