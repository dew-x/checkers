#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include "AIPlayer.h"
#include "Board.h"
using namespace std;

#define NICKSIZE 25
#define AITURNS 30

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
	Player userPlaysAs;
	AIPlayer *player;

	int aiTurn;

	bool atached;
	void drawMenu();
	void doGame(sf::Time dt);
	void updateGame();
	void drawGame();
	void updatePositions();

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

