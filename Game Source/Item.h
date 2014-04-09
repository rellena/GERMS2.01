#pragma once
#include <string>

using namespace std;

class Item 
{
public:
	Item();
	void setBuffs(float*, string*, int);
	float* getBuffs();
	string* getBuffsName();
	void setItemName(string);
	string getItemName();
private:
	float *buffs;
	string *buffName;
	string itemName;
	int size;
};