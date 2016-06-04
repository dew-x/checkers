#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include "AIPlayer.h"
#include "Board.h"
using namespace std;

#define NICKSIZE 25
#define AITURNS 30
#define TESTGAMES 100

enum scenes {
	SCENE_MENU,
	SCENE_CHOSE_DIFICULT,
	SCENE_GAME,
	SCENE_SCORE,
	SCENE_TEST
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
	int toGoTest;
	scenes scene;
	Board *board;
	Player userPlaysAs;
	unsigned player1, player2;
	vector<AIPlayer*> players;
	vector<vector<int> > scores;

	int aiTurn;

	bool atached;
	void drawMenu();
	void drawChoseDificult();
	void doGame(sf::Time dt);
	void updateGame();
	void drawGame();
	void updateScore();
	void updateTest();
	

	// TEXTURES

	//menu
	sf::Texture menuBackground;
	sf::Texture pb;
	sf::Texture ib;
	sf::Texture eb;

	//chose dificult
	sf::Texture choseBackground;
	sf::Texture dummyButton;
	sf::Texture easyButton;
	sf::Texture mediumButton;
	sf::Texture hardButton;

	//SPRITES

	//menu
	sf::Sprite menuB;
	sf::Sprite playerB;
	sf::Sprite iaB;
	sf::Sprite exitB;

	//chose dificult
	sf::Sprite choseB;
	sf::Sprite dummyB;
	sf::Sprite easyB;
	sf::Sprite mediumB;
	sf::Sprite hardB;

	sf::Font font;
	sf::Text AIname1;
	sf::Text AIname2;

	vector<sf::Text> scoreGrid;
};

