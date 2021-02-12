#pragma once
#include "Define.h"
// Класс набор игровых констант

class GameConstatnts {
public:

	const uint neutrall_roving_area = 300;				// Область брождения нейтрально-враждебных
	const uint neutrall_pursuit_dist = 1200;			// Максимальная дальность приследования нейтрально враждебных
	const uint neutrall_agressive_dist = 350;			// Дальность агрессивности нейтрально-враждебных

	const uint unit_exp_reward_for_level = 36;			// Награда опыта за убийство юнита умноженный на его уровень
	const uint unit_level_max = 101;					// Максимальный уровень юнитов
	const uint unit_walk_spd_max = 300;					// Максимальная скорость перемещения юнитов
	const uint unit_walk_spd_min = 60;					// Минимальная скорость перемещения
	const uint unit_time_dying_corpse = 120000;			// Время разложения умершего юнита	

	const uint hero_exp_for_level = 200;				// Опыт требуемый для получения уровня
	const uint hero_exp_for_increase = 100;				// Прирост требуемого опыта для повышения уровня
	const uint hero_max_level = 100;					// Максимальный уровень героя

	const uint hero_hit_point_add_str = 20;				// Прирост здоровья за еденицу силы
	const float hero_hit_point_reg_add_str = 0.04;		// Прирост регенерации здоровья за еденицу силы

	const uint hero_mana_point_add_int = 13;			// Прирост маны за еденицу интеллекта
	const float hero_mana_point_reg_add_int = 0.02;		// Прирост регенерации маны за еденицу интеллекта

	const uint hero_attack_speed_add_for_agi = 3;		// Прирост базовой скорости авто-атаки за еденицу ловкости в %
	const float hero_crit_power_add_for_agi = 0.02;		// Прирост множителя к критическим атакам за еденицу ловкости в %

	const float hero_hit_point_revive_factor = 0.5f;	// Фактор здоровья героя при воскрешении
	const float hero_mana_point_revive_factor = 0.f;	// Фактор маны героя при воскрешении

	const float timer_regeneration = 250.f;				// Общий таймер регенерации здоровья и маны всех юнитов в игре : 1000 = 1 секудна

	GameConstatnts() {
	}
	~GameConstatnts() {
	}
};