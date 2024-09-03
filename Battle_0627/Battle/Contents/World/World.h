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
	void Input();
	bool SelectBattle();



private:
	/*void Job(int num);*/

	void SelectPlayer(int num, string name, Creature** creature);
	
	void useMonster(PlayerType num, Creature** creature); 

	void useBossMonster(HobGoblin** creture);
	void MultyPlayers(); //�ڸ��� // 10������ //Player* selected_Player

	void HealAll();

	int _maxExp;
	int _accmulatedExp;
	/*int _Job;*/


	Creature* _player;
	Creature* _computer;
	
	static const int numGoblins = 10; // ������
	Goblin* goblins[numGoblins]; // ���� ����Ʈ�迭

	vector<Creature*> players;

	HobGoblin* hobgoblin;
	


};

