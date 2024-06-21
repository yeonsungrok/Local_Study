#include "pch.h"
#include "HobGoblin.h"

HobGoblin::HobGoblin(string name, int hp, int mp, int atk)
: Monster(name, hp, mp, atk)
{
}

void HobGoblin::MultyAttack(Creature* other)
{
	cout << _name << "이(가) " << other->GetName() << "을(를) 공격합니다." << endl;
	other->TakeDamage(_atk);

}

