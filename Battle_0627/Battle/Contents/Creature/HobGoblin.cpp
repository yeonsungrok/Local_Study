#include "pch.h"
#include "HobGoblin.h"

HobGoblin::HobGoblin(string name, int hp, int mp, int atk)
: Monster(name, hp, mp, atk)
{
}

void HobGoblin::MultyAttack(Creature* other)
{
	cout << _name << "��(��) " << other->GetName() << "��(��) �����մϴ�." << endl;
	other->TakeDamage(_atk);

}

