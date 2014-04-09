//collisons functions
//this class is integral to the game
#include "gameinclude.h"

extern Enemy *enemy;
extern int enemy_size;
extern bool *en_move;
extern player mainPlayer;
extern bool _move;
extern Point mouse;

extern Point movepoint, *enmovepoint;

extern bool *isDead;


//checks collisions for the player
bool checkCollidePlayer(int x)
{
	float distance = pow((float)(pow(mainPlayer.getPosition().x - enemy[x].getPosition().x, 2) + pow(mainPlayer.getPosition().y - enemy[x].getPosition().y, 2)), 0.5f);

	//basically, if the distance between the enemy and player is less than the length of their radius' added, then they collided
	if (distance - (mainPlayer.getRadius() + enemy[x].getRadius()) <= 0 && isDead[x] == false)
		return true;
	else
		return false;
}

//function that loops through every enemy to see check collisions
//returns an array of booleans telling if they collided
bool* checkCollisionsPlayer()
{
	bool *collide;

	collide = new bool[enemy_size];
	for (int x=0; x<enemy_size; x++)
		collide[x] = false;

	if (_move == true)
	{
		for (int x=0; x < enemy_size; x++)
		{
			if (isDead[x] == false)
				collide[x] = checkCollidePlayer(x);
			else
				collide[x] = false;
		}
	}

	return collide;
}

//same as for player, but this is for an enemy to enemy
bool checkCollideEnemy(int en, int x)
{
	float distance = pow((float)(pow(enemy[en].getPosition().x - enemy[x].getPosition().x, 2) + pow(enemy[en].getPosition().y - enemy[x].getPosition().y, 2)), 0.5f);

	if (distance - (enemy[en].getRadius() + enemy[x].getRadius()) <= 0 && isDead[x] == false)
		return true;
	else
		return false;
}

//checks collisions for enemies to other enemies/player
bool* checkCollisionsEnemy(int en)
{
	bool *collide;

	collide = new bool[enemy_size + 1];

	for (int x=0; x<enemy_size + 1; x++)
		collide[x] = false;

	if (en_move[en] == true && isDead[en] == false)
	{
		for (int x=0; x < enemy_size; x++)
		{
			if (x != en)
			{
				if (isDead[x] == false)
					collide[x] = checkCollideEnemy(en, x);
				else
					collide[x] = false;
			}
		}

		if (checkCollidePlayer(en) == true)
		{
			collide[enemy_size] = true;
		}

	}
	return collide;
}

//master collision function
//checks all of the collisions possible and sets the points that each
//unit on the map should move to
void Collisions()
{ 
	//variables
	float cx, cy, cr, tx, ty, tr, gox, goy, speed;
	bool *collide, *col_flag, moving;
	Point *P1;

	P1 = new Point[enemy_size + 1];
	col_flag = new bool[enemy_size + 1];

	for (int x=0; x<enemy_size + 1; x++)
		col_flag[x] = false;

	//loop through the enemy list
	//x = enemy_size then this is the collision check for the player
	for (int x=0; x<enemy_size + 1; x++)
	{
		bool death;
		//set all the variables used for checking collisons and
		//setting the points to move to
		if (x != enemy_size)
		{
			enmovepoint[x] = mainPlayer.getPosition();
			P1[x] = enemy[x].getPosition();
			tx = enemy[x].getPosition().x;
			ty = enemy[x].getPosition().y;
			tr = enemy[x].getRadius();
			gox = mainPlayer.getPosition().x;
			goy = mainPlayer.getPosition().y;
			speed = enemy[x].getSpeed();
			collide = checkCollisionsEnemy(x);
			moving = en_move[x];
			death = isDead[x];
		}
		else
		{
			movepoint = mouse;
			P1[x] = mainPlayer.getPosition();
			tx = mainPlayer.getPosition().x;
			ty = mainPlayer.getPosition().y;
			tr = mainPlayer.getRadius();
			gox = mouse.x;
			goy = mouse.y;
			speed = mainPlayer.getSpeed();
			collide = checkCollisionsPlayer();
			moving = _move;
			death = false;
		}

		if (death == false)
		{
		for (int y=0; y< enemy_size+1; y++)
		{	
			bool dead;

			if (y != enemy_size)
				dead = isDead[y];
			else
				dead = false;

			//if collided with unit[y] and the object is moving
			if (collide[y] == true && x != y && moving == true && dead == false)
			{
				col_flag[x] = true;
				//variables to check who this unit is colliding with
				if (y != enemy_size)
				{	
					cx = enemy[y].getPosition().x;
					cy = enemy[y].getPosition().y;
					cr = enemy[y].getRadius();
				}
				else
				{
					cx = mainPlayer.getPosition().x;
					cy = mainPlayer.getPosition().y;
					cr = mainPlayer.getRadius();
				}

				float distance;
				float xdis, ydis;

				//find the vector to move out of the unit that unit y collided wih
				distance = (float)(pow(pow(tx - cx,2) + pow(ty - cy, 2), 0.5));
				xdis = (((tx - cx)*(tr + cr)) / distance) - (tx - cx);
				ydis = (((ty - cy)*(tr + cr)) / distance) - (ty - cy);
				
				//add a vector that is moving in the direction of the current desitination of unit y
				distance = (float)(pow(pow(tx - gox,2) + pow(ty - goy, 2), 0.5));
				xdis += (speed*(gox - cx)) / distance;
				ydis += (speed*(goy - cy)) / distance;

				//set this move point into the enemy or player
				//this is done to check collisions after this unit when this unit is "placed" in
				//it's new position
				if (x != enemy_size)
				{
					enemy[x].setPosition(enemy[x].getPosition().x + xdis, enemy[x].getPosition().y + ydis);
				}
				else
				{
					mainPlayer.setPosition(mainPlayer.getPosition().x + xdis, mainPlayer.getPosition().y + ydis);
				}
			}
		}
		}
	}

	//revert all points of the units back
	//reset the points for the units to move tos
	for (int x = 0; x< enemy_size+1; x++)
	{
		if (col_flag[x] == true)
		{
			if (x != enemy_size)
			{
				enmovepoint[x] = enemy[x].getPosition();
				enemy[x].setPosition(P1[x].x,P1[x].y);
			}
			else
			{
				movepoint = mainPlayer.getPosition();
				mainPlayer.setPosition(P1[x].x,P1[x].y);
			}
		}
	}

	delete P1;
	delete col_flag;
}