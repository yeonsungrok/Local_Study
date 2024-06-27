#pragma once
#include "Monster.h"
class Goblin : public Monster
{
public:
	Goblin();
	~Goblin();

	virtual void Attack(shared_ptr<Creature> other) override;
};

