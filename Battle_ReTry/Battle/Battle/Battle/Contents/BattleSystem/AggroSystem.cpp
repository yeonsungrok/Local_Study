#include "pch.h"
#include "AggroSystem.h"

void AggroSystem::Push(shared_ptr<Creature> attacker, int damage)
{
	// ��� �� ���� �갡 table�� �̹� �����Ѵ�.
	auto iter = std::find_if(_aggroTable.begin(), _aggroTable.end(), [attacker](const AggroInfo info) ->bool
		{
			if (info.player == attacker)
				return true;
			return false;
		});

	// �̹� �ִ�.
	if (iter != _aggroTable.end())
	{
		iter->damageAmount += damage;
	}
	// ó�� ���ȴ�.
	else
	{
		AggroInfo info;
		info.player = attacker;
		info.damageAmount = damage;
		_aggroTable.push_back(info);
	}
}

shared_ptr<vector<shared_ptr<Creature>>> AggroSystem::Pop(int count)
{
	auto result = make_shared<vector<shared_ptr<Creature>>>(); //result;

	// ���� player _aggroTable���� ����
	auto removeIter = std::remove_if(_aggroTable.begin(), _aggroTable.end(), [](const AggroInfo& info)-> bool
		{
			if (info.player->IsDead())
				return true;
			return false;
		});

	_aggroTable.erase(removeIter, _aggroTable.end());

	// ����... ����
	std::sort(_aggroTable.begin(), _aggroTable.end(), [](const AggroInfo& infoA, const AggroInfo& infoB)-> bool
		{
			if (infoA.damageAmount > infoB.damageAmount)
				return true;
			return false;
		});
	//std::sort(_aggroTable.begin(), _aggroTable.end(), greater<AggroInfo>());

	if (_aggroTable.size() < count)
		count = _aggroTable.size();

	// ���� _aggroTable.size() >= count
	for (int i = 0; i < count; i++)
	{
		shared_ptr<Creature> attacker = _aggroTable[i].player;
		result->push_back(attacker);
	}

	return result;
}