#include "pch.h"
#include "Creature.h"

Creature::Creature(string name, int hp, int mp, int atk)
: _name(name), _curHp(hp), _atk(atk), _Mp(mp), _maxHp(hp), _aggro(0)

{
}

Creature::~Creature()
{
}
void Creature::Printinfo()
{
	/*string JobString;
	switch (job)
	{
	case 1:
		JobString = "(���)";
		break;
	case 2:
		JobString = "(�ü�)";
		break;
	case 3:
		JobString = "(������)";
		break;
	default:
		JobString = "(����)";
		break;
	}*/

	cout << "---- ���� ----" << endl;
	cout << "�̸� : " << _name << endl;
	cout << "HP : " << _curHp << endl;
	cout << "MP : " << _Mp << endl;
	cout << "ATK : " << _atk << endl;
	cout << endl;
}

void Creature::PreAttack(Creature* other)
{
	cout << _name << "�� " << other->_name << "���� ������ �õ��մϴ�." << endl;
}



void Creature::TakeDamage(int amount)
{
	_curHp -= amount;
	//_aggro += amount; // ���ط� ��׷� �߰�

	if (_curHp < 0)
		_curHp = 0;

	Printinfo();
}

void Creature::Heal()
{
	_curHp = _maxHp;
	_aggro = 0; // ȸ���Ҷ� ���� ��׷ε� 0 �ʱ�ȭ
}
