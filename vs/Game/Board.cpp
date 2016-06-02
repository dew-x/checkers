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
	moving = NULL;
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

bool Board::isMoveValid(Move m)
{
	unsigned aID = m.a;
	unsigned bID = m.b;
	for (unsigned i = 0; i < actualMoves.size(); ++i) {
		if (actualMoves[i].a == aID && actualMoves[i].b == bID) return true;
	}
	return false;
}

void Board::makeMove(Move m)
{
	if (isMoveValid(m)) {
		unsigned aID = m.a;
		unsigned bID = m.b;
		grid[bID] = grid[aID];
		grid[aID] = NONE;
		if (bID < 4 || bID >= 28) grid[bID] = (Piece)(grid[bID]|QUEEN);
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
	return (p.x / 2)+p.y*4;
}

Position Board::id2pos(unsigned id)
{
	unsigned y = id / 4;
	unsigned x = (id % 4)*2+(y%2);
	return { x,y };
}

Piece Board::otherPiece(Piece p)
{
	if (p&WHITE) return BLACK;
	else if (p&BLACK) return WHITE;
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

void Board::press(int x, int y){
	for (unsigned i = 0; i < checkers.size(); i++) {
		if(checkers[i].getGlobalBounds().contains(x,y)){
			Position p = { (x - ox) / cellSize , (y - oy) / cellSize };
			unsigned id = pos2id(p);
			if (playerUsePiece(currentPlayer(), grid[id])) {
				moving = &checkers[i];
			}
			break;
		}
	}
}

void Board::move(int x, int y){
	if (moving != NULL) {
		moving->setPosition(x, y);
	}
}

void Board::release(int x, int y){
	if (moving != NULL) {
		moving->setPosition(x, y);
		moving = NULL;
	}
}

const vector<Move> Board::getActualMoves()
{
	return actualMoves;
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
	cout << ret.size() << endl;
	return ret;
}

void moveQueen(GRID g, unsigned pos, vector<Move> &moves, Move m)
{
}

void moveNormal(GRID g, unsigned pos, int d, vector<Move> &moves, Move m)
{
	Position current = Board::id2pos(pos);
	int nextY = (int)current.y + d;
	if (nextY >= 0 && nextY < 8) {
		// right
		if (current.x < 7) {
			unsigned right = Board::pos2id({ current.x + 1,current.y + d });
			if (g[right] == NONE) {
				moves.push_back({ m.a,right });
			}
			else if (g[right] & Board::otherPiece(g[pos])) {
				if (current.x < 6 && nextY >= 1 && nextY < 7) {
					unsigned right2 = Board::pos2id({ current.x + 2,current.y + d +d});
					if (g[right2] == NONE) {
						moves.push_back({ m.a,right2 });
						GRID gc;
						memcpy(gc,g,GSIZE*sizeof(Piece));
						gc[right2] = gc[pos];
						gc[right] = NONE;
						gc[pos] = NONE;
						moveNormal(gc, right2, d, moves, m);
					}
				}
			}
		}
		// left
		if (current.x > 0) {
			unsigned left = Board::pos2id({ current.x - 1,current.y + d });
			if (g[left] == NONE) {
				moves.push_back({ m.a,left });
			}
			else if (g[left] & Board::otherPiece(g[pos])) {
				if (current.x < 6 && nextY >= 1 && nextY < 7) {
					unsigned left2 = Board::pos2id({ current.x - 2,current.y + d + d });
					if (g[left2] == NONE) {
						moves.push_back({ m.a,left2 });
						GRID gc;
						memcpy(gc, g, GSIZE*sizeof(Piece));
						gc[left2] = gc[pos];
						gc[left] = NONE;
						gc[pos] = NONE;
						moveNormal(gc, left2, d, moves, m);
					}
				}
			}
		}
	}
}
