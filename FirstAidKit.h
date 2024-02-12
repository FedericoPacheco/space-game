#pragma once
#include "Entity.h"

class FirstAidKit : public Entity
{
	public:
		static const int defaultHealthRestored = 35;

	private:
		int healthRestored;

	public:
		FirstAidKit(R2Vector positionVector);
		int getHealthRestored();
};