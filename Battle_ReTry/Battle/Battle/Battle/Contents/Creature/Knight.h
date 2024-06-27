#pragma once
class Knight : public Player
{
public:
	Knight(string name, int hp, int atk);
	virtual ~Knight();

	// Player을(를) 통해 상속됨
	virtual void Attack(shared_ptr<Creature> other) override;
private:
};

