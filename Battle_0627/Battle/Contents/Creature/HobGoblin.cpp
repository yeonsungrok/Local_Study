#include "pch.h"
#include "HobGoblin.h"

HobGoblin::HobGoblin(string name, int hp, int mp, int atk)
: Monster(name, hp, mp, atk)
{
}


//void HobGoblin::MultyAttack(Creature* other)
//{
//	cout << _name << "��(��) " << other->GetName() << "��(��) �����մϴ�." << endl;
//	other->TakeDamage(_atk);
//
//}


void HobGoblin::MultyAttack(const vector<Creature*>& players)
{
	// ����ִ� �÷��̾�� ���͸�
	vector<Creature*> LivePlayers;
	for (auto player : players)
	{
		if (!player->IsDead())
		{
			LivePlayers.push_back(player);
		}
	}
	// �⺻���� sort (begin, end) 
	// ������ sort (begin, end, comp) �������� �� sort �Լ��� c�ڸ��� true or false�� ��Ÿ����.
	// comp �� ���� + �����Լ����

	// ��׷� ���� ������� ���� 
	sort(LivePlayers.begin(), LivePlayers.end(), [](Creature* a, Creature* b)
		{return a->GetAggro() > b->GetAggro(); });


	// ���� 4�� ����
	int AttackCount = min(4, static_cast<int>(LivePlayers.size()));
	for (int i = 0; i < AttackCount; ++i)
	{
		cout << _name << "�� ������ �������� Ÿ�ٴ�� ������������>>>>>>> " << LivePlayers[i]->GetName() << "�� �����մϴ�" << endl;
		LivePlayers[i]->TakeDamage(_atk);
	}

}