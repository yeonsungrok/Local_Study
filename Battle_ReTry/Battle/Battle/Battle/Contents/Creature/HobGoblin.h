#pragma once
#include "Monster.h"
class HobGoblin : public Monster
{
public:
	HobGoblin();
	~HobGoblin();

	//void Attack_Hob();

	//vector<>
	void Attack_Hop();
	virtual void TakeDamage(int amount, shared_ptr<Creature> attacker) override;
	
	//Tabe..
	//vector<class AggroInfo> _aggroTable;
	
	//������ ����...    ������Ʈ.
	shared_ptr <AggroSystem> _aggroSystem;
	int _attackRange = 4;
};

