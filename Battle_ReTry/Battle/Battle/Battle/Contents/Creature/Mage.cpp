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
	this->Creature::PreAttack(other);
	other->TakeDamage(_atk);
}
