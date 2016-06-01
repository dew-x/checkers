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
	sf::Font font;
	sf::Text typeYourNick;
	sf::Text fpsText;
	int width, height;
	int uid;
	scenes scene;
	Board board;
	char nick[NICKSIZE];
	int nickpos;
	void drawMenu();
	void doGame(sf::Time dt);
	void updateGame(sf::Time dt);
	void drawGame();
	void updatePositions();

	
	sf::Clock deltaClock;
	float fps;

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

