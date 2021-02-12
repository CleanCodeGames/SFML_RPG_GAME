#pragma once
#include "oHero.h"

class HeroMage : public oHero
{
private:

protected:

public:

	HeroMage(
		const v2f position,
		const PC player_controll = PC::P_NEUTRALL,
		const TypeHero type_hero = TypeHero::MAGE
	)
		: oHero(position, player_controll, type_hero)
	{

	}

	virtual ~HeroMage() {

	}
};