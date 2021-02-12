#pragma once

// ��� �������
enum class TypeOrder : uint {
	NONE,								// �������������
	GUARD,								// ��������
	STAND,								// ���������� �� �����
	MOVE_TO_POINT,						// ���������
	MOVE_TO_POINT_ATTACKING_ENEMIES,	// ���������, ������� ������� �� �����������
	MOVE_TO_TAKE_ITEM,					// ��������� � �������� � ������� ���
	ATTACK_TARGET_UNIT,					// ��������� ����������� �����
	CAST_ABILITY_POINT,					// ������������ ���������� � ��������� �����
	CAST_ABILITY_UNIT,					// ������������ ���������� �� �����
	CAST_ABILITY_INSTANT,				// ��������� ������������ ����������
	CAST_ABILITY_CHANNEL				// ������������ ����������� ����������
};

// ����������� ����� ������� (NONE) - �������������
class oOrder
{
protected:
	
	bool m_is_end = false;		// ���������� ������� ���������
	bool m_is_cancel = false;	// ���������� ������� ��������
	TypeOrder m_type;			// ��� �������
	oUnit& m_order_unit;		// ���� ����������� ������

public:

	oOrder(oUnit& order_unit) : m_order_unit(order_unit) {
		m_type = TypeOrder::NONE;
	}

	virtual const v2f& GetTargetPosition() {
		return m_order_unit.GetShape().getPosition();
	}

	virtual void Update() = 0;

	// ���������� ������� ���������
	virtual const bool GetIsEnd() {
		return m_is_end;
	}

	// ���������� ������� ��������
	virtual const bool GetIsCancel() {
		return m_is_cancel;
	}

	// ��������� ���������� �������
	virtual void End() {
		m_is_end = true;
	}

	// �������� ���������� �������
	virtual void Cancel() {
		m_is_cancel = true;
	}

	// ��� ������������ �������
	virtual const TypeOrder GetType() const {
		return m_type;
	}

	virtual ~oOrder() = default;
};

// ����� ������� (GUARD) - ��������� �� ������ ����������
class OrderGuard : public oOrder {
private:

	v2f m_target_position;					// ���� ����� �������
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

// ����� ������� (STAND) - ���������� �� �����
class OrderStand : public oOrder {
private:

	v2f m_target_position;				// ���� ����� �������

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

// ����� ������� (MOVE_TO_POINT) - ��������� � ��������� �����
class OrderMoveToPoint : public oOrder {
private:

	const v2f m_target_position; // ���� ����� �������
	float m_distance;			 // ���������� �� ����� �������

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

// ����� ������� (MOVE_TO_POINT) - ��������� �� ������
class OrderFollowToUnit : public oOrder {
private:

	oUnit& m_target_unit;	// ���� ����� �������

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

// ����� ������� (ATTACK_TARGET_UNIT) - ��������� ���������� �����
class OrderAttackTargetUnit : public oOrder {
private:

	Animation& m_anim_attack;
	oUnit& m_target_unit;	// ���� ���� �������

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

		// ���� ��������� �� ���� ������ ��� ��������� ����� ����� - ������������ ������.
		if (dist_to_target > m_order_unit.GetAutoAttack().GetAttackDistance())
		{
			m_order_unit.SetWalkState(WalkState::WALK);
			B::MoveToAngle( m_order_unit.GetShape(), B::GetAngle(m_order_unit.GetShape(), GetTargetPosition()), m_order_unit.GetMoveSpeed().GetCurrent() * B::time);
		}
		else {
			m_order_unit.SetWalkState(WalkState::ATTACK);
			if (m_order_unit.GetAutoAttack().GetIsAttackDelay()) {	// ���� ���� ����� ��������� �����
				m_anim_attack.Play(false);							// ����������� �������� �����
				if (m_anim_attack.IsEnd()) {						// ���� �������� ����� ���������
					m_order_unit.GetAutoAttack().Delay();			// ���������� ����� �� �����������
					cout << "Attack!\n";
				}
			}
			//End();
		}
	}

	virtual ~OrderAttackTargetUnit() {

	}
};