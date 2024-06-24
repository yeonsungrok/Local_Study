#pragma once
#include "Monster.h"
class Goblin : public Monster
{
public:
	Goblin(string name, int hp, int atk);
	~Goblin();

	virtual void Attack(Creature* other) override;
};

