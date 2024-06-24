#pragma once
#include "Player.h"
class Mage : public Player
{
public:
	Mage(string name, int hp, int atk);
	virtual ~Mage();

	// Player을(를) 통해 상속됨
	virtual void Attack(Creature* other) override;
private:
};

