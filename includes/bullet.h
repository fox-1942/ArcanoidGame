#pragma once

#include "Element.h"

extern unsigned int sv_width, sv_height;

class Bullet : public Element
{
private:
	bool north, south, west, east;
	float distance;
	bool gameOver;
public:

	Bullet() = default;

	Bullet(unsigned _width, unsigned _height, Vector3 _color) : Element(_color),
		north(true),
		west(true),
		east(false),
		south(false),
		distance(0),
		gameOver(false)
	{
		minP = Vector2((sv_width / 2) - (_width / 2), sv_height - _height - 40);
		maxP = Vector2(minP.x + _width, minP.y + _height);
	}

	bool isCollided( Element& other)
	{
		//top
		if (minP.x < other.getMax().x &&
			maxP.x > other.getMin().x &&
			maxP.y >= other.getMin().y &&
			minP.y < other.getMin().y
			)
		{
			south = false;
			north = true;
			return true;
		}

		if (minP.x < other.getMax().x &&
			maxP.x > other.getMin().x &&
			maxP.y > other.getMax().y &&
			minP.y <= other.getMax().y
			)
		{
			south = true;
			north = false;
			return true;
		}

		if (minP.y < other.getMax().y &&
			maxP.y > other.getMin().y &&
			maxP.x >= other.getMin().x &&
			minP.x < other.getMin().x)
		{
			east = false;
			west = true;
			return true;
		}

		if (minP.y < other.getMax().y &&
			maxP.y > other.getMin().y &&
			minP.x <= other.getMax().x &&
			maxP.x > other.getMax().x)
		{
			east = true;
			west = false;
			return true;
		}

		return false;
	}

	bool is_east() const
	{
		return east;
	}

	void set_east(bool east)
	{
		this->east = east;
	}

	bool is_west() const
	{
		return west;
	}

	void set_west(bool west)
	{
		this->west = west;
	}

	bool move(float dt)
	{
		distance = dt * 80;
		if (north)
		{
			if (minP.y - distance > 50) {
				minP.y -= distance;
				maxP.y -= distance;
			}

			else
			{
				north = false;
				south = true;
				gameOver = false;
			}
		}
		else
		{
			if (south)
			{
				if (maxP.y < sv_height) {
					maxP.y += distance;
					minP.y += distance;
				}

				else
				{
					south = false;
					north = false;
					gameOver = true;
				}
			}
		}

		if (west)
		{
			if (minP.x - distance > 0) {
				minP.x -= distance;
				maxP.x -= distance;
			}

			else
			{
				west = false;
				east = true;
				gameOver = false;
			}
		}
		else
		{
			if (east)
			{
				if (maxP.x + distance < sv_width) {
					maxP.x += distance;
					minP.x += distance;
				}

				else
				{
					east = false;
					west = true;
					gameOver = false;
				}
			}
		}
		distance = 0;
		return gameOver;
	}
};