#include "FirstAidKit.h"

FirstAidKit::FirstAidKit(R2Vector positionVector)
{
	damage = 0;
	healthRestored = defaultHealthRestored;
	directionVector = R2Vector(0, 0); // not really meaningful

	Pixel auxPixel;
	R2Vector auxVector;

	auxPixel.setPositionVector(positionVector + R2Vector(-1, 0));
	auxPixel.setCh(char(verticalBoxDrawingCh));
	auxPixel.setChColor(Pixel::white);
	auxPixel.setBackgroundColor(Pixel::black);
	body.push_back(auxPixel);

	auxPixel.setPositionVector(positionVector + R2Vector());
	auxPixel.setCh('+');
	auxPixel.setChColor(Pixel::red);
	auxPixel.setBackgroundColor(Pixel::white);
	body.push_back(auxPixel);

	auxPixel.setPositionVector(positionVector + R2Vector(1, 0));
	auxPixel.setCh(char(verticalBoxDrawingCh));
	auxPixel.setChColor(Pixel::white);
	auxPixel.setBackgroundColor(Pixel::black);
	body.push_back(auxPixel);
}

int FirstAidKit::getHealthRestored()
{
	return healthRestored;
}