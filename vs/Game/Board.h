#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include <iostream>
using namespace std;

enum Piece {
	NONE=0,
	WHITE=1,
	BLACK=2,
	QUEEN = 4,
	WHITEQUEEN = 5,
	BLACKQUEEN = 6
};

enum Player {
	PLAYER_WHITE,
	PLAYER_BLACK,
	PLAYER_NONE,
};

struct Position {
	unsigned x, y;
};

const unsigned GSIZE = 32;

typedef Piece GRID[32];

const GRID DEFAULT = {
	WHITE,WHITE,WHITE,WHITE,
	WHITE,WHITE,WHITE,WHITE,
	WHITE,WHITE,WHITE,WHITE,
	NONE,NONE,NONE,NONE,
	NONE,NONE,NONE,NONE,
	BLACK,BLACK,BLACK,BLACK,
	BLACK,BLACK,BLACK,BLACK,
	BLACK,BLACK,BLACK,BLACK,
};

struct Move {
	unsigned a, b;
};

vector<Move> listPossibleMoves(GRID g, Player p);
void moveQueen(GRID g, unsigned pos, vector<Move> &moves, Move m);
void moveNormal(GRID g, unsigned pos, int d, vector<Move> &moves, Move m);

class Board:public sf::Drawable
 {
public:
	Board();
	Board(int width, int height);
	~Board();
	Player currentPlayer();
	int currentTurn();
	bool gameEnded();
	Player whoWon();
	bool isMoveValid(Position a, Position b);
	void makeMove(Position a, Position b);
	void getGrid(GRID &res);
	void reset();
	void update();
	static bool playerUsePiece(Player player, Piece piece);
	static int playerPieceDirection(Player p);
	static bool isQueen(Piece p);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void press(int x, int y);
	void move(int x, int y);
	void release(int x, int y);
private:
	unsigned pos2id(Position p);
	Position id2pos(unsigned id);
private:
	
	int turn;
	GRID grid;
	int piecesWhite;
	int piecesBlack;
	vector<Move> actualMoves;
	int cellSize;
	int ox, oy;

	sf::VertexArray table;
	sf::Texture whiteChecker;
	sf::Texture redChecker;
	sf::Texture whiteQueen;
	sf::Texture redQueen;

	vector<sf::Sprite> checkers;
};

