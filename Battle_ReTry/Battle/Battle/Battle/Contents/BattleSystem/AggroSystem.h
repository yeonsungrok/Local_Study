#pragma once

class Creature;
class AggroSystem
{
public:
	void Push(shared_ptr<Creature> attacker, int damage);
	shared_ptr<vector<shared_ptr<Creature>>> Pop(int count);

private:

	vector<class AggroInfo> _aggroTable;
};

