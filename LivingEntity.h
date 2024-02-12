#pragma once

#include "Entity.h"
#include "Shot.h"

class LivingEntity : public Entity
{
	public:
		enum Orientation
		{
			left	= 0,
			right	= 1,
			up		= 2,
			down	= 3
		};

	protected:
		int healthPoints;
		R2Vector aimingDirection;
		bool willShoot;
		bool putVertically;

	public:
		LivingEntity();
		void move(Background* background);
		bool isAlive();
		void takeDamage(int damage);
		void point(Orientation o, Background* background);
		virtual bool wantsToShoot();
		virtual Shot shoot();

	private:
		void setBodyHorizontally(char directionCh);
		void setBodyVertically(char directionCh);
};
