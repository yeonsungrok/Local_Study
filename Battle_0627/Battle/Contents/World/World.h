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
	void Input();
	bool SelectBattle();
	Player* GetPlayer() { return dynamic_cast<Player*>(_player); }


private:

	void SelectPlayer(int num, string name, Creature** creature);
	
	void useMonster(PlayerType num, Creature** creature); 

	void MultyPlayers(); //★만들어봄 // 10명유저 //Player* selected_Player

	void HealAll();
	

	int _maxExp;
	int _accmulatedExp;



	Creature* _player;
	Creature* _computer;
	
	static const int numGoblins = 10; // 고블린수
	Goblin* goblins[numGoblins]; // 고블린 포인트배열

	vector<Creature*> players;

	HobGoblin* hobgoblin;



};

