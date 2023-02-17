#include "stdafx.h"
#include "svga.h"
#include <Scene.h>

extern bool game_quited;
extern int gAxis[2];
extern int gButtons[6];
extern unsigned int sv_width, sv_height;
static unsigned* shadow_buf = NULL;
Scene scene;

void w32_update_screen(void* scrptr, unsigned scrpitch);

void win32_key_down(unsigned k) {
	if (k == VK_ESCAPE) game_quited = true;
	if (k == VK_LEFT) scene.paddle.leftShift = true;
	if (k == VK_RIGHT) scene.paddle.rightShift = true;
}
void win32_key_up(unsigned k)
{
	if (k == VK_LEFT) scene.paddle.leftShift = false;
	if (k == VK_RIGHT) scene.paddle.rightShift = false;
	if (k == VK_SPACE) scene.gameStarted = true;
}

void init_game() {
	shadow_buf = new unsigned[sv_width * sv_height];

	std::vector<Element> blocks;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			blocks.push_back(Element(Vector3(0, 130, 0)));
			blocks[(i * 3) + j].setMin(Vector2(i * 60 + 190, j * 60 + 100));
			blocks[(i * 3) + j].setMax(Vector2(blocks[(i * 3) + j].getMin().x + 40,
				blocks[(i * 3) + j].getMin().y + 40));
		}
	}

	std::vector<Bullet> bullets;

	bullets.push_back(Bullet(10, 20, Vector3(200, 50, 0)));
	bullets.push_back(Bullet(10, 20, Vector3(200, 50, 0)));
	bullets.at(1).set_east(true);
	bullets.at(1).set_west(false);

	scene = Scene(Paddle(60, 10, Vector3(255, 0, 0)), bullets, blocks);

}

void close_game() {
	delete shadow_buf;
	shadow_buf = NULL;
}

void draw_game() {
	if (!shadow_buf)return;
	memset(shadow_buf, 200, sv_width * sv_height * 4);

	// Querying the colour into the buffer.
	for (size_t i = 0; i < sv_width * sv_height; ++i)
	{
		int row = i / sv_width;
		int column = i % sv_width;

		if (scene.paddle.isOnScreen(row, column)) {
			*(shadow_buf + i) = scene.paddle.getColour();
		}

		for (size_t k = 0; k < scene.bullets.size(); ++k)
		{
			if (scene.bullets.at(k).isOnScreen(row, column)) {
				*(shadow_buf + i) = scene.bullets.at(k).getColour();
			}
		}

		for (size_t j = 0; j < scene.blocks.size(); ++j)
		{
			if (scene.blocks[j].isOnScreen(row, column))
				*(shadow_buf + i) = scene.blocks[j].getColour();
		}
	}

	// Checking collision against the paddle
	for (size_t i = 0; i < scene.bullets.size(); ++i)
	{
		scene.bullets.at(i).isCollided(scene.paddle);
	}

	// Checking collision against blocks
	for (size_t j = 0; j < scene.bullets.size(); ++j)
	{
		for (auto it = scene.blocks.begin(); it != scene.blocks.end();)
		{
			if (scene.bullets.at(j).isCollided(*it))
				it = scene.blocks.erase(it);
			else {
				++it;
			}
		}
	}

	w32_update_screen(shadow_buf, sv_width * 4);
}


void act_game(float dt) {
	if (scene.gameStarted)
	{

		for (auto it = scene.bullets.begin(); it != scene.bullets.end();)
		{
			if ((*it).move(dt))
				it = scene.bullets.erase(it);
			else {
				++it;
			}
		}

		if (scene.bullets.empty() || scene.blocks.empty()) { init_game(); }
	}

	if (scene.paddle.leftShift) { scene.shiftPaddleToLeft(); }
	if (scene.paddle.rightShift) { scene.shiftPaddleToRight(); }
}