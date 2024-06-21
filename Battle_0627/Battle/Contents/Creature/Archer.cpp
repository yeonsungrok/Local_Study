#include "pch.h"
#include "Archer.h"

Archer::Archer(string name, int hp, int mp, int atk)
: Player(name, hp, mp, atk)
{
}

Archer::~Archer()
{
}

void Archer::Attack(Creature* other)
{
	// 30프로 확률
	// 0~100까지의 난수를 뽑고
	// 100으로 나눔
	this->Creature::PreAttack(other); // 멤버함수를 호출하기 위한 조건... 객체가 항상 있어야한다.
	int num = rand() % 100;			// 0~99 무작위 정수 생성해서 반환 num
	float ratio = num / (float)100;
	if (ratio < 0.3f)
	{
		cout <<"──────────────────────────▶크리티컬 데미지 3배!!" << endl;
		other->TakeDamage(_atk * 3.0f);
	}
	else
	{
		other->TakeDamage(_atk);
	}
}
