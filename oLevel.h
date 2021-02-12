#pragma once
#include "Player.h"

class oLevel
{
private:

	float m_timer_regeneration_world = 0.f;

	// Мировой таймер регенерации здоровья и маны всех юнитов
	bool IsTimerRegenerationWorldTick() {
		m_timer_regeneration_world += B::time;
		if (m_timer_regeneration_world >= B::gc.timer_regeneration) {
			m_timer_regeneration_world -= B::gc.timer_regeneration;
			return true;
		}
		return false;
	}

	

protected:

	shared_ptr<Player> m_player;
	vector<shared_ptr<UnitOrderable>> m_vec_unit;
	vector<shared_ptr<oHero>> m_vec_hero;
	vector<Shape> m_vec_map_elem;
	v2i m_map_size;
	string m_map_name;
	bool m_is_next = false;

	// Доступ к последнему созданному юниту
	shared_ptr<UnitOrderable>& GetLastAddedUnit() {
		return m_vec_unit.back();
	}

public:

	oLevel() 
	{
	}

	// Загрузка уровня из файла .phmap
	virtual bool LoadFromFile(const string fname) {
		// Код загрузки
		return true;
	}

	// Возвращает флаг перехода на следующий уровень
	virtual bool IsNext() {
		return m_is_next;
	}

	// Обновление логики покадрово
	virtual void Update() {
		for (auto& unit1 : m_vec_unit) {
			unit1->Update();
		}
	}

	// Обработка событий (ввод с клавы, мышь)
	virtual void Action() {
		for (auto& unit : m_vec_unit) {
			unit->Action();
		}
		m_player->Action();
		// Если выбран юнит то отобразить его изображение справа вверху
		//..if(m_player->GetPickedUnitOnClick()->GetName()) 
	}

	// Отрисовка игровых объектов
	virtual void Draw() {
		const sf::FloatRect& cam_rect = B::GetCamVisible();
		for (auto& unit : m_vec_unit) {
			if (cam_rect.intersects(unit->GetShape().getGlobalBounds())) {
				unit->Draw();
				if (unit->GetIsClickPick()) {
					m_player->m_shape_click_picked_circle.setPosition(unit->GetShape().getPosition());
					B::wnd.draw(m_player->m_shape_click_picked_circle);
				}
			}
		}
	}

	virtual ~oLevel() {
	}
};