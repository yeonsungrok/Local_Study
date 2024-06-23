#pragma once
#include "Monster.h"
class HobGoblin : public Monster
{
public:
	HobGoblin(string name, int hp, int mp, int atk);
	virtual ~HobGoblin() {};


	//void MultyAttack(Creature* other);

	void MultyAttack(const vector<Creature*>& players); 
	// &이용하는이유는 복사본이아니라 원본 수정하도록 접근 가능하기 때문.
	// const는 함수가 전달받은 players vector의 내용을 변경하지 않겠다는 의미. 
};

