#include "pch.h"
#include "Monster.h"

Monster::Monster(string name, int hp, int atk)
: Creature(name, hp, atk)
{
}

Monster::~Monster()
{
}

void Monster::Attack(shared_ptr<Creature> other)
{
	if (this->IsDead()) return;
	this->Creature::PreAttack(other);

	auto self_shared = shared_from_this();
	other->TakeDamage(_atk);
}
