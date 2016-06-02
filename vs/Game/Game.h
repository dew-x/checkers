#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include "AIPlayer.h"
#include "Board.h"
using namespace std;

#define NICKSIZE 25

enum scenes {
	SCENE_MENU,
	SCENE_GAME,
	SCENE_SCORE
};


class Game
{
public:
	Game();
	~Game();
	void run();
private:
	sf::RenderWindow app;
	int width, height;
	int uid;
	scenes scene;
	Board *board;

	int ox;
	int oy;
	int cellSize;

	bool atached;
	void drawMenu();
	void doGame(sf::Time dt);
	void updateGame();
	void drawGame();
	void updatePositions();

	Position worldToGrid(int x, int y);
	Position initPos;
	Position finalPos;

	// TEXTURES
	sf::Texture menuBackground;
	sf::Texture pb;
	sf::Texture ib;
	sf::Texture eb;

	sf::Sprite menuB;
	sf::Sprite playerB;
	sf::Sprite iaB;
	sf::Sprite exitB;
};

