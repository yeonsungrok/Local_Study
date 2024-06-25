#include "pch.h"
#include "World_1.h"

World_1::World_1()
	: _player1(nullptr), _hobgoblin(nullptr)

{
	CreatePlayer();

	// player2 ����

	// ��� 10���� ����
	for (int i = 0; i < 10; ++i)
	{
		Creature* go = new Goblin("��� " + to_string(i+1), 150, 20);
		_Goblin.push_back(go);
		
	}

	_hobgoblin = new HobGoblin("�ں� ����", 8000, 100);
	
	
	_players.push_back(_player1);
	for (int i = 0; i < 9; ++i)
	{
		Creature* ply = new Archer("�� ��" + to_string(i+1), 600, 50);
		_players.push_back(ply);
	}

}

World_1::~World_1()
{
	// �÷��̾� 1
	delete _player1;

	// ���
	for (int i = 0; i < _Goblin.size(); i++)
	{
		delete _Goblin[i];
	}
	
	

	// ����
	delete _hobgoblin;

	// �÷��̾�� 1~10
	for (int i = 0; i < _players.size(); i++)
	{
		delete _players[i];
	}

}

void World_1::CreatePlayer()
{
	int input = 0;
	cin >> input;

	string name = "����";

	switch (input)
	{
	case 1:
		_player1 = new Knight(name, 5000, 30);
		break;
	case 2:
		_player1 = new Archer(name, 1000, 60);
		break;
	default:
		break;
	}

	


}

void World_1::Battle()
{
	
}

void World_1::Battle2()
{
	
	for(int i = 0; i <_Goblin.size(); ++i)
	{
		_player1->Attack(_Goblin[i]);
		_Goblin[i]->Attack(_player1);
	}

}

void World_1::Battle3()
{
	for (int i = 0; i < _players.size(); ++i)
	{
		_players[i]->Attack(_hobgoblin);

	}

}



bool World_1::GoblinsDead()
{
	for (int i = 0; i < _Goblin.size(); ++i)
	{
		// �̰��� ������ ������......
		if (!_Goblin[i]->IsDead())
		{
			return false;
		}
	}
	return true;
}

bool World_1::End()
{
	/*auto iter = find_if(_Goblin.begin(), _Goblin.end(), [](Creature* goblin)-> bool 
		{
			if (!goblin->IsDead())
				return true;
			return false;
		});*/

	// ��Ʋ2
	if(GoblinsDead())
		return true;
	if(_player1->IsDead())
		return true;
	return false;

	// ��Ʋ3..



}

