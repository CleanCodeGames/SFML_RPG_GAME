#pragma once

// Тип приказа
enum class TypeOrder : uint {
	NONE,								// Неопределенно
	GUARD,								// Охранять
	STAND,								// Оставаться на месте
	MOVE_TO_POINT,						// Двигаться
	MOVE_TO_POINT_ATTACKING_ENEMIES,	// Двигаться, попутно нападая на противников
	MOVE_TO_TAKE_ITEM,					// Двигаться к предмету и поднять его
	ATTACK_TARGET_UNIT,					// Атаковать конкретного юнита
	CAST_ABILITY_POINT,					// Использовать заклинание в указанную точку
	CAST_ABILITY_UNIT,					// Использовать заклинание на юнита
	CAST_ABILITY_INSTANT,				// Мгновенно использовать заклинание
	CAST_ABILITY_CHANNEL				// Использовать прерываемое заклинание
};

// Абстрактный класс приказа (NONE) - Неопределенно
class oOrder
{
protected:
	
	bool m_is_end = false;		// Выполнение приказа закончено
	bool m_is_cancel = false;	// Выполнение приказа отменено
	TypeOrder m_type;			// Тип приказа
	oUnit& m_order_unit;		// Юнит выполняющий приказ

public:

	oOrder(oUnit& order_unit) : m_order_unit(order_unit) {
		m_type = TypeOrder::NONE;
	}

	virtual const v2f& GetTargetPosition() {
		return m_order_unit.GetShape().getPosition();
	}

	virtual void Update() = 0;

	// Выполнение приказа завершено
	virtual const bool GetIsEnd() {
		return m_is_end;
	}

	// Выполнение приказа отменено
	virtual const bool GetIsCancel() {
		return m_is_cancel;
	}

	// Заверщить выполнение приказа
	virtual void End() {
		m_is_end = true;
	}

	// Отменить выполнение приказа
	virtual void Cancel() {
		m_is_cancel = true;
	}

	// Тип выполняемого приказа
	virtual const TypeOrder GetType() const {
		return m_type;
	}

	virtual ~oOrder() = default;
};

// Класс приказа (GUARD) - защищатся от врагов поблизости
class OrderGuard : public oOrder {
private:

	v2f m_target_position;					// Цель точка приказа
	vector<shared_ptr<oUnit>> m_vec_unit;	// 

public:

	OrderGuard(oUnit& order_unit, vector<shared_ptr<oUnit>>& vec_unit) 
		: oOrder(order_unit), m_vec_unit(vec_unit)
	{
		if (m_order_unit.GetIsAttackUses()) m_type = TypeOrder::GUARD;
		else m_type = TypeOrder::STAND;
		order_unit.SetWalkState(WalkState::STAND);
		m_target_position = order_unit.GetShape().getPosition();
	}

	virtual const v2f& GetTargetPosition() override {
		return m_target_position;
	}

	virtual void Update() override {
		if (m_order_unit.GetIsAttackUses()) {
			shared_ptr<oUnit> order_unit(&m_order_unit);
			for (auto& unit : m_vec_unit) {
				if (unit == order_unit)
				{
					cout << "Unit: " << unit << endl;
					cout << "Order Unit: " << &m_order_unit << endl;
				}
			}
		}
	}

	virtual ~OrderGuard() {

	}
};

// Класс приказа (STAND) - оставаться на месте
class OrderStand : public oOrder {
private:

	v2f m_target_position;				// Цель точка приказа

public:

	OrderStand(oUnit& order_unit)
		: oOrder(order_unit)
	{
		m_type = TypeOrder::STAND;
		m_target_position = order_unit.GetShape().getPosition();
		m_order_unit.SetWalkState(WalkState::STAND);
	}

	virtual const v2f& GetTargetPosition() override {
		return m_target_position;
	}

	virtual void Update() override {
	}

	virtual ~OrderStand() {

	}
};

// Класс приказа (MOVE_TO_POINT) - двигаться в указанную точку
class OrderMoveToPoint : public oOrder {
private:

	const v2f m_target_position; // Цель точка приказа
	float m_distance;			 // Расстояние до точки приказа

public:

	OrderMoveToPoint(oUnit& order_unit, const v2f target_position)
		: oOrder(order_unit),
		m_target_position(target_position)
	{
		m_type = TypeOrder::MOVE_TO_POINT;
		m_order_unit.SetWalkState(WalkState::WALK);
		m_distance = B::GetDistance(m_order_unit.GetShape().getPosition(), m_target_position);
	}

	virtual const v2f& GetTargetPosition() override {
		return m_target_position;
	}

	virtual void Update() override {
		if (m_distance > 0) {
			const float speed = m_order_unit.GetMoveSpeed().GetCurrent() * B::time;
			m_distance -= speed;
			B::MoveToAngle(m_order_unit.GetShape(), B::GetAngle(m_order_unit.GetShape(), m_target_position), speed);
		}
		else {
			m_order_unit.SetWalkState(WalkState::STAND);
			m_order_unit.GetShape().setPosition(m_target_position);
			End();
		}
	}

	virtual ~OrderMoveToPoint() {

	}
};

// Класс приказа (MOVE_TO_POINT) - Следовать за юнитом
class OrderFollowToUnit : public oOrder {
private:

	oUnit& m_target_unit;	// Цель точка приказа

public:

	OrderFollowToUnit(oUnit& order_unit, oUnit& target_unit)
		: oOrder(order_unit),
		m_target_unit(target_unit) {
		m_type = TypeOrder::MOVE_TO_POINT;
		m_order_unit.SetWalkState(WalkState::WALK);
	}

	virtual const v2f& GetTargetPosition() override {
		return m_target_unit.GetShape().getPosition();
	}

	virtual void Update() override {
		const float distance = B::GetDistance(m_order_unit.GetShape().getPosition(), m_target_unit.GetShape().getPosition());
		const float distance_min = (m_order_unit.GetShape().getSize().x + m_target_unit.GetShape().getSize().x) / 2;

		if (distance > distance_min) 
		{
			m_order_unit.SetWalkState(WalkState::WALK);
			const float speed = m_order_unit.GetMoveSpeed().GetCurrent() * B::time;
			B::MoveToAngle(m_order_unit.GetShape(), B::GetAngle(m_order_unit.GetShape(), m_target_unit.GetShape().getPosition()), speed);
		}
		else m_order_unit.SetWalkState(WalkState::STAND);
	}

	virtual ~OrderFollowToUnit() {

	}
};

// Класс приказа (ATTACK_TARGET_UNIT) - атаковать вражеского юнита
class OrderAttackTargetUnit : public oOrder {
private:

	Animation& m_anim_attack;
	oUnit& m_target_unit;	// Цель юнит приказа

public:

	OrderAttackTargetUnit(oUnit& order_unit, oUnit& target_unit, Animation& anim_attack)
		: oOrder(order_unit),
		m_target_unit(target_unit),
		m_anim_attack(anim_attack)
	{
		m_type = TypeOrder::ATTACK_TARGET_UNIT;
		m_order_unit.SetWalkState(WalkState::WALK);
	}

	virtual const v2f& GetTargetPosition() override {
		return m_target_unit.GetShape().getPosition();
	}

	virtual void Update() override {

		float dist_to_target = B::GetDistance(m_order_unit.GetShape(), m_target_unit.GetShape());

		if (m_order_unit.GetWalkState() == WalkState::ATTACK) 
			dist_to_target *= 1.25;

		// Если дистанция до цели больше чем дальность атаки юнита - выполняющего приказ.
		if (dist_to_target > m_order_unit.GetAutoAttack().GetAttackDistance())
		{
			m_order_unit.SetWalkState(WalkState::WALK);
			B::MoveToAngle( m_order_unit.GetShape(), B::GetAngle(m_order_unit.GetShape(), GetTargetPosition()), m_order_unit.GetMoveSpeed().GetCurrent() * B::time);
		}
		else {
			m_order_unit.SetWalkState(WalkState::ATTACK);
			if (m_order_unit.GetAutoAttack().GetIsAttackDelay()) {	// Если юнит готов совершить атаку
				m_anim_attack.Play(false);							// Проигрываем анимацию атаки
				if (m_anim_attack.IsEnd()) {						// Если анимация атаки завершена
					m_order_unit.GetAutoAttack().Delay();			// Отправляем атаку на перезарядку
					cout << "Attack!\n";
				}
			}
			//End();
		}
	}

	virtual ~OrderAttackTargetUnit() {

	}
};