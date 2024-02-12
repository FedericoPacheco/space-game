#include "Player.h"

Player::Player()
{
	for (int i = 0; i < 3; i++)
		body.push_back(Pixel());
	prepareForSpawning();
}

void Player::prepareForSpawning()
{
	score = 0;
	lives = initialLives;
	shotsLeft = maxShots;
	healthPoints = maxHealthPoints;
	damage = defaultDamage;
	aimingDirection.setXY(0, -1);
	initializeBody();
}

void Player::prepareForRespawning()
{
	shotsLeft = maxShots;
	healthPoints = maxHealthPoints;
	aimingDirection.setXY(0, -1);
	initializeBody();
}

void Player::initializeBody()
{
	static R2Vector auxVector;
	
	auxVector.setXY(Background::width / 2 - 1, Background::spaceHeight / 2);
	body.at(0).setPositionVector(auxVector);
	body.at(0).setCh(char(verticalBoxDrawingCh));
	body.at(0).setChColor(Pixel::blue);
	body.at(0).setBackgroundColor(Pixel::black);

	auxVector.setXY(Background::width / 2, Background::spaceHeight / 2);
	body.at(1).setPositionVector(auxVector);
	body.at(1).setCh('^');
	body.at(1).setChColor(Pixel::lightBlue);
	body.at(1).setBackgroundColor(Pixel::black);

	auxVector.setXY(Background::width / 2 + 1, Background::spaceHeight / 2);
	body.at(2).setPositionVector(auxVector);
	body.at(2).setCh(char(verticalBoxDrawingCh));
	body.at(2).setChColor(Pixel::blue);
	body.at(2).setBackgroundColor(Pixel::black);
}

R2Vector Player::getAimingDirection()
{
	return aimingDirection;
}

void Player::restoreHealth(int healthRestored)
{
	static int auxInt;

	auxInt = healthPoints + healthRestored;
	if (auxInt >= 2 * maxHealthPoints)
		if (lives == maxLives)
			healthPoints = 2 * maxHealthPoints;
		else
		{
			healthPoints = maxHealthPoints;
			lives++;
		}
	else
		healthPoints = auxInt;
}

void Player::detectAction(Background* background)
{
	directionVector.setXY(0, 0);
	willShoot = false;
	
	if (GetAsyncKeyState(attack))
		willShoot = true;
	
	if (GetAsyncKeyState(moveUp))
	{
		directionVector = directionVector + R2Vector(0, -1);
		point(up, background);
	}
	if (GetAsyncKeyState(moveDown))
	{
		directionVector = directionVector + R2Vector(0, 1);
		point(down, background);
	}
	if (GetAsyncKeyState(moveLeft))
	{
		directionVector = directionVector + R2Vector(-1, 0);
		point(left, background);
	}
	if (GetAsyncKeyState(moveRight))
	{
		directionVector = directionVector + R2Vector(1, 0);
		point(right, background);
	}
}

Shot Player::shoot()
{
	static char auxCh;

	if (putVertically)
		auxCh = char(Shot::horizontalShot);
	else
		auxCh = char(Shot::verticalShot);

	return
		Shot(auxCh, true, damage, aimingDirection, aimingDirection + body.at(1).getPositionVector());
}

void Player::increaseScore(int score)
{
	this -> score += score;
}

void Player::decreaseLives()
{
	lives -= 1;
}

int Player::getLives()
{
	return lives;
}

void Player::decreaseShotsLeft()
{
	shotsLeft--;
}

int Player::getShotsLeft()
{
	return shotsLeft;
}

void Player::restoreShots()
{
	shotsLeft = maxShots;
}

bool Player::canShoot()
{
	return (shotsLeft > 0);
}

int Player::getHealthPoints()
{
	return healthPoints;
}

int Player::getScore()
{
	return score;
}

void Player::handleShotsCooldown()
{
	static int shotsCooldown = Player::shotsCooldown;
	
	if (shotsCooldown == 0)
	{
		shotsLeft = maxShots;
		shotsCooldown = Player::shotsCooldown;
	}
	else
		shotsCooldown--;
}