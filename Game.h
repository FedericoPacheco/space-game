#pragma once

#include <cstdlib>
#include <conio.h>
#include <list>
#include <Windows.h>
#include "Background.h"
#include "Enemy.h"
#include "Player.h"
#include "FirstAidKit.h"

class Game
{
	public:
		static const int gameDelay = 25;//50;
		static const int deathDelay = 2000;

		static constexpr double initialLikelihoodOfSpawningAnEnemy = 0.5;
		static constexpr double likelihoodOfSpawningAnEnemyIncrement = 0.0001;

		static constexpr double initialLikelihoodOfSpawningAFirstAidKit = 0.15;
		static constexpr double likelihoodOfSpawningFirstAidKitIncrement = 0.0001;
		
	private: 
		Player player;
		list <Enemy> enemies;
		list <Shot> playerShots;
		list <Shot> enemyShots;
		list <FirstAidKit> firstAidKits;
		Background* background;
		double likelihoodOfSpawningAnEnemy;
		double likelihoodOfSpawningAFirstAidKit;

	public:
		Game();
		~Game();
		void initialScreen();
		bool gameLoop();

	private:
		void clearEnemiesAndShots();
		void handlePlayer();
		void handleEnemies();
		void handleShots();
		void handleFirstAidKits();
		void handlePlayerRespawn();
		void handleShotsMovement(list <Shot>& shots);
		void handleShotCollisions();
		void handleGameInterface();
		bool testCollision(Entity entity1, Entity entity2);
		bool gameIsOver();
		void spawnEnemy();
		void spawnFirstAidKit();
		bool retryScreen();
		bool decideToSpawn(double likelihoodOfSpawning);
};
