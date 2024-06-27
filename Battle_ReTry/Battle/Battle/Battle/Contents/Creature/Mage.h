#pragma once
#include "Player.h"
class Mage : public Player
{
public:
	Mage(string name, int hp, int atk);
	virtual ~Mage();

	// Player을(를) 통해 상속됨
	virtual void Attack(shared_ptr<Creature> other) override;
private:
};

