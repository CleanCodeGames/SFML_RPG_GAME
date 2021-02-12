#pragma once
#include "oUnit.h"
#include "Orders.h"

class oAbility
{
protected:

	string m_name;
	string m_description;
	uint m_level = 1;
	uint m_level_max = 1;

public:

	oAbility() {

	}

	virtual void SetLevel(const uint value) {
		m_level = value;
	}

	virtual void SetLevelMax(uint value) {
		m_level_max = value;
	}

	virtual const string& GetName() {
		return m_name;
	}

	virtual const string& GetDescription() {
		return m_description;
	}

	virtual void Update() {

	}

	virtual ~oAbility() {

	}
};