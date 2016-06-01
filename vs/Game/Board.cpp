#include "Board.h"



Board::Board()
{
	reset();
}


Board::~Board()
{
}

Player Board::currentPlayer()
{
	return (Player)(turn%PLAYER_NONE);
}

int Board::currentTurn()
{
	return turn;
}

bool Board::gameEnded()
{
	return piecesBlack == 0 || piecesWhite == 0;
}

Player Board::whoWon()
{
	if (piecesBlack == 0) return PLAYER_WHITE;
	else if (piecesWhite == 0) return PLAYER_BLACK;
	else return PLAYER_NONE;
}

bool Board::isMoveValid(Position a, Position b)
{
	unsigned aID = pos2id(a);
	unsigned bID = pos2id(b);
	for (unsigned i = 0; i < actualMoves.size(); ++i) {
		if (actualMoves[i].a == aID && actualMoves[i].b == bID) return true;
	}
	return false;
}

void Board::makeMove(Position a, Position b)
{
	if (isMoveValid(a, b)) {
		unsigned aID = pos2id(a);
		unsigned bID = pos2id(b);
		grid[bID] = grid[aID];
		grid[aID] = NONE;
		if (b.y == 0 || b.y == 7) grid[bID] = (Piece)(grid[bID]|QUEEN);
		actualMoves = listPossibleMoves(grid, currentPlayer());
	}
}

void Board::getGrid(GRID & res)
{
	for (unsigned i = 0; i < GSIZE; ++i) res[i] = grid[i];
}

void Board::reset()
{
	turn = 0;
	piecesBlack = 12;
	piecesWhite = 12;
	for (unsigned i = 0; i < GSIZE; ++i) grid[i] = DEFAULT[i];
	actualMoves = listPossibleMoves(grid, currentPlayer());
}

unsigned Board::pos2id(Position p)
{
	return (p.x / 2)*p.y;
}

Position Board::id2pos(unsigned id)
{
	unsigned y = id / 4;
	unsigned x = (id % 4)*2+(y%2);
	return { x,y };
}

bool Board::playerUsePiece(Player player, Piece piece)
{
	return (piece&WHITE && player == PLAYER_WHITE) || (piece&BLACK && player == PLAYER_BLACK);
}

int Board::playerPieceDirection(Player p)
{
	if (p == PLAYER_WHITE) return 1;
	else return -1;
}

bool Board::isQueen(Piece p)
{
	return p&QUEEN;
}

vector<Move> listPossibleMoves(GRID g, Player p)
{
	vector<Move> ret(0);
	int dir = Board::playerPieceDirection(p);
	for (unsigned i = 0; i < GSIZE; ++i) {
		if (Board::playerUsePiece(p, g[i])) {
			if (Board::isQueen(g[i])) {
				moveQueen(g, i, ret, { i,0 });
			}
			else {
				moveNormal(g, i, dir, ret,{ i,0 });
			}
		}
	}
	return ret;
}

void moveQueen(GRID g, unsigned pos, vector<Move> &moves, Move m)
{
}

void moveNormal(GRID g, unsigned pos, int d, vector<Move> &moves, Move m)
{
	// right

	// left
}
