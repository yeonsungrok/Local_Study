#pragma once
#include "Player.h"
class Mage : public Player
{
public:
	Mage(string name, int hp, int atk);
	virtual ~Mage();

	// Player��(��) ���� ��ӵ�
	virtual void Attack(Creature* other) override;
private:
};

