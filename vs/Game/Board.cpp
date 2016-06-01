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
	if (playerUsePiece(currentPlayer(), grid[aID]) && grid[bID] == NONE) {
		return true;
	}
}

void Board::makeMove(Position a, Position b)
{
	if (isMoveValid(a, b)) {
		unsigned aID = pos2id(a);
		unsigned bID = pos2id(b);
		grid[bID] = grid[aID];
		grid[aID] = NONE;
		if (b.y == 0 || b.y == 7) grid[bID] = (Piece)(grid[bID]|QUEEN);
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
}

unsigned Board::pos2id(Position p)
{
	return (p.x / 2)*p.y;
}

Position Board::id2pos(unsigned id)
{
	unsigned y = id / 8;
	unsigned x = (id % 4)*2+(y%2);
	return { x,y };
}

bool Board::playerUsePiece(Player player, Piece piece)
{
	return (piece&WHITE && player == PLAYER_WHITE) || (piece&BLACK && player == PLAYER_BLACK);
}
