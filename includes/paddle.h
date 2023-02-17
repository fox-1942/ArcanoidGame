#pragma once

#include "Element.h"
extern unsigned int sv_width, sv_height;

class Paddle : public Element
{
public:
	bool leftShift;
	bool rightShift;

	Paddle() : leftShift(false),
		rightShift(false) {
	};

	Paddle(unsigned int _width, unsigned int _height, Vector3 _color) :
		Element(_color)
	{
		minP = Vector2((sv_width / 2) - (_width / 2), sv_height - _height - 20);
		maxP = Vector2(minP.x + _width, minP.y + _height);

		leftShift = false;
		rightShift = false;
	}
};