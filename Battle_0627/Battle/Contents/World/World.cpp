#include "pch.h"	
#include "World.h"


World::World()
: _player(nullptr)
, _computer(nullptr)
, hobgoblin(nullptr)
{
	//Input();
	Init();
}

World::~World()
{
	//if(_player != nullptr)
		delete _player;
	//if(_computer != nullptr)
		delete _computer;
		
		delete hobgoblin;
}

void World::Init()
{
	Input();
}

bool World::End()
{
	if (_player->IsDead() || (_computer &&_computer->IsDead()))
	{
		return true;
	}
	return false;


}


void World::SelectPlayer(int num, string name, Creature** creature)
{
	switch (num)
	{
	case PlayerType::NONE:
	{
		cout << "다시 입력해주세요." << endl;
		break;
	}

	case PlayerType::KNIGHT:
	
	{
		*creature = new Knight(name, 500, 20, 15);
	}
	break;
	case PlayerType::ARCHER:
	{
		*creature = new Archer(name, 300, 25, 35);
	}
	break;
	case PlayerType::MAGE:
	{
		*creature = new Mage(name, 200, 50, 40);
	}
	break;

	default:
	{
		cout << "다시 입력해주세요." << endl;
		break;
	}
	break;

	}
}

// 몬스터 만들어보기 
void World::useMonster(PlayerType num, Creature** creature)
{
	if (num == ARCHER || num == KNIGHT || num == MAGE)
	{
		*creature = new Monster("computer", 500, 10, 20);
	}
	else 
	{
		*creature = nullptr;
	}
}

void World::useBossMonster(HobGoblin** creature)
{
	*creature = new HobGoblin("BOSS HOB_GOBLIN", 3500, 1000, 100);
}

void World::MultyPlayers()
{
	// 플레이어 벡터 초기화?
	players.clear();

	// 첫번째 플레이어는 _player
	players.push_back(_player);
	//players.push_back(dynamic_cast<Player*>(_player));
	
	// 9명 플레이어 추가.
	for (int i = 0; i < 9; ++i)
	{
		int randPlayer = rand() % 3 + 1;
		string playerName = "Player " + to_string(i + 2);
		
		Creature* newPlayer = nullptr;

		SelectPlayer(randPlayer, playerName, &newPlayer);
		if (newPlayer)
			players.push_back(dynamic_cast<Player*>(newPlayer));

	}
	

}


void World::HealAll()
{
	if (_player)
		_player->Heal();
	if (_computer)
		_computer->Heal();

}



void World::Input()
{
	int playerNum = 0;
	int cumNum = 0;
	string name;
	
	cout << "이름을 입력해주세요" << endl;
	cin >> name;
	cout << "1. Knight(기사)\t2. Archer(궁수)\t 3. Mage(마법사) 중에서 번호를 입력해주세요." << endl;
	cin >> playerNum;
	cumNum = rand() % 3 + 1; // 1 ~ 3
	SelectPlayer(playerNum, name, &_player);
	//MultyPlayers();
	//BossMonster();
	//SelectPlayer(playerNum, "computer", &_computer); // 보류
	useMonster(static_cast<PlayerType>(cumNum), &_computer); // ★변경해봄
	// player의 받는 값에 따라 달라진것 없이 동일한 한 몬스터만 출력되게함
	// 하지만 playerNum 맴버변수로 입력되지 않음.
	// 그래서 static_cast<CharacterType>(cumNum)를 정적캐스팅 사용함. 그래야 useMonster 함수에전달됨
}


void World::Battle1()
{
	while (!End())
	{
		_player->Attack(_computer);
		if (_computer && !_computer->IsDead())
		{
			_computer->Attack(_player);
		}
	}
	
	HealAll();
}

void World::Battle2()
{

	for (int i = 0; i < numGoblins; ++i) 
	{
		goblins[i] = new Goblin("고블린" + to_string(i + 1), 150, 0, 15);
	}
	
	
	for (int i = 0; i < numGoblins; ++i)
	{
		while (!goblins[i]->IsDead() && !_player->IsDead())
		{
			_player->Attack(goblins[i]);
			// 경험치..
			if (goblins[i]->IsDead())
			{
				Player* player = dynamic_cast<Player*>(_player);
				if (player)
				{
					player->AddExp(10); // 고블린을 처치할 때 10 경험치를 추가
					_accmulatedExp += 10;
					if (_accmulatedExp >= _maxExp)
					{
						_maxExp += 15;
						_accmulatedExp = 0;
					}
					cout << "─────────────────────────────────────────────[경험치를 획득했습니다!]" << endl;
					player->PrintExp();

				}
			}
			else
			{
				goblins[i]->Attack(_player);
			}
		}
		delete goblins[i];
		goblins[i] = nullptr;
	}

	HealAll();

}

void World::Battle3()
{
	/*MultyPlayers();

	while (!hobgoblin->IsDead()) {
		for (auto player : players) {
			if (!hobgoblin->IsDead() && !player->IsDead()) {
				player->Attack(hobgoblin);
				if (!hobgoblin->IsDead()) {
					hobgoblin->Attack(player);
				}
			}
		}
		hobgoblin->MultyAttack(players);
	}
	HealAll();*/

	MultyPlayers();

	useBossMonster(&hobgoblin);
	// any_of 란?
	// first 부터 last 전 까지 원소들에 대해 pred 가 참을 리턴하는 원소가 하나라도 있다면, any_of도 참을 리턴
	// 
	while (!hobgoblin->IsDead() && any_of(players.begin(), players.end(), [](Creature* player) {return !player->IsDead(); }))
	{
		for (auto player : players)
		{
			if (!hobgoblin->IsDead() && !player->IsDead())
			{
				player->Attack(hobgoblin);
			}
		}
		if (!hobgoblin->IsDead()) 
		{
			hobgoblin->MultyAttack(players);
		}
	}
	
	HealAll();
	//players.clear();
	

	/*useBossMonster(&hobgoblin);
	while (!hobgoblin->IsDead()) {
		for (auto player : players) {
			if (!hobgoblin->IsDead()) {
				player->Attack(hobgoblin);
			}
			if (!player->IsDead()) {
				hobgoblin->Attack(player);
			}
		}
	}
	HealAll();*/


	




}









bool World::SelectBattle()
{
	int selecNum = 0;

	cout << "─────────────────────────── 선 택 ───────────────────────────" << endl;
	cout << "1. 컴퓨터와 전투\t2. 사냥(경험치)\t\t3. 보스(고블린)\t4. 종료" << endl;
	cin >> selecNum;

	switch (selecNum)
	{
	case 1:
		Battle1();
		break;
	case 2:
		Battle2();
		break;
	case 3:
		Battle3();
		break;
	case 4:
		return false;

	default:
		cout << "잘못 입력하셨으니 다시 선택해 주세요" << endl;
		return true;	
	}
	return true;


}
