#include "pch.h"
#include "HobGoblin.h"

HobGoblin::HobGoblin(string name, int hp, int mp, int atk)
: Monster(name, hp, mp, atk)
{
}


//void HobGoblin::MultyAttack(Creature* other)
//{
//	cout << _name << "이(가) " << other->GetName() << "을(를) 공격합니다." << endl;
//	other->TakeDamage(_atk);
//
//}


void HobGoblin::MultyAttack(const vector<Creature*>& players)
{
	// 살아있는 플레이어들 필터링
	vector<Creature*> LivePlayers;
	for (auto player : players)
	{
		if (!player->IsDead())
		{
			LivePlayers.push_back(player);
		}
	}
	// 기본형태 sort (begin, end) 
	// 비교형태 sort (begin, end, comp) 세가지가 들어간 sort 함수는 c자리에 true or false로 나타낸다.
	// comp 에 조건 + 람다함수사용

	// 어그로 높은 순서대로 정렬 
	sort(LivePlayers.begin(), LivePlayers.end(), [](Creature* a, Creature* b)
		{return a->GetAggro() > b->GetAggro(); });


	// 상위 4명 공격
	int AttackCount = min(4, static_cast<int>(LivePlayers.size()));
	for (int i = 0; i < AttackCount; ++i)
	{
		cout << _name << "가 데미지 순서별로 타겟대상 ──────>>>>>>> " << LivePlayers[i]->GetName() << "을 공격합니다" << endl;
		LivePlayers[i]->TakeDamage(_atk);
	}

}