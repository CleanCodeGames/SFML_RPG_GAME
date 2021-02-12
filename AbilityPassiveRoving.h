#pragma once
#include "oAbility.h"

// ����������� "��������" ������������ ��� ����������� �������� - �����, ���, ������ � �.�.
class AbilityPassiveRoving : oAbility
{
private:

	float m_timer_activation = 0;			 // ������ ������������ ���������
	v2f m_roving_position;					 // �������� ����� ���������
	const v2f& m_spawn_position;			 // ����� �������� �����
	static constexpr uint m_radius = 300;	 // ������ ������ �������� ����� ���������
	UnitOrderable& m_unit;

	// �������������� �������� ����� ���������
	inline void ResetPoint() {
		// �������� ��������� ����� � ������� (m_radius) �� "����� �������� �����"
		m_roving_position = B::GetNormalizedPosition(m_spawn_position, rand() % m_radius, rand() % 360);
		m_unit.SetOrder(make_shared<OrderMoveToPoint>(m_unit, m_roving_position));
		m_timer_activation = rand() % 9000 + 1000; 	// ��������� ������ �� 10 ���.
	}

public:

	AbilityPassiveRoving(UnitOrderable& unit) 
		: m_unit(unit), 
		m_spawn_position(unit.GetSpawnPosition()) 
	{
		m_name = "��������";
		m_description = "�������� ���� ����������� ����� ������������ �������������\n� ��������� ����� � ������� " + to_string(m_radius) + " ��. �� ����� ������.";
		m_level	= 1;
		m_level_max = 1;
		m_unit.SetOrder(make_shared<OrderMoveToPoint>(m_unit, m_roving_position));
	}

	const v2f& GetRovingPosition() {
		return m_roving_position;
	}

	virtual void Update() override {
		m_timer_activation -= B::time;
		if (m_timer_activation < 0) { // ���� ������ ��������� ������ ����
			if (m_unit.GetOrder()->GetIsEnd()) {
				ResetPoint();
			}
		}
	}

	~AbilityPassiveRoving() {

	}
};