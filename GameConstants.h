#pragma once
#include "Define.h"
// ����� ����� ������� ��������

class GameConstatnts {
public:

	const uint neutrall_roving_area = 300;				// ������� ��������� ����������-����������
	const uint neutrall_pursuit_dist = 1200;			// ������������ ��������� ������������� ���������� ����������
	const uint neutrall_agressive_dist = 350;			// ��������� ������������� ����������-����������

	const uint unit_exp_reward_for_level = 36;			// ������� ����� �� �������� ����� ���������� �� ��� �������
	const uint unit_level_max = 101;					// ������������ ������� ������
	const uint unit_walk_spd_max = 300;					// ������������ �������� ����������� ������
	const uint unit_walk_spd_min = 60;					// ����������� �������� �����������
	const uint unit_time_dying_corpse = 120000;			// ����� ���������� �������� �����	

	const uint hero_exp_for_level = 200;				// ���� ��������� ��� ��������� ������
	const uint hero_exp_for_increase = 100;				// ������� ���������� ����� ��� ��������� ������
	const uint hero_max_level = 100;					// ������������ ������� �����

	const uint hero_hit_point_add_str = 20;				// ������� �������� �� ������� ����
	const float hero_hit_point_reg_add_str = 0.04;		// ������� ����������� �������� �� ������� ����

	const uint hero_mana_point_add_int = 13;			// ������� ���� �� ������� ����������
	const float hero_mana_point_reg_add_int = 0.02;		// ������� ����������� ���� �� ������� ����������

	const uint hero_attack_speed_add_for_agi = 3;		// ������� ������� �������� ����-����� �� ������� �������� � %
	const float hero_crit_power_add_for_agi = 0.02;		// ������� ��������� � ����������� ������ �� ������� �������� � %

	const float hero_hit_point_revive_factor = 0.5f;	// ������ �������� ����� ��� �����������
	const float hero_mana_point_revive_factor = 0.f;	// ������ ���� ����� ��� �����������

	const float timer_regeneration = 250.f;				// ����� ������ ����������� �������� � ���� ���� ������ � ���� : 1000 = 1 �������

	GameConstatnts() {
	}
	~GameConstatnts() {
	}
};