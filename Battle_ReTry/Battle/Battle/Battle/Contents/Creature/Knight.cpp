#include "pch.h"
#include "Knight.h"

Knight::Knight(string name, int hp, int atk)
: Player(name, hp, atk)
{
}

Knight::~Knight()
{
}

void Knight::Attack(shared_ptr<Creature> other)
{
	if (this->IsDead()) return;
	this->Creature::PreAttack(other);
	float ratio = (float)_curHp / (float)_maxHp;

	if (ratio < 0.5f)
	{
		// 현재 체력이 50프로 미만
		other->TakeDamage(_atk * 2, shared_from_this());
		
	}
	else
	{
		other->TakeDamage(_atk, shared_from_this());
		
	}
}
