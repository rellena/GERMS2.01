#include "gameinclude.h"

Item::Item()
{
	itemName = "";
	buffs = new float[5];
	size = 5;
}

void Item::setBuffs(float* other, string* thebuffs, int size)
{
	buffs = new float[size];
	buffName = new string[size];
	for (int x=0; x<size; x++)
	{
		buffs[x] = other[x];
		buffName[x] = thebuffs[x];
	}

	delete thebuffs;
	delete other;
}

float* Item::getBuffs()
{
	return buffs;
}

string* Item::getBuffsName()
{
	return buffName;
}

void Item::setItemName(string name)
{
	itemName = name;
}

string Item::getItemName()
{
	return itemName;
}