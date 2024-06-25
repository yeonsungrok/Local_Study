#include "pch.h"
#include "Mage.h"

Mage::Mage(string name, int hp, int atk)
: Player(name, hp, atk)
{
}

Mage::~Mage()
{
}

void Mage::Attack(Creature* other)
{
	if (this->IsDead()) return;
	this->Creature::PreAttack(other);
	other->TakeDamage(_atk);
	
}
