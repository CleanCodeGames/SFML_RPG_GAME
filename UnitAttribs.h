#pragma once
#include "Base.h"
// static sf::Text text_hit(mana)_point для отображения в интерфейсе при клике на юнита
class Point 
{
protected:
	
	uint m_maximum;			// Максимальное : Наример 500/500 ед.
	int m_current;			// Текущее : Например 376/500
	float m_regeneration;	// ** Регенерация : Срабатывает 4 раза в секунду

public:

	Point(uint max = 100, uint curr = 100, float regen = 0) {
		m_maximum = max;
		m_current = curr;
		m_regeneration = regen;
	}

	// Задать указанный максимум и подогнать значение текущего в процентном соотношении
	// Если указать is_current_full, то значение текущего станет полным
	virtual void SetMax(uint value, bool is_current_full = false) {
		m_maximum = value;
		const int current = m_current;
		is_current_full ? m_current = m_maximum : m_current = (current / 100) * (m_maximum / 100) * 100;
	}

	// Мгновенное восстановление
	virtual void Restore(const uint value) {
		m_current += value;
		if (m_current > m_maximum) {
			m_current = m_maximum;
		}
	}

	virtual void SetRegeneration(float value) {
		m_regeneration = value;
	}
	 
	// Обновлять таймером регенерации из игровых констант 
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
	CLOTH,	// Ткань
	LEATH,	// Кожа
	CHAIN,	// Кольчуга
	PLATE,	// Латы
	BUILD,	// Строение
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

	// Возвращает процент сопротивления получаемого урона
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
	HAND,		// Рукопашный
	CHOP,		// Рубящий
	INCISIVE,	// Режущий
	ARROW,		// Дальний бой
	MAGIC,		// Магический
	PURE		// Чистый
};

enum class TypeDamageModifier : uint {
	STANDART,	// Без уникальных модификаторов
	FROSTSLOW,	// Замедление холодом
	VAMPIRIC,	// Вампиризм
	LIGHTING,	// Молния
	NOMISS		// Атаки без промаха
};

class AutoAttack : public B
{
private:

	TypeDamageModifier m_type_damage_modifier = TypeDamageModifier::STANDART;	// Тип эффекта наносимого урона
	TypeAttack m_type_attack;	// Тип атаки
	TypeDamage m_type_damage;	// Тип наносимого урона

	float m_attack_distance; // Дальность атаки
	uint m_damage_default;	 // Урон по умолчанию (Белая)
	uint m_damage_bonus;	 // Дополнительная атака (Зелёная)
	float m_attack_coldown;	 // 16.11.20 lxd25 ;)
	float m_attack_coldown_on_timer;	// Действующий таймер перезарядки для отсчёта задействования атаки

	float m_missle_speed;	 // Скорость полёта снаряда
	int m_damage_current;	 // Текущий урон (Всего)
	bool m_is_attack_delay;	 // Перезарядился и готов начать действия, вызывающие атаку текущего юнита

public:

	static constexpr float m_attack_coldown_min = 300; // Минимально возможная пауза между атаками

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
	// Возвращает true если юнит готов совершить авто-атаку
	const bool& GetIsAttackDelay() {
		return m_is_attack_delay;
	}

	// Отправляет атаку на перезарядку
	const void Delay() {
		m_attack_coldown_on_timer = m_attack_coldown;
		m_is_attack_delay = false;
	}

	// Возвращает тип атаки
	const TypeAttack& GetAttackType() {
		return m_type_attack;
	}
	// Возвращает тип наносимого урона
	const TypeDamage& GetDamageType() {
		return m_type_damage;
	}
	// Возвращает тип модификатора атаки
	const TypeDamageModifier& GetDamageModifierType() {
		return m_type_damage_modifier;
	}
	// Возвращает количество наносимого текущего урона
	const uint& GetDamageCurrent() {
		return m_damage_current;
	}
	// Возвращает количество наносимого урона по умолчанию
	const uint& GetDamageDefault() {
		return m_damage_default;
	}
	// Возвращает количество бонусного урона (от предметов, баффов и т.д.)
	const uint& GetDamageBonus() {
		return m_damage_bonus;
	}
	// Возвращает дистанцию нанесения атаки
	const uint& GetAttackDistance() {
		return m_attack_distance;
	}
	// Возвращает время задержки между атаками
	const float& GetAttackColdown() {
		return m_attack_coldown;
	}
	// Возвращает скорость полёта снаряда
	const float& GetMissleSpeed() {
		return m_missle_speed;
	}

public: // Sets ...

	// Делает возможность сотворить автоатаку без кд повторно мгновенно
	void FastAttackDelay() {
		m_is_attack_delay = true;
	}

	// Установить тип атаки TypeAttack::
	void SetAttackType(const TypeAttack type) {
		m_type_attack = type;
	}
	// Установить тип урона TypeDamage::
	void SetDamageType(const TypeDamage type) {
		m_type_damage = type;
	}
	// Установить тип модификатор урона TypeDamageModifier::
	void SetDamageModifierType(const TypeDamageModifier type) {
		m_type_damage_modifier = type;
	}
	// Установить значение текущего наносимого урона
	void SetDamageCurrent(const uint value) {
		m_damage_current = value;
	}
	// Установить значение наносимого урона по умолчанию
	void SetDamageDefault(const uint value) {
		m_damage_default = value;
	}
	// Установить значение наносимого бонусного урона
	void SetDamageBonus(const uint value) {
		m_damage_bonus = value;
	}
	// Установить значение дальности автоатаки
	void SetAttackDistance(const uint value) {
		m_attack_distance = value;
	}
	// Установить время задержки между атаками
	void SetAttackColdown(const float value) {
		m_attack_coldown = value;
	}
	// Установить скорость полёта снаряда
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