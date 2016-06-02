#include "Game.h"



Game::Game(){
	width = 1280;
	height = 720;

	app.create(sf::VideoMode(width,height), "GAME", sf::Style::Default);
	app.setVerticalSyncEnabled(true);
	app.setKeyRepeatEnabled(false);
	scene = SCENE_MENU;
	aiTurn = 0;
	atached = false;
	//load images
	if (!menuBackground.loadFromFile("textures/menu.png"))
	{
		// error...
	}
	if (!pb.loadFromFile("textures/BUTTON.png"))
	{
		// error...
	}
	if (!ib.loadFromFile("textures/BUTTON2.png"))
	{
		// error...
	}
	if (!eb.loadFromFile("textures/BUTTON3.png"))
	{
		// error...
	}

	menuB.setTexture(menuBackground);
	menuB.setPosition(0, 0);
	menuB.setScale(width/menuB.getLocalBounds().width, height/menuB.getLocalBounds().height);

	playerB.setTexture(pb);
	playerB.setOrigin(playerB.getLocalBounds().width/2.0f, playerB.getLocalBounds().height/2.0f);
	playerB.setScale((width*0.18f) / playerB.getLocalBounds().width, (height*0.18f) / playerB.getLocalBounds().height);
	playerB.setPosition(width/2.0f, height/2.0f);
	

	iaB.setTexture(ib);
	iaB.setOrigin(iaB.getLocalBounds().width/2.0f, iaB.getLocalBounds().height / 2.0f);
	iaB.setScale((width*0.18f) / iaB.getLocalBounds().width, (height*0.18f) / iaB.getLocalBounds().height);
	iaB.setPosition(width / 2.0f, (height / 2.0f) + iaB.getGlobalBounds().height);
	

	exitB.setTexture(eb);
	exitB.setOrigin(exitB.getLocalBounds().width/2.0f, exitB.getLocalBounds().height/2.0f);
	exitB.setScale((width*0.18f) / exitB.getLocalBounds().width, (height*0.18f) / exitB.getLocalBounds().height);
	exitB.setPosition(width - exitB.getGlobalBounds().width, height - exitB.getGlobalBounds().height);
	
	//create scope
	
	//app.setMouseCursorVisible(false);

	board = new Board(width, height);
	player = new AIPlayer();
}


Game::~Game(){
	delete board;
	delete player;
}

void Game::run(){
	//app->setFramerateLimit(60);
	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) {
				app.close();
			}

			//mouse event pressed
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (scene == SCENE_MENU) {
					
				}
				else if (scene == SCENE_GAME) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						if (userPlaysAs==board->currentPlayer()) board->press(event.mouseButton.x, event.mouseButton.y);
					}
				}
			}
			//mouse event released
			else if (event.type == sf::Event::MouseButtonReleased) {
				if (scene == SCENE_MENU) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						if (playerB.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
							board->reset();
							scene = SCENE_GAME;
							userPlaysAs = (Player)(rand() % PLAYER_NONE);
						}
						if (iaB.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
							board->reset();
							scene = SCENE_GAME;
							userPlaysAs = PLAYER_NONE;
						}
						if (exitB.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
							app.close();
						}
					}
				}

				else if (scene == SCENE_GAME) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						if (userPlaysAs == board->currentPlayer()) {
							board->release(event.mouseButton.x, event.mouseButton.y);
							if (board->gameEnded()) {
								scene = SCENE_MENU;
							}
						}
					}
				}
			}
			//key pressed events
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape || event.key.alt && event.key.code == sf::Keyboard::F4) {
					app.close();
				}
				else if (scene == SCENE_GAME) {
					if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::D) {

					}

				}
			}

			//key released events
			else if (event.type == sf::Event::KeyReleased) {
				if (scene == SCENE_MENU) {
					
				}
				else if (scene == SCENE_GAME) {
					
				}
			}
		}
		app.clear(sf::Color(0, 0, 0, 128));

		if (scene == SCENE_MENU) {
			drawMenu();
		}
		else if (scene == SCENE_GAME) {
			updateGame();
			drawGame();
		}
		app.display();

	}
}

void Game::drawMenu(){
	app.draw(menuB);
	app.draw(playerB);
	app.draw(iaB);
	app.draw(exitB);
}

void Game::doGame(sf::Time dt){

}

void Game::updateGame(){
	board->move(sf::Mouse::getPosition(app).x, sf::Mouse::getPosition(app).y);
	if (userPlaysAs != board->currentPlayer()) {
		++aiTurn;
		if (aiTurn > AITURNS) {
			//system("PAUSE");
			GRID grid;
			board->getGrid(grid);
			board->makeMove(player->doMove(grid, board->getActualMoves()));
			if (board->gameEnded()) {
				scene = SCENE_MENU;
			}
			aiTurn = 0;
		}
	}
}

void Game::drawGame(){
	app.draw(*board);
}

void Game::updatePositions(){

}
