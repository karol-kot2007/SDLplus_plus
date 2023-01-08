// SDL++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <Window.h>
#include <Surface.h>
#include <Texture.h>
#include <AnimatedSprite.h>
#include "SDL++Client.h"
#include <Input.h>

#undef main
using namespace SDL;
int width = 1920;// SDL::SCREEN_WIDTH;
int height = 1080;
const int spriteSize = 128;
const int numTrees = 10;
const int numEnemies = 4;
//std::unique_ptr<Window> window;
std::unique_ptr<AnimatedSprite> trees[numTrees];
std::unique_ptr<AnimatedSprite> enemies[numEnemies];
/// <summary>
/// 
/// </summary>
void moveSprite(AnimatedSprite* sprite, int deltaX, int deltaY)
{
	auto pos = sprite->position();
	auto newX = pos.x + deltaX;
	pos.x = newX;

	if (pos.x >= 1920)
	{
		return;
	}
	else if (pos.x < 0)
	{
		return;
	}
	pos.y += deltaY;
	if (pos.y > 1080)
	{
		return;
	}
	else if (pos.y < 0)
	{
		return;
	}
	for (int i = 0; i < numTrees; i++)
	{
		auto treePos=trees[i]->position();
		if (treePos.x == pos.x && treePos.y==pos.y)
		{
			return;
		}
	}

	sprite->setPosition(pos);


}
std::unique_ptr<AnimatedSprite> createSprite(std::unique_ptr<Window>* window,std::string spriteImage )
{
	int a = 3;
	int ay = 1;
	int by = 10;
	int bx = 15;
	int dx = rand() % (bx - a) + a;
	int dy = rand() % (by - a) + ay;
	auto sprite = SDL::createAnimatedSprite(*window, spriteImage, { spriteSize * dx,spriteSize * dy });
	return sprite;
}





/// <summary>
/// 
/// 
/// </summary>
/// <returns></returns>
int main()
{

	auto window = SDL::createWindow();
	auto hero = SDL::createAnimatedSprite(window, "Images\\hero.bmp", { 0, 0 });
	

	
	for (int i = 0; i < numTrees; i++)
	{
		trees[i] = createSprite(&window,"Images\\tree.bmp");
	}
	for (int i = 0; i < numEnemies; i++)
	{
		enemies[i] =createSprite(&window,"Images\\bear.bmp");
	}
	bool quit = false;
	SDL::Input input;
	bool redraw = true;
	int speed = spriteSize;
	while (!quit)
	{
		input.update();
		if (input.isKeyDown(SDLK_LEFT))
		{
			moveSprite(hero.get(), -1 * speed, 0);
			redraw = true;
		}
		else if (input.isKeyDown(SDLK_RIGHT))
		{
			moveSprite(hero.get(), 1 * speed, 0);
			redraw = true;
		}
		else if (input.isKeyDown(SDLK_UP))
		{
			moveSprite(hero.get(), 0, -1 * speed);
			redraw = true;
		}
		else if (input.isKeyDown(SDLK_DOWN))
		{
			moveSprite(hero.get(), 0, 1 * speed);
			redraw = true;
		}
		else if (input.isKeyDown(SDLK_ESCAPE))
			quit = true;

		if (redraw)
		{
			window->clear();
			window->render(hero);
			
			for (int i = 0; i < numTrees; i++)
			{
				window->render(trees[i]);
			}

			for (int i = 0; i < numEnemies; i++)
			{
				window->render(enemies[i]);
			}
		}    
		redraw = false;
		SDL::delay(10);
	}  

	return 0;
}


