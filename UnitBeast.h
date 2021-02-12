#pragma once
#include "oUnit.h"

class UnitBeast : public UnitOrderable
{
private:

protected:

public:

	UnitBeast(const v2f position, const PC player_controll) : UnitOrderable(position, player_controll) {
		SetTypeUnit(TypeUnit::BEAST);
		SetLiveState(LiveState::ALIVE);
		SetWalkState(WalkState::STAND);
		SetAutoAttack(AutoAttack(TypeAttack::MELEE, TypeDamage::INCISIVE, TypeDamageModifier::STANDART, 90, 10, 0, 1800, 0));
		SetArmor(Armor(TypeArmor::CLOTH, 2, 0));
		SetHitPnt(HitPoint(220, 220, 0.25));
		SetManaPnt(ManaPoint(0, 0, 0));
		SetMoveSpeed(MovementSpeed(0.25f));
		SetName("Scorpio");
		SetLevel(1);
	}

	virtual void Update() override 
	{ 
		UnitOrderable::Update();
	}

	virtual void Action() override 
	{ 

	}

	virtual void Draw() override { 
		B::wnd.draw(m_shape);
	}

	virtual ~UnitBeast() {

	}
};