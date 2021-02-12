#pragma once
#include "oUnit.h"
#include "Orders.h"

// ����� ����� ������� ���� ������� oOrder
// ������������ ����� ������ � �������� ����������� ��� ������ ������
class UnitOrderable : public oUnit
{
protected:

	shared_ptr<oOrder> m_order;			// ���� �������, ������� ��������� �������� �����

	/* ��� ���� �������� ������������� ������������� � ������� ����������� - 
		- � ������, ���� �������� ������ ���������� ������, ��� ������ ������.
		- � ����� ������ � ��������������� �������� ��� �� ������������� ����������� - 
		- ����� ���� ��������. �������� m_animation_attack_left, m_animation_ability_cast, m_animation_death...*/

public:

	UnitOrderable(const v2f position, const PC player_controll) : oUnit(position, player_controll)
	{
		// ���� ������� � �������� ��������� ���� ������ �����, � ������ ���� ��� -
		// - ����������� ��������� ��������, ��������������� ���� �������
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

	// ���������� ������� ����� (������, ������� ��������� ����)
	virtual shared_ptr<oOrder> GetOrder() {
		return m_order;
	}
	// ��������� ������� ������ (������, ������� ��������� ����)
	virtual void SetOrder(shared_ptr<oOrder> order) {
		m_order = order;
	}

	virtual ~UnitOrderable() {}
};