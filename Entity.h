#pragma once

#include <vector>
#include "Background.h"

class Entity
{
	public:
		// https://theasciicode.com.ar/
		static const int verticalBoxDrawingCh = 179;//186;
		static const int horizontalBoxDrawingCh = 196;//220;//205;

	protected: 
		int damage;
		R2Vector directionVector;
		vector <Pixel> body;

	public: 
		virtual void move(Background* background);
		void printSpaceBehind(Background* background);
		void print();
		void disappear();
		int getDamage();
		bool bodyWillBeOutOfBounds();
		bool bodyOutOfBounds();
		vector <Pixel> getBody();
};
