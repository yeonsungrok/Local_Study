#pragma once
class World_1
{
public:
	World_1();
	~World_1();

	void CreatePlayer();

	void Battle1();
	void Battle2();
	void Battle3();

	bool GoblinsDead();

	bool End();

private:
	shared_ptr <Creature> _player1;
	shared_ptr <Creature> _player2;

	vector<shared_ptr<Creature>> _Goblin;

	vector<shared_ptr<Creature>> _players;
	shared_ptr <Creature> _hobgoblin;

	//shared_ptr<Creature> _hobgoblin;
	//vector<shared_ptr<Creature>> _players;
	// dynamic_cast를 사용할땐 virtual function table이 필요하다. (가상함수테이블)
	// 값이 없을때는 nullptr을 뱉어낸다. 
};

