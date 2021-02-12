#pragma once
#include "oHero.h"

class HeroWarior : public oHero
{
private:

protected:

public:

	HeroWarior(
		const v2f position,
		const PC player_controll = PC::P_NEUTRALL,
		const TypeHero type_hero = TypeHero::WARIOR
	) 
		: oHero(position, player_controll, type_hero)
	{

	}

	virtual ~HeroWarior() {

	}
};