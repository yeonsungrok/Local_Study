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
		cout << "──────────────────────────▶ 마나가 부족하여 휴식이 필요합니다." << endl;
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
//	cout << "──────────────────────────▶ 마나가 부족하여 휴식이 필요합니다." << endl;
//	_Mp = 50;
//}
