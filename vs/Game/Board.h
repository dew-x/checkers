#pragma once
#include <vector>
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

class Board
{
public:
	Board();
	~Board();
	Player currentPlayer();
	int currentTurn();
	bool gameEnded();
	Player whoWon();
	bool isMoveValid(Position a, Position b);
	void makeMove(Position a, Position b);
	void getGrid(GRID &res);
	void reset();
private:
	unsigned pos2id(Position p);
	Position id2pos(unsigned id);
	bool playerUsePiece(Player player, Piece piece);
private:
	int turn;
	GRID grid;
	int piecesWhite;
	int piecesBlack;

};

