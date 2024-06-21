#include "pch.h"
#include "Goblin.h"

Goblin::Goblin(string name, int hp, int mp, int atk)
: Monster(name, hp, mp, atk)
{
}

void Goblin::Attack(Creature* other)
{

	cout << _name << "이(가) " << other->GetName() << "을(를) 공격합니다." << endl;
	other->TakeDamage(_atk);
}
