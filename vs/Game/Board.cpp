#include "Board.h"


Board::Board()
{
}
Board::Board(int width, int height)
{
	reset();
	table = sf::VertexArray(sf::Quads, 256);
	int min = width;
	if (height < width) min = height;
	ox = (width - min) / 2;
	oy = (height - min) / 2;
	cellSize = min / 8;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			int coord = (i * 8 + j)*4;
			table[coord].position = { (float)ox + min / 8 * i,(float)oy + min / 8 * j };
			table[coord+1].position = { (float)ox + min / 8 * (i+1),(float)oy + min / 8 * j };
			table[coord+2].position = { (float)ox + min / 8 * (i+1),(float)oy + min / 8 * (j+1) };
			table[coord+3].position = { (float)ox + min / 8 * i,(float)oy + min / 8 * (j+1) };
			sf::Color bg = sf::Color::White;
			if ((i + j) % 2) bg = sf::Color::Black;
			for (int k = 0; k < 4; ++k) table[coord + k].color = bg;
		}
	}
	checkers = vector<sf::Sprite>(24);
	update();
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
		update();
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

void Board::update(){
	//load images
	if (!whiteChecker.loadFromFile("textures/whiteChecker.png"))
	{
		// error...
		cout << "ERR" << endl;
	}
	if (!redChecker.loadFromFile("textures/redChecker.png"))
	{
		// error...
		cout << "ERR" << endl;
	}
	if (!whiteQueen.loadFromFile("textures/whiteQueen.png"))
	{
		// error...
		cout << "ERR" << endl;
	}
	if (!redQueen.loadFromFile("textures/redQueen.png"))
	{
		// error...
		cout << "ERR" << endl;
	}
	int whiteCounter = 0;
	int redCounter = 0;
	for (unsigned i = 0; i < GSIZE; ++i) {
		if (grid[i] & WHITE) {
			sf::Texture *tex = &whiteChecker;
			if (grid[i] & QUEEN) {
				tex = &whiteQueen;
			}
			Position p = id2pos(i);
			checkers[whiteCounter] = sf::Sprite(*tex);
			checkers[whiteCounter].setPosition(ox+p.x * cellSize, oy+p.y * cellSize );
			++whiteCounter;
		}
		else if (grid[i] & BLACK) {
			sf::Texture *tex = &redChecker;
			if (grid[i] & QUEEN) {
				tex = &redQueen;
			}
			Position p = id2pos(i);
			checkers[redCounter + 12] = sf::Sprite(*tex);
			checkers[redCounter + 12].setPosition(ox+p.x * cellSize, oy+p.y * cellSize);
			++redCounter;
		}
	}
	cout << whiteCounter << " " << redCounter << " " << checkers.size() << endl;
	while (whiteCounter < 12) {
		checkers[whiteCounter] = sf::Sprite(whiteChecker);
		checkers[whiteCounter].setPosition(-1000,-1000);
		++whiteCounter;
	}
	while (redCounter < 12) {
		checkers[redCounter+12] = sf::Sprite(redChecker);
		checkers[redCounter+12].setPosition(-1000, -1000);
		++redCounter;
	}
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
	return (p&QUEEN)>0;
}

void Board::draw(sf::RenderTarget & target, sf::RenderStates states) const{
	target.draw(table);
	for (unsigned i = 0; i < 24; i++) {
		target.draw(checkers[i]);
	}
}

void Board::press(int x, int y)
{
}

void Board::move(int x, int y)
{
}

void Board::release(int x, int y)
{
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
