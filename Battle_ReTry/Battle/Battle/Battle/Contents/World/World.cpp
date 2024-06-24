#include "pch.h"	
#include "World.h"

World::World()
: _player(nullptr)
, _computer(nullptr)
, _Goblin(nullptr)
, _HobGoblin(nullptr)
{
	
	Input();
	//Init();
}

World::~World()
{
	if(_player != nullptr)
		delete _player;
	if(_computer != nullptr)
		delete _computer;
	if (_Goblin != nullptr)
		delete _Goblin;
	if (_HobGoblin != nullptr)
		delete _HobGoblin;
}


void World::Init()
{
}

bool World::End()
{
	/*if (_player->IsDead() || (_computer && _computer->IsDead() || _Goblin->IsDead()))
	{
		return true;
	}
	return false;*/
	if (_player->IsDead() || _computer->IsDead())
		return true;

	return false;
}

bool World::SelectBattle()
{

	cout << "1 컴퓨터와 대결, 2 사냥, 3 유저10명 vs 보스 4 종료    선택을 입력해주세요." << endl;
	cin >> battleNum;
	

	switch (battleNum)
	{
	case COMPUTER:
	{
		Battle1();
	}
	break;
	case GOBLIN:
	{
		
		//*monster = new Goblin("고블린", 200, 15);
		Battle2();
	}
	break;
	case HOBGOBLIN:
	{
		Battle3();
	}
	break;
	case 4:
		return false;

	default:
	{
		cout << "다시 입력해주세요." << endl;
		return true;
	}
	return true;
	}
	
}

void World::Players()
{
	_players.clear();
	_players.push_back(_player);

	for (int i = 0; i < 9; ++i)
	{
		int ranUser = rand() % 3 + 1;
		PlayerName = "사용자 " + to_string(i + 2);
		
		Creature* _NewPlayer = nullptr;

		SeletPlayer(ranUser, PlayerName, &_NewPlayer);
		if (_NewPlayer)
			_players.push_back(dynamic_cast<Player*>(_NewPlayer));
	}

}


void World::SeletPlayer(int num, string name, Creature** creature)
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
		*creature = new Knight(name, 500, 15);
	}
	break;
	case PlayerType::ARCHER:
	{
		*creature = new Archer(name, 300, 35);
	}
	break;
	case PlayerType::MAGE:
	{
		*creature = new Mage(name, 220, 60);
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




void World::Input()
{
	
	int playerNum = 0;
	int cumNum = 0;
	string name;
	
	cout << "이름을 입력해주세요" << endl;
	cin >> name;
	cout << "<1 기사, 2 궁수, 3 마법사> 선택을 입력해주세요." << endl;
	cin >> playerNum;
	cumNum = rand() % 3 + 1; // 1 ~ 2
	SeletPlayer(playerNum, name, &_player);
	SeletPlayer(cumNum, "computer", &_computer);
	

}

void World::MakeMonster(Monster** monster)
{
	*monster = new Goblin("고블린", 200, 15);
}

void World::MakeBoss(Monster** boss)
{
	*boss = new HobGoblin("보스 : 홉고블린", 3000, 70);
}



void World::Battle1()
{
	_player->Attack(_computer);
	_computer->Attack(_player);
	
}



void World::Battle2()
{
	MakeMonster(&_Goblin);
	//_player->Attack(_Goblin);
	//_Goblin->Attack(_player);
	//

}

void World::Battle3()
{
	
	Players();
	MakeBoss(&_HobGoblin);
	
	for (auto player : _players)
	{
		if (!_HobGoblin->IsDead() && !player->IsDead())
		{
			player->Attack(_HobGoblin);
		}
		if (!_HobGoblin->IsDead())
		{
			/*_HobGoblin->*/
			//dynamic_cast<Player*>(_HobGoblin)->MultyAttack(_players)
		}
	}


	_players.

	while (!_HobGoblin->IsDead())
	{

	}


	


}
