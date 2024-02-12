#include "Game.h"

Game::Game()
{
	background = new Background;
	likelihoodOfSpawningAnEnemy = initialLikelihoodOfSpawningAnEnemy;
	likelihoodOfSpawningAFirstAidKit = initialLikelihoodOfSpawningAFirstAidKit;
}

Game::~Game()
{
	delete background;
}

void Game::initialScreen()
{
	string auxStr = "Press any key to start";
	char auxCh;
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * Pixel::black + Pixel::white);
	Pixel::goToXY(Background::width / 2 - (int) auxStr.length() / 2, Background::spaceHeight / 2); 
	cout << auxStr;
	auxCh = _getch();    // not really useful
}

bool Game::gameLoop()
{
	background->printSpace();

	while (player.getLives() > 0)
	{
		handleGameInterface();
		handlePlayer();
		handleEnemies();
		handleShots();
		handleFirstAidKits();
	
		if (!player.isAlive())
			handlePlayerRespawn();
			
		likelihoodOfSpawningAnEnemy += likelihoodOfSpawningAnEnemyIncrement;
		likelihoodOfSpawningAFirstAidKit += likelihoodOfSpawningFirstAidKitIncrement;
		
		Sleep(gameDelay);
	}

	return retryScreen();
}

void Game::handleGameInterface()
{
	background->setPlayerInformation
	(
		player.getHealthPoints(),
		Player::maxHealthPoints,
		player.getLives(),
		Player::maxLives,
		player.getShotsLeft(),
		Player::maxShots,
		player.getScore()
	);

	background->printInterface();
}

void Game::handlePlayer()
{
	static Shot auxShot;
	
	player.detectAction(background);
	player.move(background);
	player.handleShotsCooldown();
	if (player.wantsToShoot() && player.canShoot())
	{
		auxShot = player.shoot();
		if (!auxShot.bodyOutOfBounds())
		{
			playerShots.push_back(auxShot);
			player.decreaseShotsLeft();
		}
	}
}

void Game::handleEnemies()
{
	static Shot auxShot;
	
	for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
	{
		enemy -> move(player, background);
		if (enemy -> wantsToShoot(player))
		{
			auxShot = enemy -> shoot();
			if (!auxShot.bodyOutOfBounds())
				enemyShots.push_back(auxShot);
		}
	}

	
	if (decideToSpawn(likelihoodOfSpawningAnEnemy))
		spawnEnemy();
}

void Game::handleShots()
{
	handleShotsMovement(playerShots);
	handleShotsMovement(enemyShots);
	handleShotCollisions();
}

void Game::handleShotsMovement(list <Shot>& shots)
{
	auto shot = shots.begin();
	while (shot != shots.end())
	{
		shot->move(background);

		if (shot -> bodyOutOfBounds())
			shot = shots.erase(shot);
		else
			shot++;
	}
}

void Game::handleShotCollisions()    
{
	// https://stackoverflow.com/questions/16269696/erasing-while-iterating-an-stdlist
	
	static bool collisionProduced;

	// enemies and player shots
	auto enemy = enemies.begin();
	while (enemy != enemies.end())
	{
		collisionProduced = false;
		auto playerShot = playerShots.begin();
		while (playerShot != playerShots.end() && !collisionProduced)
		{
			collisionProduced = testCollision(*enemy, *playerShot);
			if (collisionProduced)
			{
				enemy -> takeDamage(playerShot -> getDamage());
				playerShot = playerShots.erase(playerShot);
			}
			else 
				playerShot++;
		}

		if (!(enemy->isAlive()))
		{
			player.increaseScore(enemy->getScore());
			enemy->disappear();
			enemy = enemies.erase(enemy);
		}
		else
			enemy++;
	}

	// player and enemy shots
	collisionProduced = false;
	auto enemyShot = enemyShots.begin();
	while (enemyShot != enemyShots.end() && !collisionProduced)
	{
		collisionProduced = testCollision(player, *enemyShot);
		if (collisionProduced)
		{
			player.takeDamage(enemyShot -> getDamage());
			enemyShot = enemyShots.erase(enemyShot);
		}
		else
			enemyShot++;
	}
}

bool Game::testCollision(Entity entity1, Entity entity2)
{
	// https://docs.microsoft.com/en-us/cpp/code-quality/c26815?view=msvc-160
	
	static bool collisionProduced;
	static vector <Pixel> entity1Body, entity2Body;

	entity1Body = entity1.getBody();
	entity2Body = entity2.getBody();

	auto i = entity1Body.begin();
	collisionProduced = false;
	while (i != entity1Body.end() && !collisionProduced)
	{
		auto j = entity2Body.begin();
		while (j != entity2Body.end() && !collisionProduced)
			if (i -> getPositionVector() == j -> getPositionVector())
				collisionProduced = true;
			else
				j++;
		
		i++;
	}

	return collisionProduced;
}

void Game::handlePlayerRespawn()
{
	player.disappear();
	Sleep(deathDelay);
	player.decreaseLives();
	player.prepareForRespawning();
}

void Game::handleFirstAidKits()
{
	auto kit = firstAidKits.begin();
	while (kit != firstAidKits.end())      // test collisions between player and first aid kits
		if (testCollision(player, *kit))
		{
			player.restoreHealth(kit->getHealthRestored());
			kit->printSpaceBehind(background);
			kit = firstAidKits.erase(kit);
		}
		else
			kit++;
	
	for (kit = firstAidKits.begin(); kit != firstAidKits.end(); kit++)    // print them
		kit -> print();

	if (decideToSpawn(likelihoodOfSpawningAFirstAidKit))    // maybe spawn one more
		spawnFirstAidKit();
}

bool Game::gameIsOver()
{
	return (player.getLives() <= 0);
}

void Game::spawnEnemy()
{
	static R2Vector auxVector;
	
	auxVector.setXY(rand() % Background::width, rand() % Background::spaceHeight);
	enemies.push_back(Enemy(auxVector));
}

void Game::spawnFirstAidKit()
{
	static R2Vector auxVector;

	auxVector.setXY(rand() % Background::width, rand() % Background::spaceHeight);
	firstAidKits.push_back(FirstAidKit(auxVector));
}

bool Game::retryScreen()
{
	string auxStr;
	char auxCh;
	bool loop, continuePlaying;

	system("cls");
		
	// cheap way of displaying "game over" without having to add another background to the class Background (with the methods asociated)
	auxStr = "GAME OVER";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * Pixel::black + Pixel::red);
	Pixel::goToXY(Background::width / 2 - (int) auxStr.length() / 2, Background::spaceHeight / 2);
	cout << auxStr;

	auxStr = "Retry? ( Y / N )";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * Pixel::black + Pixel::white);
	Pixel::goToXY(Background::width / 2 - (int) auxStr.length() / 2, Background::spaceHeight / 2 + 2);
	cout << auxStr;

	continuePlaying = false;
	loop = true;
	while(loop)
	{
		auxCh = _getch();

		if (auxCh == 'y' || auxCh == 'Y')
		{
			loop = false;
			player.prepareForSpawning();
			clearEnemiesAndShots();
			continuePlaying = true;
		}
		else if (auxCh == 'n' || auxCh == 'N')
		{
			loop = false;
			continuePlaying = false;
		}
	}

	return continuePlaying;
}

void Game::clearEnemiesAndShots()
{
	playerShots.clear();
	enemyShots.clear();
	enemies.clear();
}

bool Game::decideToSpawn(double likelihoodOfSpawning)
{
	if ((rand() % 10001) / 100.0 < likelihoodOfSpawning)
		return true;
	else
		return false;
}


