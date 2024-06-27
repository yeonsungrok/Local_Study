#pragma once

struct AggroInfo
{
	shared_ptr<Creature> player;
	int damageAmount;

	bool operator<(const AggroInfo& info) const // �Լ� �ڿ� ���� const
	{
		if (this->damageAmount < info.damageAmount)
			return true;
		return false;
	}

	bool operator>(const AggroInfo& info) const
	{
		if (this->damageAmount > info.damageAmount)
			return true;
		return false;
	}
};