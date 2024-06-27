#pragma once
class Creature : public enable_shared_from_this<Creature>
{
public:
	Creature(string name, int hp, int atk);
	virtual ~Creature();

	void Init();

	void PrintInfo();

	//void PreAttack(Creature* other);

	void PreAttack(shared_ptr<Creature> other);

	//virtual void Attack(Creature* other) abstract; // 순수가상함수
	
	virtual void Attack(shared_ptr<Creature> other) abstract;


	virtual void TakeDamage(int amount, shared_ptr<Creature> attacker = nullptr);
	//void TakeDamage(int amount);
	
	bool IsDead() { return _curHp <= 0; }

	bool isActive = false;

	/*virtual void Damage(Creature* attacker, int amount);
	bool IsAttacker() { return _dmg; }*/

protected: // 멤버변수: 속성
	string _name;
	int _curHp;
	int _maxHp;
	int _atk;
	

};

