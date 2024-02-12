#include "Pixel.h"

//public

Pixel::Pixel()
{
	ch = ' ';
	backgroundColor = Pixel::black;
	chColor = Pixel::black;
}

void Pixel::print()
{
	goToXY(positionVector.getX(), positionVector.getY());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * backgroundColor + chColor);
	cout << ch;	
}

void Pixel::setPositionVector(R2Vector positionVector)
{
	this->positionVector = positionVector;
}

void Pixel::setCh(char ch)
{
	this->ch = ch; 
}

void Pixel::setChColor(int color)
{
	chColor = color;
}

void Pixel::setBackgroundColor(int color)
{
	backgroundColor = color;
}

R2Vector Pixel::getPositionVector()
{
	return positionVector;
}

void Pixel::goToXY(int x, int y)
{
	COORD cp = {(short) x, (short) y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cp);
}



