#pragma once
#include "Units.h"
#include "Heroes.h"

class Player
{
private:

	const PC m_player_controll;	// Номер контроля
	string m_name;				// Имя
	uint m_gold = 0;			// Золото
	uint m_crystall = 0;		// Кристаллы
	

	vector<shared_ptr<UnitOrderable>> m_vec_unit;			// Группа из абсолютно всех юнитов в игре (на текущей карте)
	vector<shared_ptr<oHero>> m_vec_hero;					// Группа героев под контролем текущего игрока
	shared_ptr<UnitOrderable> m_picked_unit_on_left_click;	// Указатель на выбранного юнита
	bool m_is_click_picked = false;							// Если у игрока есть выбранный кликом мышки юнит

public:

	Shape m_shape_click_picked_circle;	// Отображаемый круг на выбранном юните
	Shape m_shape_ui_picked_unit_ally;	// Иконка для портрета выбранного юнита (Управляемый игроком)
	Shape m_shape_ui_picked_unit_enemy;	// Иконка для портрета выбранного юнита (Являющиеся целью выбранного юнита (Управляемый игроком))

	Player(PC p_controll, string name)
		: 
		m_player_controll(p_controll), 
		m_name(name)
	{
		m_picked_unit_on_left_click = nullptr;
	}

	~Player() {}

	// Функция выбора юнита левой кнопкой мышки
	void ActionPickUnitLeftClick() {
		if (B::IsMousePressed(sf::Mouse::Left)) {					// Если нажали левую кнопку мышки
			for (auto& unit : m_vec_unit) {							// Проходимся по всем юнитам
				if (B::IsContains(unit->GetShape(), B::cur_p)) {	// Если курсор попал в спрайт юнита

					// Это для обводки (массовый выбор обводкой мышки)
					//// Обнуляем ClickPick на всех юнитах
					//for (auto& unit1 : m_vec_unit) {
					//	unit1->ClickPick(false);
					//}

					// Если выбранный юнит существует
					if (m_picked_unit_on_left_click != nullptr)
						m_picked_unit_on_left_click->ClickPick(false);

					// Определяем выбор на юните под курсором
					unit->ClickPick(true);
					m_picked_unit_on_left_click = unit;
					m_shape_click_picked_circle = B::CreateShape(unit->GetShape().getPosition(), unit->GetShape().getSize(), B::resources.texture.click_picked);

					// Задаём соответствующий цвет круга выбора (m_shape_click_picked_circle)
					if (unit->GetPlayerControll() == this->m_player_controll) m_shape_click_picked_circle.setFillColor(Color::Green);
					else if (unit->GetPlayerControll() == PlayerControll::P_NEUTRALL) m_shape_click_picked_circle.setFillColor(Color::Yellow);
					else m_shape_click_picked_circle.setFillColor(Color::Red);

					m_is_click_picked = true;
					break;	// Выходим из цикла
				}
			}

			for (auto& hero : m_vec_hero) {							// Проходимся по героям принадлежащим игроку
				if (B::IsContains(hero->GetShape(), B::cur_p)) {	// Если курсор попал в спрайт героя
					cout << hero->GetName() << endl;				// Выводим имя героя в консоль
					break;											// Выходим из цикла
				}
			}
		}
	}

	// Задаём приказ выбранному юниту правой кнопки мышки
	void ActionPickUnitRightClick() {
		if (B::IsMousePressed(sf::Mouse::Right)) {
			bool is_target_unit = false;
			// Если выбранный юнит существует
			if (m_picked_unit_on_left_click != nullptr) {
				// Если юнит выбран игроком и принадлежит ему
				if (m_picked_unit_on_left_click->GetIsClickPick() && m_picked_unit_on_left_click->GetPlayerControll() == m_player_controll) 
				{
					for (auto& unit : m_vec_unit) {
						// Если курсор мышки попадает на шейп юнита
						if (B::IsContains(unit->GetShape(), B::cur_p)) {
							is_target_unit = true;
							// Если юнит принадлежит игроку или нейтр-пассивный
							if (unit->GetPlayerControll() == m_player_controll || unit->GetPlayerControll() == PlayerControll::P_NEUTRALL) {
								// Задаём приказ двигаться в позицию фигуры юнита под курсором
								m_picked_unit_on_left_click->SetOrder(make_shared<OrderFollowToUnit>(*m_picked_unit_on_left_click, *unit));
							}
							else // Иначе если юнит под курсором вражеский
							{
								// Если выбранный игроком юнит умеет атаковать
								if (m_picked_unit_on_left_click->GetAutoAttack().GetAttackType() != TypeAttack::NONE)
								{	// Задаём приказ атаковать юнита
									m_picked_unit_on_left_click->SetOrder(make_shared<OrderAttackTargetUnit>(*m_picked_unit_on_left_click, *unit, m_picked_unit_on_left_click->GetAnimation()));
								}
								else // Иначе задаём приказ двигаться в позицию фигуры юнита под курсором
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

	// Обработчик действий игрока
	void Action() {
		// Функция выбора юнита левой кнопкой мышки
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
	// Возвращает true, если у игрока есть выбранный кликом мышки юнит
	const bool GetIsClickPickedUnit() {
		return m_is_click_picked;
	}

	// Возвращает указатель на выбранного юнита левой кнопкой мышки
	shared_ptr<UnitOrderable>& GetPickedUnitOnClick() {
		return m_picked_unit_on_left_click;
	}

public: // Sets...

	// Переданный юнит станет выбранным юнитом без вмешательства пользователя
	void SetPickedUnit(shared_ptr<UnitOrderable>& unit) {
		m_picked_unit_on_left_click = unit;
	}

	// Заполняет вектор ссылок на юнитов, которые находятся под контролем текущего игрока
	void SetUnitGroup(vector<shared_ptr<UnitOrderable>>& vec_unit) {
		m_vec_unit = vec_unit;
	}

	// Заполняет вектор ссылок на героев, которые находятся под контролем текущего игрока
	void SetHeroGroup(vector<shared_ptr<oHero>>& vec_hero) {
		m_vec_hero = vec_hero;
	}

	// Добавляет одного юнита в вектор ссылок на юнитов под контролем текущего игрока
	// Возвращает TRUE, если юнит принадлежит игроку
	bool AddUnitGroup(shared_ptr<UnitOrderable>& unit) {
		if (unit->GetPlayerControll() == m_player_controll) {
			m_vec_unit.push_back(unit);
			return true;
		}
		return false;
	}

	// Добавляет одного юнита в вектор ссылок на юнитов под контролем текущего игрока
	// Если юнит не принадлежит игроку, то юнит меняет цвет на цвет(номер) игрока
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

	// Отнимает указанное(amount) количество золота и возвращает true если кол-во золота больше чем amount.
	// Если параметр is_deficiently установлен true, то если кол-во золота меньше amount, то кол золото станет ноль (0) и вернёт true
	// Иначе в консоль выведется сообщение о нехватке золота и вернётся false
	bool SpendGold(uint amount, bool is_deficiently = false) {
		if (amount > m_gold) {
			if (!is_deficiently) {
				cout << "Недостаточно золота!" << endl;
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
		cout << "Функция bool SpendGold(uint amount, bool is_deficiently = false) в файле Player.h: Что-то пошло не так!" << endl;
		return false;
	}

	void SetCrystall(uint amount) {
		m_crystall = amount;
	}

	void AddCrystall(uint amount) {
		m_crystall += amount;
	}

	// Отнимает указанное(amount) количество кристаллов и возвращает true если кол-во кристаллов больше чем amount.
	// Если параметр is_deficiently установлен true, то если кол-во кристаллов меньше amount, то кол кристаллов станет ноль (0) и вернёт true
	// Иначе в консоль выведется сообщение о нехватке кристаллов и вернётся false
	bool SpendCrystall(uint amount, bool is_deficiently = false) {
		if (amount > m_crystall) {
			if (!is_deficiently)  {
				cout << "Недостаточно кристаллов!" << endl;
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
		cout << "Функция bool SpendCrystall(uint amount, bool is_deficiently = false) в файле Player.h: Что-то пошло не так!" << endl;
		return false;
	}

};

