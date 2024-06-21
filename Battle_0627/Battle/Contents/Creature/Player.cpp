#include "pch.h"
#include "Player.h"

Player::Player(string name, int hp, int mp, int atk)
// : Creature()
: Creature(name, hp, mp, atk)
, _exp(0)
, _level(1)
, _nextLevelExp(100)

{
}

Player::~Player()
{
}


// ����ġ �߰�..
void Player::AddExp(int exp)
{
	_exp += exp;
	
	// �Ʒ� ������ ����ġ �߰�
	cout << "����ġ " << exp << "(��)�� ȹ���߽��ϴ�. ���� ����ġ : " << _exp << endl;
	while (_exp >= _nextLevelExp)
	{
		_exp -= _nextLevelExp;
		LevelUp();
	}

}
void Player::LevelUp()
{
	_level++;
	_nextLevelExp += _level * 50;
	cout << "������! ���� ����: " << _level << endl;
	UpdateStats();
}

//int Player::GetExp() const
//{
//	return _exp;
//}

void Player::PrintExp() const
{
	cout << "�������������������������������������� ���� ����: " << _level <<", ���� ����ġ:  " << _exp << ", ���� �������� ���� ����ġ: " << _nextLevelExp - _exp <<endl;
}

int Player::GetLevel() const
{
	return _level;
}

void Player::UpdateStats()
{
	_maxHp += 50 * _level; // ������ HP ������
	_curHp = _maxHp; // ���� HP�� �ִ� HP�� ����
	_Mp += 20 * _level; // ������ MP ������
	_atk += 10 * _level; // ������ ���ݷ� ������
	cout << "�������������������������������������� ������ �����߽��ϴ�. HP: " << _maxHp << ", MP: " << _Mp << ", ���ݷ�: " << _atk << endl;
}


