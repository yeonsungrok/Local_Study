#pragma once
class Player : public Creature
{
public:
	Player(string name, int hp, int mp, int atk);
	virtual ~Player();

	void AddExp(int exp); // �ڻ��θ��� 6/16 exp ����ġ..���� �Լ�
	
	
	//int GetExp() const;
	
	
	void PrintExp() const; // ����ġ ��� �ż���
	void LevelUp(); // ���������� 
	int GetLevel() const; // ����ġ �ҷ����� �ż���



protected:
	int _exp;
	int _level;
	int _nextLevelExp;

	void UpdateStats();


};

