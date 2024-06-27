#include "pch.h"
#include "Goblin.h"

Goblin::Goblin()
: Monster("°íºí¸°", 150, 20)
{

}

Goblin::~Goblin()
{
}

void Goblin::Attack(shared_ptr<Creature> other)
{
	if (this->IsDead()) return;
	this->Creature::PreAttack(other);
	other->TakeDamage(_atk);
}
