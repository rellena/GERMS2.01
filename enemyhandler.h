//Group of functions used to handle enemy motion/attack etc
#pragma once
#include <string>
using namespace std;

void initializeEnemies();
void setEnemy(float, float, float, int, float, float, float, float, float, string);
void drawHealth(float, float, float, int);
void drawEnemy(float, float, float, int);
void enemyMovement();
void enemyMovementStart();
bool checkDeath();
void loadEnemySprites();
void setEnemyData(string);
void enemyInit();
GLuint getCurrentSprite(int, int);
void enemyMovementSet();