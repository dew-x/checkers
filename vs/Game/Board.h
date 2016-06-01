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

struct Move {
	unsigned a, b;
};

vector<Move> listPossibleMoves(GRID g, Player p);
void moveQueen(GRID g, unsigned pos, vector<Move> &moves, Move m);
void moveNormal(GRID g, unsigned pos, int d, vector<Move> &moves, Move m);

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
	static bool playerUsePiece(Player player, Piece piece);
	static int playerPieceDirection(Player p);
	static bool isQueen(Piece p);
private:
	unsigned pos2id(Position p);
	Position id2pos(unsigned id);
private:
	int turn;
	GRID grid;
	int piecesWhite;
	int piecesBlack;
	vector<Move> actualMoves;
};

