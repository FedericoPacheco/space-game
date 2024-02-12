#pragma once

#include <iostream>
#include <Windows.h>
#include "R2Vector.h"
using namespace std;

class Pixel
{	
	public: 
		static const int black = 0;
		static const int blue = 1;
		static const int red = 4;
		static const int yellow = 6;
		static const int lightBlue = 9;
		static const int lightRed = 12;
		static const int lightYellow = 14;
		static const int white = 15;
		
	private:
		R2Vector positionVector;
		char ch;
		int chColor;
		int backgroundColor;

	public:
		Pixel();
		void print();
		void setPositionVector(R2Vector positionVector);
		void setCh(char ch);
		void setChColor(int color);
		void setBackgroundColor(int color);
		R2Vector getPositionVector();

	// pseudo private:
		static void goToXY(int x, int y);
};

