#include "pch.h"
#include "Mage.h"

Mage::Mage(string name, int hp, int atk)
: Player(name, hp, atk)
{
}

Mage::~Mage()
{
}

void Mage::Attack(shared_ptr<Creature> other)
{
	if (this->IsDead()) return;
	this->Creature::PreAttack(other);
	other->TakeDamage(_atk, shared_from_this());
	
}
