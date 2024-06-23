#pragma once
class Creature
{
public:
	Creature(string name, int hp, int mp, int atk);
	virtual ~Creature();

	// 멤버함수 : 기능

	void Printinfo();



	void PreAttack(Creature* other);
	virtual void Attack(Creature* other) abstract; // 순수가상함수
	

	void TakeDamage(int amount);
	bool IsDead() { return _curHp <= 0; }

	//bool Rest() { return _curMp < 5; } // ★만들어봄

	string GetName() const { return _name; }
	void Heal();
	/*string GetJob() { return _job; }*/

	// aggro 전달
	int GetAggro() const { return _aggro; }
	void AddAggro(int amount) { _aggro += amount; }

protected: // 멤버변수: 속성
	string _name;
	int _curHp;
	int _maxHp;
	int _atk;
	int _Mp;
	int _aggro;
	
};

