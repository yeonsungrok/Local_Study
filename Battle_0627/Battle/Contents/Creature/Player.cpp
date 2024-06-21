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


// 경험치 추가..
void Player::AddExp(int exp)
{
	_exp += exp;
	
	// 아래 누적된 경험치 추가
	cout << "경험치 " << exp << "(를)을 획득했습니다. 현재 경험치 : " << _exp << endl;
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
	cout << "레벨업! 현재 레벨: " << _level << endl;
	UpdateStats();
}

//int Player::GetExp() const
//{
//	return _exp;
//}

void Player::PrintExp() const
{
	cout << "──────────────────▶ 현재 레벨: " << _level <<", 현재 경험치:  " << _exp << ", 다음 레벨까지 남은 경험치: " << _nextLevelExp - _exp <<endl;
}

int Player::GetLevel() const
{
	return _level;
}

void Player::UpdateStats()
{
	_maxHp += 50 * _level; // 레벨당 HP 증가량
	_curHp = _maxHp; // 현재 HP를 최대 HP로 설정
	_Mp += 20 * _level; // 레벨당 MP 증가량
	_atk += 10 * _level; // 레벨당 공격력 증가량
	cout << "──────────────────▶ 스탯이 증가했습니다. HP: " << _maxHp << ", MP: " << _Mp << ", 공격력: " << _atk << endl;
}


