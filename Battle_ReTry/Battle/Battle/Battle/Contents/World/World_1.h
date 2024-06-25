#pragma once
class World_1
{
public:
	World_1();
	~World_1();

	void CreatePlayer();

	void Battle();
	void Battle2();

	bool GoblinsDead();

	bool End();

private:
	Creature* _player1;
	//const int multyplayer = 10;
	vector<Creature*> _Goblin;
};

