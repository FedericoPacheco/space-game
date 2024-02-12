#pragma once

#include <Windows.h>
#include "LivingEntity.h"

class Player : public LivingEntity
{
	public: 
		static const int maxLives = 6;
		static const int initialLives = 3;
		static const int maxHealthPoints = 125;
		static const int defaultDamage = 10;
		static const int maxShots = 25;
		static const int shotsCooldown = 60;

		static const int moveUp = 0x57;		// W 
		static const int moveDown = 0x53;	// S
		static const int moveLeft = 0x41;	// A
		static const int moveRight = 0x44;	// D
		static const int attack = VK_SPACE;	// Space

	private:
		int shotsLeft;
		int score;
		int lives;

	public:
		Player();
		void prepareForSpawning();
		void prepareForRespawning();
		void detectAction(Background* background);
		void increaseScore(int score);
		void decreaseLives();
		void handleShotsCooldown();
		Shot shoot() override;
		void decreaseShotsLeft();
		void restoreShots();
		void restoreHealth(int healthRestored);
		
		bool canShoot();
		R2Vector getAimingDirection();
		int getHealthPoints();
		int getScore();
		int getShotsLeft();
		int getLives();
	
	private:
		void initializeBody();
};
