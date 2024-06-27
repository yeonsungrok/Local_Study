#include "pch.h"
#include "HobGoblin.h"

HobGoblin::HobGoblin()
: Monster("Hop", 50000, 30), 
_aggroSystem(make_shared<AggroSystem>())
{
	
}

HobGoblin::~HobGoblin()
{
}

void HobGoblin::Attack_Hop()
{
	shared_ptr<vector<shared_ptr<Creature>>> players_for_attack = _aggroSystem->Pop(_attackRange);

	for (auto player : *players_for_attack)
	{
		player->TakeDamage(_atk, shared_from_this());
	}
}

void HobGoblin::TakeDamage(int amount, shared_ptr<Creature> attacker)
{
	//Creature::TakeDamage(amount, attacker);
	Monster::TakeDamage(amount, attacker);

	_aggroSystem->Push(attacker, amount);
}