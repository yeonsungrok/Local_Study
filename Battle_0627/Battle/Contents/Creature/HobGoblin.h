#pragma once
#include "Monster.h"
class HobGoblin : public Monster
{
public:
	HobGoblin(string name, int hp, int mp, int atk);
	virtual ~HobGoblin() {};


	//void MultyAttack(Creature* other);

	void MultyAttack(const vector<Creature*>& players); 
	// &�̿��ϴ������� ���纻�̾ƴ϶� ���� �����ϵ��� ���� �����ϱ� ����.
	// const�� �Լ��� ���޹��� players vector�� ������ �������� �ʰڴٴ� �ǹ�. 
};

