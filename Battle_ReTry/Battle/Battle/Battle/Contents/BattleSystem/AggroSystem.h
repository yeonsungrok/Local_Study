#pragma once
class AggroSystem
{
public:
	void Push(class Creature* attacker, int damage);
	vector<Creature*> Pop(int count);

private:

	vector<class AggroInfo> _aggroTable;
};

