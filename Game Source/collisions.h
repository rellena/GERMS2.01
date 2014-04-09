//Collisions.h
//Author: Richard Ellena
#pragma once
#include "Point.h"
#include "player.h"
#include "unit.h"
using namespace std;

//collision functions
bool checkCollidePlayer(int);
bool* checkCollisionsPlayer();
bool* checkCollisionsEnemy(int);
bool checkCollideEnemy(int, int);
void Collisions();