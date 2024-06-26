#pragma once
class World_1
{
public:
	World_1();
	~World_1();

	void CreatePlayer();

	void Battle();
	void Battle2();
	void Battle3();

	bool GoblinsDead();

	bool End();

private:
	Creature* _player1;

	vector<Creature*> _Goblin;

	vector<Creature*> _players;
	Creature* _hobgoblin;

	shared_ptr<Creature> _hobgoblin;
	vector<shared_ptr<Creature>> _players;
	// dynamic_cast�� ����Ҷ� virtual function table�� �ʿ��ϴ�. (�����Լ����̺�)
	// ���� �������� nullptr�� ����. 
};

