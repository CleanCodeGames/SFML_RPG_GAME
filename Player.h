#pragma once
#include "Units.h"
#include "Heroes.h"

class Player
{
private:

	const PC m_player_controll;	// ����� ��������
	string m_name;				// ���
	uint m_gold = 0;			// ������
	uint m_crystall = 0;		// ���������
	

	vector<shared_ptr<UnitOrderable>> m_vec_unit;			// ������ �� ��������� ���� ������ � ���� (�� ������� �����)
	vector<shared_ptr<oHero>> m_vec_hero;					// ������ ������ ��� ��������� �������� ������
	shared_ptr<UnitOrderable> m_picked_unit_on_left_click;	// ��������� �� ���������� �����
	bool m_is_click_picked = false;							// ���� � ������ ���� ��������� ������ ����� ����

public:

	Shape m_shape_click_picked_circle;	// ������������ ���� �� ��������� �����
	Shape m_shape_ui_picked_unit_ally;	// ������ ��� �������� ���������� ����� (����������� �������)
	Shape m_shape_ui_picked_unit_enemy;	// ������ ��� �������� ���������� ����� (���������� ����� ���������� ����� (����������� �������))

	Player(PC p_controll, string name)
		: 
		m_player_controll(p_controll), 
		m_name(name)
	{
		m_picked_unit_on_left_click = nullptr;
	}

	~Player() {}

	// ������� ������ ����� ����� ������� �����
	void ActionPickUnitLeftClick() {
		if (B::IsMousePressed(sf::Mouse::Left)) {					// ���� ������ ����� ������ �����
			for (auto& unit : m_vec_unit) {							// ���������� �� ���� ������
				if (B::IsContains(unit->GetShape(), B::cur_p)) {	// ���� ������ ����� � ������ �����

					// ��� ��� ������� (�������� ����� �������� �����)
					//// �������� ClickPick �� ���� ������
					//for (auto& unit1 : m_vec_unit) {
					//	unit1->ClickPick(false);
					//}

					// ���� ��������� ���� ����������
					if (m_picked_unit_on_left_click != nullptr)
						m_picked_unit_on_left_click->ClickPick(false);

					// ���������� ����� �� ����� ��� ��������
					unit->ClickPick(true);
					m_picked_unit_on_left_click = unit;
					m_shape_click_picked_circle = B::CreateShape(unit->GetShape().getPosition(), unit->GetShape().getSize(), B::resources.texture.click_picked);

					// ����� ��������������� ���� ����� ������ (m_shape_click_picked_circle)
					if (unit->GetPlayerControll() == this->m_player_controll) m_shape_click_picked_circle.setFillColor(Color::Green);
					else if (unit->GetPlayerControll() == PlayerControll::P_NEUTRALL) m_shape_click_picked_circle.setFillColor(Color::Yellow);
					else m_shape_click_picked_circle.setFillColor(Color::Red);

					m_is_click_picked = true;
					break;	// ������� �� �����
				}
			}

			for (auto& hero : m_vec_hero) {							// ���������� �� ������ ������������� ������
				if (B::IsContains(hero->GetShape(), B::cur_p)) {	// ���� ������ ����� � ������ �����
					cout << hero->GetName() << endl;				// ������� ��� ����� � �������
					break;											// ������� �� �����
				}
			}
		}
	}

	// ����� ������ ���������� ����� ������ ������ �����
	void ActionPickUnitRightClick() {
		if (B::IsMousePressed(sf::Mouse::Right)) {
			bool is_target_unit = false;
			// ���� ��������� ���� ����������
			if (m_picked_unit_on_left_click != nullptr) {
				// ���� ���� ������ ������� � ����������� ���
				if (m_picked_unit_on_left_click->GetIsClickPick() && m_picked_unit_on_left_click->GetPlayerControll() == m_player_controll) 
				{
					for (auto& unit : m_vec_unit) {
						// ���� ������ ����� �������� �� ���� �����
						if (B::IsContains(unit->GetShape(), B::cur_p)) {
							is_target_unit = true;
							// ���� ���� ����������� ������ ��� �����-���������
							if (unit->GetPlayerControll() == m_player_controll || unit->GetPlayerControll() == PlayerControll::P_NEUTRALL) {
								// ����� ������ ��������� � ������� ������ ����� ��� ��������
								m_picked_unit_on_left_click->SetOrder(make_shared<OrderFollowToUnit>(*m_picked_unit_on_left_click, *unit));
							}
							else // ����� ���� ���� ��� �������� ���������
							{
								// ���� ��������� ������� ���� ����� ���������
								if (m_picked_unit_on_left_click->GetAutoAttack().GetAttackType() != TypeAttack::NONE)
								{	// ����� ������ ��������� �����
									m_picked_unit_on_left_click->SetOrder(make_shared<OrderAttackTargetUnit>(*m_picked_unit_on_left_click, *unit, m_picked_unit_on_left_click->GetAnimation()));
								}
								else // ����� ����� ������ ��������� � ������� ������ ����� ��� ��������
								{
									m_picked_unit_on_left_click->SetOrder(make_shared<OrderMoveToPoint>(*m_picked_unit_on_left_click, unit->GetShape().getPosition()));
								}
							}
							break;
						}
					}
					if (!is_target_unit) {
						m_picked_unit_on_left_click->SetOrder(make_shared<OrderMoveToPoint>(*m_picked_unit_on_left_click, B::cur_p));
					}
				}
			}
		}
	}

	// ���������� �������� ������
	void Action() {
		// ������� ������ ����� ����� ������� �����
		ActionPickUnitLeftClick();
		ActionPickUnitRightClick();
	}

public: // Gets...

	const uint& GetGold() {
		return m_gold;
	}

	const uint& GetCrystall() {
		return m_crystall;
	}
	// ���������� true, ���� � ������ ���� ��������� ������ ����� ����
	const bool GetIsClickPickedUnit() {
		return m_is_click_picked;
	}

	// ���������� ��������� �� ���������� ����� ����� ������� �����
	shared_ptr<UnitOrderable>& GetPickedUnitOnClick() {
		return m_picked_unit_on_left_click;
	}

public: // Sets...

	// ���������� ���� ������ ��������� ������ ��� ������������� ������������
	void SetPickedUnit(shared_ptr<UnitOrderable>& unit) {
		m_picked_unit_on_left_click = unit;
	}

	// ��������� ������ ������ �� ������, ������� ��������� ��� ��������� �������� ������
	void SetUnitGroup(vector<shared_ptr<UnitOrderable>>& vec_unit) {
		m_vec_unit = vec_unit;
	}

	// ��������� ������ ������ �� ������, ������� ��������� ��� ��������� �������� ������
	void SetHeroGroup(vector<shared_ptr<oHero>>& vec_hero) {
		m_vec_hero = vec_hero;
	}

	// ��������� ������ ����� � ������ ������ �� ������ ��� ��������� �������� ������
	// ���������� TRUE, ���� ���� ����������� ������
	bool AddUnitGroup(shared_ptr<UnitOrderable>& unit) {
		if (unit->GetPlayerControll() == m_player_controll) {
			m_vec_unit.push_back(unit);
			return true;
		}
		return false;
	}

	// ��������� ������ ����� � ������ ������ �� ������ ��� ��������� �������� ������
	// ���� ���� �� ����������� ������, �� ���� ������ ���� �� ����(�����) ������
	void AddUnitGroupControllAndRecolor(shared_ptr<UnitOrderable>& unit) {
		if (unit->GetPlayerControll() != m_player_controll)
			unit->SetPlayerControll(m_player_controll);
		m_vec_unit.push_back(unit);
	}

	void SetGold(uint amount) {
		m_gold = amount;
	}

	void AddGold(uint amount) {
		m_gold += amount;
	}

	// �������� ���������(amount) ���������� ������ � ���������� true ���� ���-�� ������ ������ ��� amount.
	// ���� �������� is_deficiently ���������� true, �� ���� ���-�� ������ ������ amount, �� ��� ������ ������ ���� (0) � ����� true
	// ����� � ������� ��������� ��������� � �������� ������ � ������� false
	bool SpendGold(uint amount, bool is_deficiently = false) {
		if (amount > m_gold) {
			if (!is_deficiently) {
				cout << "������������ ������!" << endl;
				return false;
			}
			else {
				m_gold = 0;
				return is_deficiently;
			}
		}
		else {
			m_gold -= amount;
			return true;
		}
		cout << "������� bool SpendGold(uint amount, bool is_deficiently = false) � ����� Player.h: ���-�� ����� �� ���!" << endl;
		return false;
	}

	void SetCrystall(uint amount) {
		m_crystall = amount;
	}

	void AddCrystall(uint amount) {
		m_crystall += amount;
	}

	// �������� ���������(amount) ���������� ���������� � ���������� true ���� ���-�� ���������� ������ ��� amount.
	// ���� �������� is_deficiently ���������� true, �� ���� ���-�� ���������� ������ amount, �� ��� ���������� ������ ���� (0) � ����� true
	// ����� � ������� ��������� ��������� � �������� ���������� � ������� false
	bool SpendCrystall(uint amount, bool is_deficiently = false) {
		if (amount > m_crystall) {
			if (!is_deficiently)  {
				cout << "������������ ����������!" << endl;
				return false;
			}
			else {
				m_crystall = 0;
				return is_deficiently;
			}
		}
		else {
			m_crystall -= amount;
			return true;
		}
		cout << "������� bool SpendCrystall(uint amount, bool is_deficiently = false) � ����� Player.h: ���-�� ����� �� ���!" << endl;
		return false;
	}

};

