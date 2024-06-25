#pragma once
class Creature
{
public:
	Creature(string name, int hp, int atk);
	virtual ~Creature();

	// ����Լ� : ���
	void PrintInfo();
	void PreAttack(Creature* other);
	virtual void Attack(Creature* other) abstract; // ���������Լ�
	//virtual void TakeDamage(int amount, Creature* attacker = nullptr);
	void TakeDamage(int amount);
	
	bool IsDead() { return _curHp <= 0; }

	// ��׷� ��� �Ұ����� ���...

	//void AttackAmount(int amount);

protected: // �������: �Ӽ�
	string _name;
	int _curHp;
	int _maxHp;
	int _atk;
	
	//vector<int> _Aggro;
};

