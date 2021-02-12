#pragma once
#include "oUnit.h"
#include "Orders.h"

// Класс юнита имеющий поле приказа oOrder
// Наследование этого класса в основном использется для боевых юнитов
class UnitOrderable : public oUnit
{
protected:

	shared_ptr<oOrder> m_order;			// Поле приказа, умеющий подменять действия юнита

	/* Все поля анимаций настраиваются индивидуально в классах наследниках - 
		- в случае, если содержат разные количество кадров, или размер кадров.
		- В типах юнитов с дополнительными анимации так же индивидуально добовляются - 
		- новые поля анимаций. Например m_animation_attack_left, m_animation_ability_cast, m_animation_death...*/

public:

	UnitOrderable(const v2f position, const PC player_controll) : oUnit(position, player_controll)
	{
		// Поле приказа в качестве аргумента берёт самого юнита, и внутри него уже -
		// - проделываем алгоритмы действий, соответствующие типу приказа
		SetOrder(make_shared<OrderStand>(OrderStand(*this)));
	}

	virtual void Update() {
		oUnit::Update();
		if (GetLiveState() == LiveState::ALIVE) {
			m_auto_attack.Update();
			//m_animation->Play();
			m_order->Update();
		}
	}

	// Возвращает текущий ордер (Приказ, который выполняет юнит)
	virtual shared_ptr<oOrder> GetOrder() {
		return m_order;
	}
	// Подменяем текущий приказ (Приказ, который выполняет юнит)
	virtual void SetOrder(shared_ptr<oOrder> order) {
		m_order = order;
	}

	virtual ~UnitOrderable() {}
};