#include "pch.h"
#include "Goblin.h"

Goblin::Goblin(string name, int hp, int mp, int atk)
: Monster(name, hp, mp, atk)
{
}

void Goblin::Attack(Creature* other)
{

	cout << _name << "��(��) " << other->GetName() << "��(��) �����մϴ�." << endl;
	other->TakeDamage(_atk);
}
