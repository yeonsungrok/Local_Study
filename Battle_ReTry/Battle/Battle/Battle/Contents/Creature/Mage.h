#pragma once
#include "Player.h"
class Mage : public Player
{
public:
	Mage(string name, int hp, int atk);
	virtual ~Mage();

	// Player��(��) ���� ��ӵ�
	virtual void Attack(shared_ptr<Creature> other) override;
private:
};

