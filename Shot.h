#pragma once

#include "Entity.h"

class Shot : public Entity
{
	public:
		// https://theasciicode.com.ar/
		static const int horizontalShot = 45; //196;
		static const int verticalShot = 124; //179;

	private:
		bool firstMovement;

	public:
		Shot();
		Shot(char shotCh, bool isFromPlayer, int damage, R2Vector directionVector, R2Vector positionVector);
		void move(Background* background);
};