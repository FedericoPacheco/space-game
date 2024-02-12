#include "LivingEntity.h"

LivingEntity::LivingEntity()
{
	putVertically = false;
}

void LivingEntity::move(Background* background)
{
	printSpaceBehind(background);
	if (!bodyWillBeOutOfBounds())
	{
		for (auto i = body.begin(); i != body.end(); i++)
			i->setPositionVector(i->getPositionVector() + directionVector);
	}
	print();
}

bool LivingEntity::isAlive()
{
	return (healthPoints > 0);
}

void LivingEntity::takeDamage(int damage)
{
	healthPoints -= damage;
}

void LivingEntity::point(Orientation o, Background* background)
{
	static vector <Pixel> bodyCopy;

	bodyCopy = body;
	printSpaceBehind(background);

	if (o == left)
		setBodyVertically('<');
	else if (o == right)
		setBodyVertically('>');
	else if (o == up)
		setBodyHorizontally('^');
	else if (o == down)
		setBodyHorizontally('v');

	if (!bodyWillBeOutOfBounds())   // only the body that isn't out of bounds after rotated is allowed
	{
		if (o == left)
			aimingDirection.setXY(-1, 0);
		else if (o == right)
			aimingDirection.setXY(1, 0);
		else if (o == up)
			aimingDirection.setXY(0, -1);
		else if (o == down)
			aimingDirection.setXY(0, 1);
	}
	else
		body = bodyCopy;
}

void LivingEntity::setBodyHorizontally(char directionCh)
{
	putVertically = false;
	
	body.at(0).setCh(char(verticalBoxDrawingCh));
	body.at(0).setPositionVector(body.at(1).getPositionVector() + R2Vector(1, 0));

	body.at(1).setCh(directionCh);

	body.at(2).setCh(char(verticalBoxDrawingCh));
	body.at(2).setPositionVector(body.at(1).getPositionVector() + R2Vector(-1, 0));
}

void LivingEntity::setBodyVertically(char directionCh)
{
	putVertically = true;
	
	body.at(0).setCh(char(horizontalBoxDrawingCh));
	body.at(0).setPositionVector(body.at(1).getPositionVector() + R2Vector(0, 1));

	body.at(1).setCh(directionCh);
	
	body.at(2).setCh(char(horizontalBoxDrawingCh));
	body.at(2).setPositionVector(body.at(1).getPositionVector() + R2Vector(0, -1));
}

Shot LivingEntity::shoot()
{
	return Shot();
}

bool LivingEntity::wantsToShoot()
{
	return willShoot;
}


