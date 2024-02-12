#include "Enemy.h"

Enemy::Enemy(R2Vector positionVector)
{
	healthPoints = maxHealthPoints;
	damage = defaultDamage;
	scoreGiven = defaultScoreGiven;

	Pixel auxPixel;
	R2Vector auxVector;

	auxPixel.setPositionVector(positionVector + R2Vector(-1, 0));
	auxPixel.setCh(char(verticalBoxDrawingCh));    
	auxPixel.setChColor(Pixel::red);
	auxPixel.setBackgroundColor(Pixel::black);
	body.push_back(auxPixel);

	auxPixel.setPositionVector(positionVector + R2Vector());
	auxPixel.setCh('^');                      
	auxPixel.setChColor(Pixel::lightRed);
	body.push_back(auxPixel);

	auxPixel.setPositionVector(positionVector + R2Vector(1, 0));
	auxPixel.setCh(char(verticalBoxDrawingCh));    
	auxPixel.setChColor(Pixel::red);
	body.push_back(auxPixel);
}

bool Enemy::wantsToShoot(Player player)
{
	static R2Vector playerPositionVector, enemyPositionVector;
	static int c, r, R = 8;

	playerPositionVector = player.getBody().at(1).getPositionVector();
	enemyPositionVector = body.at(1).getPositionVector();

	if (putVertically)
	{
		c = enemyPositionVector.getX();
		r = playerPositionVector.getX();
	}
	else
	{
		c = enemyPositionVector.getY();
		r = playerPositionVector.getY();
	}

	if (abs(c - r) < R)
		willShoot = (rand() % 100) > 65; // increased chances of shooting if the player is moving near the enemy
	else
		willShoot = (rand() % 100) > 99;

	return LivingEntity::wantsToShoot();
}

void Enemy::move(Player player, Background* background)
{
	static R2Vector playerPositionVector, enemyPositionVector;
	static int auxInt, deltaX, deltaY;
	static int keepDirectionVectorCounter = 0;

	playerPositionVector = player.getBody().at(1).getPositionVector();
	enemyPositionVector = body.at(1).getPositionVector();
	deltaX = playerPositionVector.getX() - enemyPositionVector.getX();
	deltaY = playerPositionVector.getY() - enemyPositionVector.getY();

	if (keepDirectionVectorCounter > 0)
		keepDirectionVectorCounter--;   // maintain previous directionVector
	else
	{
		auxInt = rand() % 100;  
		if (auxInt < 20)         // 20% chance of approaching the player
		{
			directionVector.setXY(deltaX, deltaY);
			directionVector.pseudoNormalize();

			keepDirectionVectorCounter = 0; // do it only once
		}
		else
		{
			keepDirectionVectorCounter = rand() % 3 + 1;

			if (auxInt < 80)
				directionVector = player.getAimingDirection().orthogonalVector() * (int) pow(-1, rand() % 2);   // move sideways with respect to player
			else
				directionVector.setXY(0, 0);   // stay in place
		}
	}

	if (abs(deltaY) > abs(deltaX))   // aim to the player
	{
		if (playerPositionVector.getY() < enemyPositionVector.getY())
			point(up, background);
		else
			point(down, background);
	}
	else
	{
		if (playerPositionVector.getX() > enemyPositionVector.getX())
			point(right, background);
		else
			point(left, background);
	}
	
	LivingEntity::move(background);
}

int Enemy::getScore()
{
	return scoreGiven;
}

Shot Enemy::shoot()
{
	static char auxCh;

	if (putVertically)
		auxCh = char(Shot::horizontalShot);
	else
		auxCh = char(Shot::verticalShot);

	return
		Shot(auxCh, false, damage, aimingDirection, aimingDirection + body.at(1).getPositionVector());
}