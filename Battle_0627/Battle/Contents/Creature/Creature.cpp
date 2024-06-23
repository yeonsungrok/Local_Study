#include "pch.h"
#include "Creature.h"

Creature::Creature(string name, int hp, int mp, int atk)
: _name(name), _curHp(hp), _atk(atk), _Mp(mp),_maxHp(hp),_aggro(0)
{
}

Creature::~Creature()
{
}

void Creature::Printinfo()
{
	cout << "---- 정보 ----" << endl;
	cout << "이름 : " <<_name << endl;
	cout << "HP : " << _curHp << endl;
	cout << "MP : " << _Mp << endl;
	cout << "ATK : " << _atk << endl;
	cout << endl;
}

void Creature::PreAttack(Creature* other)
{
	cout << _name << "이 " << other->_name << "에게 공격을 시도합니다." << endl;
}



void Creature::TakeDamage(int amount)
{
	_curHp -= amount;
	_aggro += amount; // 피해량 어그로 추가

	if (_curHp < 0)
		_curHp = 0;

	Printinfo();
}

void Creature::Heal()
{
	_curHp = _maxHp;
	_aggro = 0; // 회복할때 누적 어그로도 0 초기화
}
