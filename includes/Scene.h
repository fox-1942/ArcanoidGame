#pragma once
#include <paddle.h>
#include <bullet.h>
#include <vector>
class Scene
{
public:
	Paddle paddle;
	std::vector<Bullet> bullets;
	std::vector<Element> blocks;
	bool gameStarted;

public:
	friend void act_game(float dt);
	friend void draw_game();
	friend void win32_key_down(unsigned k);
	friend void win32_key_up(unsigned k);
	
	Scene():gameStarted(false) {};

	Scene(Paddle _paddle, std::vector<Bullet> _bullets, std::vector<Element> _blocks)
		:paddle(_paddle),
		bullets(_bullets),
		blocks(_blocks),
		gameStarted(false)
	{
		
	}

	void shiftPaddleToLeft() {
		if (paddle.getMin().x  > 8) {
			if (!gameStarted) {

				for (size_t i = 0; i < bullets.size(); ++i)
				{
					bullets.at(i).setMinX(-6);
					bullets.at(i).setMaxX(-6);
				}

			}
			paddle.setMinX(-6);
			paddle.setMaxX(-6);
		}
	}

	void shiftPaddleToRight() {
		if (paddle.getMax().x + 8 < sv_width)
		{
			if (!gameStarted) {
				for (size_t i = 0; i < bullets.size(); ++i)
				{
					bullets.at(i).setMinX(6);
					bullets.at(i).setMaxX(6);
				}
			}
			paddle.setMinX(6);
			paddle.setMaxX(6);
		}
	}
};


