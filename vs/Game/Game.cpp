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

	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	AIname1 = sf::Text("UNKNOWN",font);
	AIname1.setFont(font);
	AIname2 = sf::Text("UNKNOWN",font);
	AIname2.setFont(font);

	AIname1.setOrigin(AIname1.getLocalBounds().width / 2.0f, AIname1.getLocalBounds().height / 2.0f);
	AIname1.setColor(sf::Color::White);
	AIname1.setPosition(width/8.0f,height/5.0f);

	AIname2.setOrigin(AIname2.getLocalBounds().width / 2.0f, AIname2.getLocalBounds().height / 2.0f);
	AIname2.setColor(sf::Color::Red);
	AIname2.setPosition(width-(width / 8.0f),height- (height / 5.0f));
	//load images

	//menu
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

	//chose dificult
	if (!choseBackground.loadFromFile("textures/IAselectionMenu.jpg"))
	{
		// error...
	}
	if (!dummyButton.loadFromFile("textures/DummyButton.jpg"))
	{
		// error...
	}
	if (!easyButton.loadFromFile("textures/EasyButton.jpg"))
	{
		// error...
	}
	if (!mediumButton.loadFromFile("textures/MediumButton.jpg"))
	{
		// error...
	}
	if (!hardButton.loadFromFile("textures/HardButton.jpg"))
	{
		// error...
	}


	//SPRITES

	//menu
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

	//chose dificult
	choseB.setTexture(choseBackground);
	choseB.setPosition(0, 0);
	choseB.setScale(width / choseB.getLocalBounds().width, height / choseB.getLocalBounds().height);

	dummyB.setTexture(dummyButton);
	dummyB.setOrigin(dummyB.getLocalBounds().width / 2.0f, dummyB.getLocalBounds().height / 2.0f);
	dummyB.setScale((width*0.18f) / dummyB.getLocalBounds().width, (height*0.18f) / dummyB.getLocalBounds().height);
	dummyB.setPosition(width / 4.0f, height / 3.0f);

	easyB.setTexture(easyButton);
	easyB.setOrigin(easyB.getLocalBounds().width / 2.0f, easyB.getLocalBounds().height / 2.0f);
	easyB.setScale((width*0.18f) / easyB.getLocalBounds().width, (height*0.18f) / easyB.getLocalBounds().height);
	easyB.setPosition(width - (width / 4.0f), height / 3.0f);

	mediumB.setTexture(mediumButton);
	mediumB.setOrigin(mediumB.getLocalBounds().width / 2.0f, mediumB.getLocalBounds().height / 2.0f);
	mediumB.setScale((width*0.18f) / mediumB.getLocalBounds().width, (height*0.18f) / mediumB.getLocalBounds().height);
	mediumB.setPosition(width / 4.0f,height -  (height / 4.0f));

	hardB.setTexture(hardButton);
	hardB.setOrigin(hardB.getLocalBounds().width / 2.0f, hardB.getLocalBounds().height / 2.0f);
	hardB.setScale((width*0.18f) / hardB.getLocalBounds().width, (height*0.18f) / hardB.getLocalBounds().height);
	hardB.setPosition(width - (width / 4.0f), height - (height / 4.0f));


	
	//create scope
	
	//app.setMouseCursorVisible(false);

	board = new Board(width, height);
	players = vector<AIPlayer*>(0);
	players.push_back(new AIDummy());
	players.push_back(new AIBest());
	players.push_back(new AIBest2());
	players.push_back(new AIABP());
	player1 = 0;
	player2 = 0;

	scores = vector<vector <int> >(players.size(), vector<int>(players.size(), 0));

	scoreGrid = vector<sf::Text>((players.size() + 1)*(players.size() + 1));
	for (unsigned i = 0;i<=players.size();i++) {
		for (unsigned j = 0;j <=players.size();j++) {
			unsigned c = i * (players.size() + 1) + j;
			scoreGrid[c] = sf::Text("0",font,25);
			if ((i == 0 && j != 0) || (i != 0 && j == 0)) {
				scoreGrid[c].setCharacterSize(12);
			}
			scoreGrid[c].setOrigin(scoreGrid[c].getLocalBounds().width / 2.0f, scoreGrid[c].getLocalBounds().height / 2.0f);
			scoreGrid[c].setPosition((j* width/25.0f) + width/40.0f, (i * height/16.0f)+ height/3.0f);
			
		}
	}
	updateScore();
}


Game::~Game(){
	delete board;
	for (unsigned i = 0; i < players.size(); ++i) {
		delete players[i];
	}
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
							scene = SCENE_CHOSE_DIFICULT;
							board->reset();
							board->update();
							userPlaysAs = (Player)(rand() % PLAYER_NONE);
							if (userPlaysAs == PLAYER_WHITE) {
								AIname1.setString("PLAYER");
							}
							else {
								AIname2.setString("PLAYER");
							}
						}
						if (iaB.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
							board->reset();
							board->update();
							scene = SCENE_GAME;
							userPlaysAs = PLAYER_NONE;
							player1 = rand() % players.size();
							player2 = rand() % players.size();
							while (player2==player1) player2 = rand() % players.size();
							AIname1.setString(players[player1]->getName());
							AIname2.setString(players[player2]->getName());
						}
						if (exitB.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
							app.close();
						}
					}
				}
				else if (scene == SCENE_CHOSE_DIFICULT) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						if (dummyB.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
							scene = SCENE_GAME;
							player1 = 0;
						}if (easyB.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
							scene = SCENE_GAME;
							player1 = 1;
						}if (mediumB.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
							scene = SCENE_GAME;
							player1 = 2;
						}if (hardB.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
							scene = SCENE_GAME;
							player1 = 3;
						}
						if (scene == SCENE_GAME) {
							if (userPlaysAs == PLAYER_WHITE) {
								AIname2.setString(players[player1]->getName());
							}
							else {
								AIname1.setString(players[player1]->getName());
							}
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
				else if (scene == SCENE_MENU) {
					if (event.key.code == sf::Keyboard::T) {
						scene = SCENE_TEST;
						toGoTest = TESTGAMES;
						board->reset();
						board->update();
						player1 = rand() % players.size();
						player2 = rand() % players.size();
						while (player2 == player1) player2 = rand() % players.size();
						AIname1.setString(players[player1]->getName());
						AIname2.setString(players[player2]->getName());
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
		else if (scene == SCENE_CHOSE_DIFICULT) {
			drawChoseDificult();
		}

		else if (scene == SCENE_GAME) {
			updateGame();
			drawGame();
		}
		else if (scene == SCENE_TEST) {
			updateTest();
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

void Game::drawChoseDificult(){
	app.draw(choseB);
	app.draw(dummyB);
	app.draw(easyB);
	app.draw(mediumB);
	app.draw(hardB);
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
			unsigned movingPlayer = board->currentPlayer() == PLAYER_WHITE ? player1 : player2;
			board->makeMove(players[movingPlayer]->doMove(grid, board->currentPiece(), board->getActualMoves()));
			if (board->gameEnded()) {
				unsigned otherPlayer = movingPlayer == player2 ? player1 : player2;
				++scores[movingPlayer][otherPlayer];
				updateScore();
				scene = SCENE_MENU;
			}
			aiTurn = 0;
		}
	}
}

void Game::drawGame(){
	app.draw(*board);
	app.draw(AIname1);
	app.draw(AIname2);
	for (unsigned i = 0; i < scoreGrid.size(); i++) {
		app.draw(scoreGrid[i]);
	}
}

void Game::updateScore() {
	for (unsigned i = 0; i <= players.size(); i++) {
		for (unsigned j = 0; j <= players.size(); j++) {
			unsigned c = i * (players.size() + 1) + j;
			string s = "";
			if ((i == 0 && j != 0) || (i !=0 && j == 0)) {
				s = players[i + j - 1]->getName();
			}
			else if(i + j){
				s += to_string(scores[i - 1][j - 1])+"-"+to_string(scores[j - 1][i - 1]);
			}
			scoreGrid[c].setString(s);
			scoreGrid[c].setOrigin(scoreGrid[c].getLocalBounds().width / 2.0f, scoreGrid[c].getLocalBounds().height / 2.0f);
		}
	}
}

void Game::updateTest()
{
	GRID grid;
	board->getGrid(grid);
	unsigned movingPlayer = board->currentPlayer() == PLAYER_WHITE ? player1 : player2;
	board->makeMove(players[movingPlayer]->doMove(grid, board->currentPiece(), board->getActualMoves()));
	if (board->gameEnded()) {
		unsigned otherPlayer = movingPlayer == player2 ? player1 : player2;
		++scores[movingPlayer][otherPlayer];
		updateScore();
		--toGoTest;
		if (toGoTest) {
			board->reset();
			board->update();
			player1 = rand() % players.size();
			player2 = rand() % players.size();
			while (player2 == player1) player2 = rand() % players.size();
			AIname1.setString(players[player1]->getName());
			AIname2.setString(players[player2]->getName());
		}
		else {
			scene = SCENE_MENU;
		}
	}
}
