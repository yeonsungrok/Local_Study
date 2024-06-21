#include "pch.h"
#include "Knight.h"

Knight::Knight(string name, int hp, int mp, int atk)
: Player(name, hp, mp, atk)
{
}

Knight::~Knight()
{
}

void Knight::Attack(Creature* other)
{
	this->Creature::PreAttack(other);
	float ratio = (float)_curHp / (float)_maxHp;

	if (ratio < 0.5f)
	{
		cout << "������������������������������������������������������ ü��50%�̸� ������ 2��!!" << endl;
		// ���� ü���� 50���� �̸�
		other->TakeDamage(_atk * 2);
	}
	else
	{
		other->TakeDamage(_atk);
	}
}
