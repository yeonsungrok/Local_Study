#pragma once
#include "Monster.h"
class HobGoblin : public Monster
{
public:
	HobGoblin(string name, int hp, int atk);
	~HobGoblin();

	//void Attack_Hob();

	//vector<>
	void MultyAttack(Creature* creature, int amout);
	
	//Tabe..
	//vector<class AggroInfo> _aggroTable;
	
	//디자인 패턴...    컴포넌트.
	AggroSystem* _aggroSystem;
	int _attackRange = 4;
};

