#pragma once
#include "Monster.h"  // ũ���Ŀ��� ���ͷ� ��ȯ

class Goblin : public Monster
{
public:
	Goblin(string name, int hp, int mp, int atk);
	virtual ~Goblin() {};

	void Attack(Creature* other) override;  // Attack �Լ� ������..

};

