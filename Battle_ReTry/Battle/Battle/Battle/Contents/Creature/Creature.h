#pragma once
class Creature
{
public:
	Creature(string name, int hp, int atk);
	virtual ~Creature();

	// 멤버함수 : 기능
	void PrintInfo();
	void PreAttack(Creature* other);
	virtual void Attack(Creature* other) abstract; // 순수가상함수
	//virtual void TakeDamage(int amount, Creature* attacker = nullptr);
	void TakeDamage(int amount);
	
	bool IsDead() { return _curHp <= 0; }

	// 어그로 어떻게 할것인지 고민...

	//void AttackAmount(int amount);

protected: // 멤버변수: 속성
	string _name;
	int _curHp;
	int _maxHp;
	int _atk;
	
	//vector<int> _Aggro;
};

