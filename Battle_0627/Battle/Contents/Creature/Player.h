#pragma once
class Player : public Creature
{
public:
	Player(string name, int hp, int mp, int atk);
	virtual ~Player();

	void AddExp(int exp); // ★새로만듬 6/16 exp 경험치..구성 함수
	
	
	//int GetExp() const;
	
	
	void PrintExp() const; // 경험치 출력 매서드
	void LevelUp(); // 레벨업관련 
	int GetLevel() const; // 경험치 불러오는 매서드



protected:
	int _exp;
	int _level;
	int _nextLevelExp;

	void UpdateStats();


};

