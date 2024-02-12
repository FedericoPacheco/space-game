#include "Shot.h"

Shot::Shot() { }

Shot::Shot(char shotCh, bool isFromPlayer, int damage, R2Vector directionVector, R2Vector positionVector)
{
	this->damage = damage;
	this->directionVector = directionVector;
	firstMovement = true;

	Pixel auxPixel;

	auxPixel.setPositionVector(positionVector);
	auxPixel.setCh(shotCh);
	auxPixel.setBackgroundColor(Pixel::black);

	if (isFromPlayer)
		auxPixel.setChColor(Pixel::lightBlue);
	else
		auxPixel.setChColor(Pixel::lightRed);

	body.push_back(auxPixel);
}

void Shot::move(Background* background)
{
	static R2Vector positionVector;

	if (firstMovement)   // not that good fix for the shot first printing
	{
		positionVector = body.at(0).getPositionVector();
		firstMovement = false;
	}
	else 
		positionVector = body.at(0).getPositionVector() + directionVector; // a shot only has one pixel

	printSpaceBehind(background);
	body.at(0).setPositionVector(positionVector);	
	//if (!Background::outOfBounds(positionVector))
	print();
}
