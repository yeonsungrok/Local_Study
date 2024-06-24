#pragma once
class World
{
public:
	enum PlayerType
	{
		NONE = 0,
		KNIGHT = 1,
		ARCHER = 2,
		MAGE = 3
	};

	enum BattleType
	{
		COMPUTER = 1,
		GOBLIN = 2,
		HOBGOBLIN = 3
	};


	World();
	~World();
	// �������� : ���������, ������Կ����� �Ѵ�
	// ���������
	// World(const World& other);
	// ���� ���Կ�����
	// World& operator=(const World& other);

	void Init(); // �ʱ�ȭ
	
	bool End();
	void Battle1();
	void Battle2(); // ����
	void Battle3();
	bool SelectBattle();
	int battleNum = 0;
	void Players();


private:
	void Input();
	void SeletPlayer(int num, string name, Creature** creature);
	void MakeMonster(Monster** monster);
	void MakeBoss(Monster** boss);
	Creature* _player;
	Creature* _computer;

	Monster* _Goblin;
	Monster* _HobGoblin;
	//vector<Creature*> monster;

	vector<Creature*> _players;
	string PlayerName; // Players �Լ����� _players�� 9�� ����� �̸���
};

