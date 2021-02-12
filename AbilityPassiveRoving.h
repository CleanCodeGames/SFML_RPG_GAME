#pragma once
#include "oAbility.h"

// —пособность "Ѕрод€чий" используетс€ дл€ нейтральных животных - коров, кур, овечек и т.д.
class AbilityPassiveRoving : oAbility
{
private:

	float m_timer_activation = 0;			 // “аймер срабатывани€ брод€чего
	v2f m_roving_position;					 //  онечна€ точка брод€чего
	const v2f& m_spawn_position;			 // ќколо брод€ча€ точка
	static constexpr uint m_radius = 300;	 // –адиус выбора конечной точки брод€чего
	UnitOrderable& m_unit;

	// ѕереназначение конечной точки брод€чего
	inline void ResetPoint() {
		// ¬ыбираем случайную точку в радиусе (m_radius) от "ќколо брод€чей точки"
		m_roving_position = B::GetNormalizedPosition(m_spawn_position, rand() % m_radius, rand() % 360);
		m_unit.SetOrder(make_shared<OrderMoveToPoint>(m_unit, m_roving_position));
		m_timer_activation = rand() % 9000 + 1000; 	// ќбновл€ем таймер до 10 сек.
	}

public:

	AbilityPassiveRoving(UnitOrderable& unit) 
		: m_unit(unit), 
		m_spawn_position(unit.GetSpawnPosition()) 
	{
		m_name = "Ѕрод€чий";
		m_description = "¬ладелец этой способности будет переодически прогуливатьс€\nв случайную точку в области " + to_string(m_radius) + " ед. от точки спавна.";
		m_level	= 1;
		m_level_max = 1;
		m_unit.SetOrder(make_shared<OrderMoveToPoint>(m_unit, m_roving_position));
	}

	const v2f& GetRovingPosition() {
		return m_roving_position;
	}

	virtual void Update() override {
		m_timer_activation -= B::time;
		if (m_timer_activation < 0) { // ≈сли таймер активации достиг нул€
			if (m_unit.GetOrder()->GetIsEnd()) {
				ResetPoint();
			}
		}
	}

	~AbilityPassiveRoving() {

	}
};