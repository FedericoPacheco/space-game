#include "Entity.h"

void Entity::disappear()
{
	for (auto i = body.begin(); i != body.end(); i++)
	{
		i -> setCh(' ');
		i -> setChColor(Pixel::black);
		i -> print();
	}
}

bool Entity::bodyOutOfBounds()
{
	static bool outOfBounds;

	outOfBounds = false;
	auto i = body.begin();
	while (i != body.end() && !outOfBounds)
	{
		outOfBounds = Background::outOfBounds(i -> getPositionVector());
		i++;
	}

	return outOfBounds;
}

bool Entity::bodyWillBeOutOfBounds()
{
	static bool outOfBounds;

	outOfBounds = false;
	auto i = body.begin();
	while (i != body.end() && !outOfBounds)
	{
		outOfBounds = Background::outOfBounds(i -> getPositionVector() + directionVector);
		i++;
	}

	return outOfBounds;
}

void Entity::move(Background* background)
{
	// subclass responsability
}

void Entity::printSpaceBehind(Background* background)
{
	for (auto i = body.begin(); i != body.end(); i++)
		(background -> getSpacePixel(i -> getPositionVector())).print();
}

void Entity::print()
{
	for (auto i = body.begin(); i != body.end(); i++)
		if (!Background::outOfBounds(i -> getPositionVector()))
			i -> print();
}

int Entity::getDamage()
{
	return damage;
}

vector <Pixel> Entity::getBody()
{
	return body;
}