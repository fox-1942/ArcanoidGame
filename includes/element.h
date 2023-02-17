#pragma once

struct Vector3 {
	unsigned char x, y, z;

	Vector3() = default;

	Vector3(unsigned char x_, unsigned char y_, unsigned char z_) {
		x = x_;
		y = y_;
		z = z_;
	}
};

struct Vector2 {
	float x, y;

	Vector2() = default;

	Vector2(float x_, float y_) {
		x = x_;
		y = y_;
	}
};

class Element
{

protected:

	Vector2 minP;
	Vector2 maxP;
	Vector3 colour;

public:

	Element() :colour(Vector3(0, 0, 0)),
		minP(Vector2(0, 0)),
		maxP(Vector2(0, 0))
	{

	}

	Element(Vector3 _color) :
		minP(Vector2(0, 0)),
		maxP(Vector2(0, 0)),
		colour(_color)
	{
	}

	virtual Vector2 getMin() { return minP; }
	virtual Vector2 getMax() { return maxP; }
	virtual void setMin(Vector2 _min) { minP = _min; }
	virtual void setMax(Vector2 _max) { maxP = _max; }

	virtual void setMinX(int param) { minP.x += param; }
	virtual void setMaxX(int param) { maxP.x += param; }


	virtual bool isOnScreen(unsigned row, unsigned column)
	{
		if (minP.x <= column && maxP.x >= column &&
			minP.y <= row && maxP.y >= row)
		{
			return true;
		}
		return false;
	}

	virtual unsigned int getColour() {
		return (colour.x << 16) | (colour.y << 8) | colour.z;
	}
};