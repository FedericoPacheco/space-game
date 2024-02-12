#include "R2Vector.h"

R2Vector::R2Vector()
{
	x = 0;
	y = 0;
}

R2Vector::R2Vector(int x, int y)
{
	this->x = x;
	this->y = y;
}

R2Vector R2Vector::operator+(R2Vector other)
{
	return R2Vector(x + other.x, y + other.y);
}

R2Vector R2Vector::operator*(int scalar)
{
	return R2Vector(scalar * x, scalar * y);
}

R2Vector R2Vector::orthogonalVector()
{
	return R2Vector(y, -x);
}

bool R2Vector::operator==(R2Vector other)
{
	return (x == other.x && y == other.y);
}

int R2Vector::getX()
{
	return x;
}

int R2Vector::getY()
{
	return y;
}

void  R2Vector::setXY(int x, int y)
{
	this->x = x;
	this->y = y;
}

void R2Vector::pseudoNormalize()   // can't really do u = v / ||v||, the components are integers
{
	if (x < 0)
		x = -1;
	else if (x > 0)
		x = 1;

	if (y < 0)
		y = -1;
	else if (y > 0)
		y = 1;
}


