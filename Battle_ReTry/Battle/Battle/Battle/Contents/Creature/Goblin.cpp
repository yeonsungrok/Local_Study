#include "pch.h"
#include "Goblin.h"

Goblin::Goblin(string name, int hp, int atk)
: Monster(name, hp, atk)
{

}

Goblin::~Goblin()
{
}

void Goblin::Attack(Creature* other)
{
	if (this->IsDead()) return;
	this->Creature::PreAttack(other);
	other->TakeDamage(_atk);
}
