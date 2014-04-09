#include "gameinclude.h"

extern Enemy *enemy;
extern Point *enmovepoint;
extern float *enangle;
extern int *enemy_animation_select, *en_attack_cool, *enemy_animation_max;
extern int *deathDelay;
extern bool *enattack;
extern GLuint *whiteBCDeathSprites;
extern GLuint *whiteBCSprites;
extern GLuint *neutroSprites;
extern GLuint *neutroDeathSprites;
extern int *deathSprite;
extern bool *isDead;
extern bool *enIsRemoved;
extern player mainPlayer;
extern level currentLevel;

void theDelete()
{
	//delete enemy;
	//delete enmovepoint;
	//delete enangle;
	//delete enemy_animation_select;
	//delete en_attack_cool;
	//delete enemy_animation_max;
	//delete deathDelay;
	//delete enattack;
	//delete whiteBCDeathSprites;
	//delete whiteBCSprites;
	//delete neutroSprites;
	//delete neutroDeathSprites;
	//delete deathSprite;
	//delete isDead;
	//delete enIsRemoved;
	//mainPlayer.playerDelete();
	currentLevel.levelDelete();

	exit(0);
}