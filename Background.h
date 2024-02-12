#pragma once

#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Pixel.h"

class Background
{
	public:
		static const int width = 120;
		static const int spaceHeight = 36;
		static const int interfaceHeight = 4;

		static const int amountOfStarTypes = 3;
		static constexpr char stars[amountOfStarTypes] = {'*', '+', '.'};
		static const int amountOfColors = 4;
		static constexpr int starColors[amountOfColors] = {Pixel::white, Pixel::yellow, Pixel::lightYellow, Pixel::lightRed};
		static const int amountOfStarsInSpace = 25;

	private: 
		Pixel space[spaceHeight][width];
		Pixel gameInterface[interfaceHeight][width];

	public:
		Background();
		void setConsoleSize();
		void initializeSpace();
		void initializeInterface();
		void printSpace();
		void printInterface();
		void setPlayerInformation(int currentHealthPoints, int maxHealthPoints, int currentLives, int maxLives, int currentShotsAvailable, int maxShotsAvailable, int score);
		Pixel getSpacePixel(R2Vector positionVector);
		static bool outOfBounds(R2Vector positionVector);

	private:
		void setText(string text, int textColor, int backgroundColor, R2Vector initialPosition);
		void eraseText(int textLength, R2Vector initialPosition);
};
