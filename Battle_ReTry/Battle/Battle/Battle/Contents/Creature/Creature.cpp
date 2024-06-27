#include "pch.h"
#include "Creature.h"

Creature::Creature(string name, int hp, int atk)
: _name(name), _curHp(hp), _atk(atk), _maxHp(hp)
{
}

Creature::~Creature()
{
}

void Creature::Init()
{
	_curHp = _maxHp;
	isActive = true;
}

void Creature::PrintInfo()
{
	cout << "---- ���� ----" << endl;
	cout << "�̸� : " << _name << endl;
	cout << "HP : " << _curHp << endl;
	cout << "ATK : " << _atk << endl;
	
	cout << "---------------" << endl;

}

void Creature::PreAttack(shared_ptr<Creature> other)
{
	cout << _name << "�� " << other->_name << "���� ������ �õ��մϴ�." << endl;
}

void Creature::TakeDamage(int amount, shared_ptr<Creature> attacker)
{
	_curHp -= amount;

	if (attacker != nullptr && dynamic_cast <Monster*>(this) != nullptr)
	{
		shared_ptr<Player> p = dynamic_pointer_cast<Player>(attacker);
		if (p != nullptr && this->IsDead())
		{
			p->GainExp(_maxHp);
			p->LevelUp();
		}
	}

	if (_curHp < 0)
		_curHp = 0;

	PrintInfo();
}

//void Creature::Damage(Creature* attacker, int amount)
//{
//	//Player* pPlys = dynamic_cast<>();
//	//Attack(attacker);
//
//
//	amount += _dmg; //+= amount;
//	
//}
//

