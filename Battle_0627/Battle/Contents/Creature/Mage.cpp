#include "pch.h"
#include "Mage.h"

Mage::Mage(string name, int hp, int mp, int atk)
: Player(name, hp, mp, atk)
{
}

Mage::~Mage()
{
}

void Mage::Attack(Creature* other)
{
	this->Creature::PreAttack(other);
	
	if (_Mp < 5)
	{
		cout << "������������������������������������������������������ ������ �����Ͽ� �޽��� �ʿ��մϴ�." << endl;
		_Mp = 50;
		return;
	}
	else
	{
		_Mp -= 5;
		other->TakeDamage(_atk);
	}



}

//void Mage::Rest()
//{
//	cout << "������������������������������������������������������ ������ �����Ͽ� �޽��� �ʿ��մϴ�." << endl;
//	_Mp = 50;
//}
