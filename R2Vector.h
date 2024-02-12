#pragma once

class R2Vector
{
	private:
		int x;
		int y;

	public:
		R2Vector();
		R2Vector(int x, int y);
		R2Vector operator+(R2Vector other);
		R2Vector operator*(int scalar);
		R2Vector orthogonalVector();
		bool operator==(R2Vector other);
		int getX();
		int getY();
		void setXY(int x, int y);
		void pseudoNormalize();
};