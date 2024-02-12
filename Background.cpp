#include "Background.h"

Background::Background()
{
	setConsoleSize();
	initializeSpace();
	initializeInterface();
}

void Background::setConsoleSize()
{
	// cols = width , lines = spaceHeight + interfaceHeight
	system("mode con: cols=120 lines=40"); 
}

void Background::initializeSpace()
{
	static int i, j, k;
	static int randI, randJ;

	for (i = 0; i < spaceHeight; i++)
	{
		for (j = 0; j < width; j++)
		{
			space[i][j].setPositionVector(R2Vector(j, i));
			space[i][j].setCh(' ');
			space[i][j].setChColor(Pixel::red);
			space[i][j].setBackgroundColor(Pixel::black);
		}
	}

	srand((int) time(nullptr));
	for (k = 0; k < amountOfStarsInSpace; k++)
	{
		randI = rand() % spaceHeight;
		randJ = rand() % width;

		space[randI][randJ].setCh(stars[rand() % amountOfStarTypes]);
		space[randI][randJ].setChColor(starColors[rand() % amountOfColors]);
	}
}

void Background::printSpace()
{
	static int i, j;

	for (i = 0; i < spaceHeight; i++)
		for (j = 0; j < width; j++)
			space[i][j].print();
}

void Background::printInterface()
{
	static int i, j;

	for (i = 0; i < interfaceHeight; i++)
		for (j = 0; j < width; j++)
			gameInterface[i][j].print();
}

Pixel Background::getSpacePixel(R2Vector positionVector)
{
	return space[positionVector.getY()][positionVector.getX()];
}

bool Background::outOfBounds(R2Vector positionVector)
{
	static int x, y;
	
	x = positionVector.getX();
	y = positionVector.getY();
	
	return 
		(
			(x < 0)				||
			(x >= width)		||
			(y < 0)				||
			(y >= spaceHeight)
		);
}

void Background::setText(string text, int textColor, int backgroundColor, R2Vector initialPosition) 
{
	static int i, j;

	for (j = 0, i = initialPosition.getX(); i < initialPosition.getX() + text.length(); i++, j++)
	{
		gameInterface[initialPosition.getY()][initialPosition.getX() + j].setCh(text.at(j));
		gameInterface[initialPosition.getY()][initialPosition.getX() + j].setChColor(textColor);
		gameInterface[initialPosition.getY()][initialPosition.getX() + j].setBackgroundColor(backgroundColor);
	}
}

void Background::initializeInterface()
{
	static int i, j;

	// general position vector and background/ch color initialization
	for (i = 0; i < interfaceHeight; i++)
	{
		for (j = 0; j < width; j++)
		{
			gameInterface[i][j].setPositionVector(R2Vector(j, i + spaceHeight));
			gameInterface[i][j].setBackgroundColor(Pixel::black);
			gameInterface[i][j].setChColor(Pixel::lightBlue);
			gameInterface[i][j].setCh(' ');
		}
	}

	// upper left corner
	gameInterface[0][0].setCh(char(201));

	// upper horizontal line
	for (j = 1; j < width - 1; j++)
		gameInterface[0][j].setCh(char(205));

	// upper right corner
	gameInterface[0][width - 1].setCh(char(187));

	// left vertical line
 	gameInterface[1][0].setCh(char(186));
	gameInterface[2][0].setCh(char(186));

	// lower left corner
	gameInterface[3][0].setCh(char(200));

	// lower right corner
	gameInterface[3][width - 1].setCh(char(188));

	// right vertical line
	gameInterface[1][width - 1].setCh(char(186));
	gameInterface[2][width - 1].setCh(char(186));

	// lower horizontal line
	for (j = 1; j < width - 1; j++)
		gameInterface[3][j].setCh(char(205));
}

void Background::setPlayerInformation(int currentHealthPoints, int maxHealthPoints, int currentLives, int maxLives, int currentShotsAvailable, int maxShotsAvailable, int score)
{
	static int i, x, auxInt;
	static string auxStr;
	
	// health points
	x = 2;
	setText("HP", Pixel::white, Pixel::black, R2Vector(x + 1, 1));
	eraseText(maxHealthPoints / 5, R2Vector(x + 1, 2));
	if (currentHealthPoints > maxHealthPoints)
	{
		auxStr = "";
		for (i = 0; i < maxHealthPoints / 5; i++)
			auxStr += char(219);
		setText(auxStr, Pixel::red, Pixel::black, R2Vector(x + 1, 2));
		
		auxStr = "";
		for (i = 0; i < (currentHealthPoints - maxHealthPoints) / 5; i++)
			auxStr += char(219);
		setText(auxStr, Pixel::yellow, Pixel::black, R2Vector(x + 1, 2));
	}
	else
	{
		auxStr = "";
		for (i = 0; i < currentHealthPoints / 5; i++)
			auxStr += char(219);
		
		setText(auxStr, Pixel::red, Pixel::black, R2Vector(x + 1, 2));
	}

	// shots
	x += maxHealthPoints / 5 + 2;
	setText("Ammo", Pixel::white, Pixel::black, R2Vector(x + 1, 1));
	auxStr = "";
	for (i = 0; i < currentShotsAvailable; i++)
		auxStr += char(219);
	eraseText(maxShotsAvailable, R2Vector(x + 1, 2));    
	setText(auxStr, Pixel::lightBlue, Pixel::black, R2Vector(x + 1, 2));

	// lives
	x += maxShotsAvailable + 2;
	setText("Lives", Pixel::white, Pixel::black, R2Vector(x + 1, 1));
	auxStr = "";
	for (i = 0; i < currentLives; i++)
		auxStr += "<3 ";
	eraseText(3 * maxLives, R2Vector(x + 1, 2));
	setText(auxStr, Pixel::red, Pixel::black, R2Vector(x + 1, 2));

	// score
	x += 3 * maxLives + 1; // the last heart leaves a space at the end
	setText("Score", Pixel::white, Pixel::black, R2Vector(x + 1, 1));
	setText(to_string(score), Pixel::white, Pixel::black, R2Vector(x + 1, 2));

	// general info
	auxInt = (int) (to_string(score)).length();
	x += ((5 > auxInt)? 5 : auxInt) + 2;   // 5 = "score" length
	setText("WASD:  move", Pixel::white, Pixel::black, R2Vector(x + 1, 1));
	setText("Space: shoot", Pixel::white, Pixel::black, R2Vector(x + 1, 2));
}

void Background::eraseText(int textLength, R2Vector initialPosition)
{
	static int i, x, y;

	x = initialPosition.getX();
	y = initialPosition.getY();

	for (i = 0; i < textLength; i++)
	{
		gameInterface[y][x + i].setCh(' ');
		gameInterface[y][x + i].setBackgroundColor(Pixel::black);
		gameInterface[y][x + i].setChColor(Pixel::black);
	}
}

