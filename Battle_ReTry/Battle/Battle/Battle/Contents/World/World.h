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
	// 깊은복사 : 복사생성자, 복사대입연산자 둘다
	// 복사생성자
	// World(const World& other);
	// 복사 대입연산자
	// World& operator=(const World& other);

	void Init(); // 초기화
	
	bool End();
	void Battle1();
	void Battle2(); // 과제
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
	string PlayerName; // Players 함수안의 _players들 9명 사용자 이름들
};

