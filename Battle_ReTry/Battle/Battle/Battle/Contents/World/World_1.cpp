#include "pch.h"
#include "World_1.h"

World_1::World_1()
	: _player1(nullptr), _player2(nullptr), _hobgoblin(nullptr)

{
	CreatePlayer();

	// player2 생성
	_player2 = make_shared<Knight>("player2", 100, 5);


	// 고블린 10마리 생성

	

	for (int i = 0; i < 10; ++i)
	{

		auto go = make_shared<Goblin>("고블린 " + to_string(i+1), 150, 20);
		_Goblin.push_back(go);
		
	}





}

World_1::~World_1()
{
	/*delete _player1;
	delete _player2;*/
	


	// 고블린
	//for (int i = 0; i < _Goblin.size(); i++)
	//{
	//	delete _Goblin[i];
	//}
	//
	

	// 보스
	




}

void World_1::CreatePlayer()
{
	int input = 0;
	cin >> input;

	string name = "성롹";

	switch (input)
	{
	case 1:
		_player1 = make_shared<Knight>(name, 5000, 30);
		break;
	case 2:
		_player1 = make_shared<Archer>(name, 1000, 60);
		break;
	default:
		break;
	}

	


}

void World_1::Battle1()
{
	_player1->Attack(_player2);
	_player2->Attack(_player1);
}

void World_1::Battle2()
{
	
	/*for(int i = 0; i <_Goblin.size(); ++i)
	{
		_player1->Attack(_Goblin[i]);
		_Goblin[i]->Attack(_player1);
	}*/

	for (auto& goblin : _Goblin) {
		_player1->Attack(goblin);
		goblin->Attack(_player1);
	}



}

void World_1::Battle3()
{
	/*for (auto _players : )
	{
		_players[i]->Attack(_hobgoblin);

	}*/

}



bool World_1::GoblinsDead()
{
	//for (int i = 0; i < _Goblin.size(); ++i)
	//{
	//	// 이곳에 무엇을 넣을까......
	//	if (!_Goblin[i]->IsDead())
	//	{
	//		return false;
	//	}
	//}
	//return true;
	for (const auto& goblin : _Goblin) {
		if (!goblin->IsDead()) {
			return false;
		}
	}
	return true;



}

bool World_1::End()
{
	auto iter = find_if(_Goblin.begin(), _Goblin.end(), [](const shared_ptr<Creature>& goblin)-> bool
		{
			if (!goblin->IsDead())
				return true;
			return false;
		});

	// 배틀2
	if(GoblinsDead())
		return true;
	if(_player1->IsDead())
		return true;
	return false;

	// 배틀3..



}

