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


//void World::Job(int num)
//{
//	
//	if (PlayerType::KNIGHT == num)
//	{
//		cout << "(���)" << endl;
//	}
//	else if (PlayerType::ARCHER == num)
//
//
//}

void World::SelectPlayer(int num, string name, Creature** creature)
{
	switch (num)
	{
	case PlayerType::NONE:
	{
		cout << "�ٽ� �Է����ּ���." << endl;
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
		cout << "�ٽ� �Է����ּ���." << endl;
		break;
	}
	break;

	}
}

// ���� ������ 
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
	// �÷��̾� ���� �ʱ�ȭ?
	players.clear();

	// ù��° �÷��̾�� _player
	players.push_back(_player);
	//players.push_back(dynamic_cast<Player*>(_player));
	
	// 9�� �÷��̾� �߰�.
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
	
	cout << "�̸��� �Է����ּ���" << endl;
	cin >> name;
	cout << "1. Knight(���)\t2. Archer(�ü�)\t 3. Mage(������) �߿��� ��ȣ�� �Է����ּ���." << endl;
	cin >> playerNum;
	cumNum = rand() % 3 + 1; // 1 ~ 3
	SelectPlayer(playerNum, name, &_player);
	//MultyPlayers();
	//BossMonster();
	//SelectPlayer(playerNum, "computer", &_computer); // ����
	useMonster(static_cast<PlayerType>(cumNum), &_computer); // �ں����غ�
	// player�� �޴� ���� ���� �޶����� ���� ������ �� ���͸� ��µǰ���
	// ������ playerNum �ɹ������� �Էµ��� ����.
	// �׷��� static_cast<CharacterType>(cumNum)�� ����ĳ���� �����. �׷��� useMonster �Լ������޵�
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
		goblins[i] = new Goblin("����" + to_string(i + 1), 150, 0, 15);
	}
	
	
	for (int i = 0; i < numGoblins; ++i)
	{
		while (!goblins[i]->IsDead() && !_player->IsDead())
		{
			_player->Attack(goblins[i]);
			// ����ġ..
			if (goblins[i]->IsDead())
			{
				Player* player = dynamic_cast<Player*>(_player);
				if (player)
				{
					player->AddExp(10); // ������ óġ�� �� 10 ����ġ�� �߰�
					_accmulatedExp += 10;
					if (_accmulatedExp >= _maxExp)
					{
						_maxExp += 15;
						_accmulatedExp = 0;
					}
					cout << "������������������������������������������������������������������������������������������[����ġ�� ȹ���߽��ϴ�!]" << endl;
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
	// any_of ��?
	// first ���� last �� ���� ���ҵ鿡 ���� pred �� ���� �����ϴ� ���Ұ� �ϳ��� �ִٸ�, any_of�� ���� ����
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

	cout << "������������������������������������������������������ �� �� ������������������������������������������������������" << endl;
	cout << "1. ��ǻ�Ϳ� ����\t2. ���(����ġ)\t\t3. ����(����)\t4. ����" << endl;
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
		cout << "�߸� �Է��ϼ����� �ٽ� ������ �ּ���" << endl;
		return true;	
	}
	return true;


}

