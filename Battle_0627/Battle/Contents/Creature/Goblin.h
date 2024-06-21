#pragma once
#include "Monster.h"  // 크리쳐에서 몬스터로 변환

class Goblin : public Monster
{
public:
	Goblin(string name, int hp, int mp, int atk);
	virtual ~Goblin() {};

	void Attack(Creature* other) override;  // Attack 함수 재정의..

};

