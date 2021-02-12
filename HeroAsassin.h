#pragma once
#include "oHero.h"

class HeroAsassin : public oHero
{
private:

protected:

public:

	HeroAsassin(
		const v2f position,
		const PC player_controll = PC::P_NEUTRALL,
		const TypeHero type_hero = TypeHero::ASASSIN
	)
		: oHero(position, player_controll, type_hero)
	{

	}

	virtual ~HeroAsassin() {

	}
};