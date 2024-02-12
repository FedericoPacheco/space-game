#pragma once

#include "LivingEntity.h"
#include "Player.h"
#include "Pixel.h"
#include "cstdlib"

class Enemy : public LivingEntity
{
	public: 
		static const int maxHealthPoints = 50;
		static const int defaultDamage = 5;
		static const int defaultScoreGiven = 50;
		
	private:
		int scoreGiven;

	public:
		Enemy(R2Vector positionVector);
		bool wantsToShoot(Player player);
		void move(Player player, Background* background);
		int getScore();
		Shot shoot() override;
};
