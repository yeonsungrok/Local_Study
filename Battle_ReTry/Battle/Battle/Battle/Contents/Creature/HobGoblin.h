#pragma once
#include "Monster.h"
class HobGoblin : public Monster
{
public:
	HobGoblin(string name, int hp, int atk);
	~HobGoblin();

	//void Attack_Hob();

	//vector<>
	void TakeDamage(int amount);
	
	//Tabe..
	//vector<class AggroInfo> _aggroTable;
	
};

