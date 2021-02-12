#pragma once
#include "UnitOrderable.h"

enum class TypeHero : uint {
	ASASSIN,	// Ловкий убийца (Главная хар-ка ловкость)
	WARIOR,		// Сильный воин (Главная хар-ка сила)
	MAGE		// Маг (Главная хар-ка разум)
};

class Experience {
private:

	uint m_current;
	uint m_value;
	uint m_need_for_next_lvl;

public:

	void Add(uint value) {
		m_current += value;
	}

	bool IsLevelUp(uint& current_hero_lvl) {
		if (m_current > m_need_for_next_lvl) {
			m_current -= m_need_for_next_lvl;
			m_need_for_next_lvl = 200 + (B::gc.hero_exp_for_increase * current_hero_lvl);
			current_hero_lvl++;
			return true;
		}
		return false;
	}

	Experience() {

	}

	~Experience() {

	}
};

class oHero : public UnitOrderable
{
private:

protected:

	TypeHero m_type_hero = TypeHero::ASASSIN;
	
public:
	
	oHero(
		const v2f position,
		const PC player_controll = PC::P_NEUTRALL, 
		const TypeHero type_hero = TypeHero::ASASSIN
	)
		: 
		UnitOrderable(position, player_controll),
		m_type_hero(type_hero)
	{
		SetTypeUnit(TypeUnit::HUMANOID);
		SetLiveState(LiveState::ALIVE);
		SetWalkState(WalkState::STAND);
		SetAutoAttack(AutoAttack(TypeAttack::MELEE, TypeDamage::INCISIVE, TypeDamageModifier::STANDART, 120, 10, 0, 1800, 0));
		SetArmor(Armor(TypeArmor::LEATH, 2, 0));
		SetMoveSpeed(MovementSpeed(0.3f));
		SetHitPnt(HitPoint(220, 220, 0.25));
		SetManaPnt(ManaPoint(0, 0, 0));
		SetName("Hero");
		SetLevel(1);
	}

	virtual ~oHero() {

	}

	virtual void Update() override {
		UnitOrderable::Update();
	}

public: // Gets... 

	const TypeHero& GetType() {
		return m_type_hero;
	}

public: // Sets...


};