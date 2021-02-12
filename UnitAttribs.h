#pragma once
#include "Base.h"
// static sf::Text text_hit(mana)_point ��� ����������� � ���������� ��� ����� �� �����
class Point 
{
protected:
	
	uint m_maximum;			// ������������ : ������� 500/500 ��.
	int m_current;			// ������� : �������� 376/500
	float m_regeneration;	// ** ����������� : ����������� 4 ���� � �������

public:

	Point(uint max = 100, uint curr = 100, float regen = 0) {
		m_maximum = max;
		m_current = curr;
		m_regeneration = regen;
	}

	// ������ ��������� �������� � ��������� �������� �������� � ���������� �����������
	// ���� ������� is_current_full, �� �������� �������� ������ ������
	virtual void SetMax(uint value, bool is_current_full = false) {
		m_maximum = value;
		const int current = m_current;
		is_current_full ? m_current = m_maximum : m_current = (current / 100) * (m_maximum / 100) * 100;
	}

	// ���������� ��������������
	virtual void Restore(const uint value) {
		m_current += value;
		if (m_current > m_maximum) {
			m_current = m_maximum;
		}
	}

	virtual void SetRegeneration(float value) {
		m_regeneration = value;
	}
	 
	// ��������� �������� ����������� �� ������� �������� 
	virtual void Update() {
		if (m_current > 0 && m_current < m_maximum)
			Restore(m_regeneration);
	}

	virtual void SetCurrent(int value) {
		if (value < 0) value = 0;
		else if (value > m_maximum) value = m_maximum;
		m_current = value;
	}

	virtual ~Point() { }
};

class HitPoint : public Point {
public:
	HitPoint(uint max = 100, uint curr = 100, float regen = 0) : Point(max, curr, regen) { }
	virtual ~HitPoint() { }
};

class ManaPoint : public Point {
public:
	ManaPoint(uint max = 100, uint curr = 100, float regen = 0) : Point(max, curr, regen) { }
	virtual ~ManaPoint() { }
};

enum class TypeArmor : uint {
	CLOTH,	// �����
	LEATH,	// ����
	CHAIN,	// ��������
	PLATE,	// ����
	BUILD,	// ��������
};

class Armor : public B {
private:

	uint m_default;
	uint m_bonus;
	uint m_current;
	uint m_resistance = 0;
	TypeArmor m_type;

	static constexpr float m_factor_resistance = 0.06f;

public:

	Armor(
		const TypeArmor type = TypeArmor::CLOTH,
		const uint arm_default = 0,
		const uint arm_bonus = 0
	) 
		: m_type(type), m_default(arm_default), m_bonus(arm_bonus), m_current(m_default + m_bonus) {
		m_resistance = GetResistance();
	}

	// ���������� ������� ������������� ����������� �����
	float GetResistance(const uint level_factor = 1) {
		return 100.f * ((m_current * m_factor_resistance) / (level_factor + m_current * m_factor_resistance));
	}

	const TypeArmor& GetType() {
		return m_type;
	}

	void SetType(const TypeArmor type) {
		m_type = type;
	}

	void SetDefault(uint value) {
		m_default = value;
	}

	void SetBonus(uint value) {
		m_bonus = value;
	}

	void ResetCurrent() {
		m_current = ( m_default + m_bonus );
	}

	uint GetBonus() {
		return m_bonus;
	}

	uint GetCurrent() {
		return m_current;
	}

	uint GetDefault() {
		return m_default;
	}

	~Armor() {

	}
};

enum class TypeAttack : uint {
	MELEE,
	RANGE,
	NONE
};

enum class TypeDamage : uint {
	HAND,		// ����������
	CHOP,		// �������
	INCISIVE,	// �������
	ARROW,		// ������� ���
	MAGIC,		// ����������
	PURE		// ������
};

enum class TypeDamageModifier : uint {
	STANDART,	// ��� ���������� �������������
	FROSTSLOW,	// ���������� �������
	VAMPIRIC,	// ���������
	LIGHTING,	// ������
	NOMISS		// ����� ��� �������
};

class AutoAttack : public B
{
private:

	TypeDamageModifier m_type_damage_modifier = TypeDamageModifier::STANDART;	// ��� ������� ���������� �����
	TypeAttack m_type_attack;	// ��� �����
	TypeDamage m_type_damage;	// ��� ���������� �����

	float m_attack_distance; // ��������� �����
	uint m_damage_default;	 // ���� �� ��������� (�����)
	uint m_damage_bonus;	 // �������������� ����� (������)
	float m_attack_coldown;	 // 16.11.20 lxd25 ;)
	float m_attack_coldown_on_timer;	// ����������� ������ ����������� ��� ������� �������������� �����

	float m_missle_speed;	 // �������� ����� �������
	int m_damage_current;	 // ������� ���� (�����)
	bool m_is_attack_delay;	 // ������������� � ����� ������ ��������, ���������� ����� �������� �����

public:

	static constexpr float m_attack_coldown_min = 300; // ���������� ��������� ����� ����� �������

	AutoAttack(
		const TypeAttack attack_type = TypeAttack::NONE,
		const TypeDamage damage_type = TypeDamage::HAND,
		const TypeDamageModifier damage_modifier = TypeDamageModifier::STANDART,
		const float distance = 90,
		const uint dmg_default = 10,
		const uint dmg_bonus = 0,
		const float coldown = 1300,
		const float missle_speed = 900)
	{
		if (attack_type == TypeAttack::NONE) {
			m_attack_distance = 0;
			m_damage_default = 0;
			m_damage_bonus = 0;
			m_attack_coldown = 0;
			m_missle_speed = 0;
			m_is_attack_delay = false;
		}
		else {
			m_attack_distance = distance;
			m_damage_default = dmg_default;
			m_damage_bonus = dmg_bonus;
			m_attack_coldown = coldown;
			m_missle_speed = missle_speed;
			m_is_attack_delay = true;
		}
		m_type_attack = attack_type;
		m_type_damage = damage_type;
		m_damage_current = (m_damage_default + m_damage_bonus);
		m_type_damage_modifier = damage_modifier;
		m_attack_coldown_on_timer = m_attack_coldown;
	}

	~AutoAttack() {

	}

public: // Update Cooldwn

	void Update() {
		if (!m_is_attack_delay) {
			m_attack_coldown_on_timer -= time;
			if (m_attack_coldown_on_timer <= 0)
				m_is_attack_delay = true;
		}
	}

public: // Gets ...
	// ���������� true ���� ���� ����� ��������� ����-�����
	const bool& GetIsAttackDelay() {
		return m_is_attack_delay;
	}

	// ���������� ����� �� �����������
	const void Delay() {
		m_attack_coldown_on_timer = m_attack_coldown;
		m_is_attack_delay = false;
	}

	// ���������� ��� �����
	const TypeAttack& GetAttackType() {
		return m_type_attack;
	}
	// ���������� ��� ���������� �����
	const TypeDamage& GetDamageType() {
		return m_type_damage;
	}
	// ���������� ��� ������������ �����
	const TypeDamageModifier& GetDamageModifierType() {
		return m_type_damage_modifier;
	}
	// ���������� ���������� ���������� �������� �����
	const uint& GetDamageCurrent() {
		return m_damage_current;
	}
	// ���������� ���������� ���������� ����� �� ���������
	const uint& GetDamageDefault() {
		return m_damage_default;
	}
	// ���������� ���������� ��������� ����� (�� ���������, ������ � �.�.)
	const uint& GetDamageBonus() {
		return m_damage_bonus;
	}
	// ���������� ��������� ��������� �����
	const uint& GetAttackDistance() {
		return m_attack_distance;
	}
	// ���������� ����� �������� ����� �������
	const float& GetAttackColdown() {
		return m_attack_coldown;
	}
	// ���������� �������� ����� �������
	const float& GetMissleSpeed() {
		return m_missle_speed;
	}

public: // Sets ...

	// ������ ����������� ��������� ��������� ��� �� �������� ���������
	void FastAttackDelay() {
		m_is_attack_delay = true;
	}

	// ���������� ��� ����� TypeAttack::
	void SetAttackType(const TypeAttack type) {
		m_type_attack = type;
	}
	// ���������� ��� ����� TypeDamage::
	void SetDamageType(const TypeDamage type) {
		m_type_damage = type;
	}
	// ���������� ��� ����������� ����� TypeDamageModifier::
	void SetDamageModifierType(const TypeDamageModifier type) {
		m_type_damage_modifier = type;
	}
	// ���������� �������� �������� ���������� �����
	void SetDamageCurrent(const uint value) {
		m_damage_current = value;
	}
	// ���������� �������� ���������� ����� �� ���������
	void SetDamageDefault(const uint value) {
		m_damage_default = value;
	}
	// ���������� �������� ���������� ��������� �����
	void SetDamageBonus(const uint value) {
		m_damage_bonus = value;
	}
	// ���������� �������� ��������� ���������
	void SetAttackDistance(const uint value) {
		m_attack_distance = value;
	}
	// ���������� ����� �������� ����� �������
	void SetAttackColdown(const float value) {
		m_attack_coldown = value;
	}
	// ���������� �������� ����� �������
	void SetMissleSpeed(const float value) {
		m_missle_speed = value;
	}
};

class MovementSpeed : public B {
private:

	float m_default;
	float m_bonus;
	float m_current;
	static constexpr float m_maximum = 1.f;

public:

	MovementSpeed(const float default_value = 0.25, const float bonus_value = 0) {
		m_default = default_value;
		m_bonus = bonus_value;
		m_current = (m_default + m_bonus);
		if (m_current > m_maximum) m_current = m_maximum;
	}

	void SetDefault(const float value) {
		m_default = value;
	}

	void SetBonus(const float value) {
		m_bonus = value;
	}

	void ResetCurrent() {
		m_current = (m_default + m_current);
		if (m_current > m_maximum) m_current = m_maximum;
	}

	const float GetDefault() {
		return m_default;
	}

	const float GetBonus() {
		return m_bonus;
	}

	const float GetCurrent() {
		return m_current;
	}
	~MovementSpeed() {

	}
};