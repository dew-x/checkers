#pragma once
#include "Board.h"
#include <string>
#include <iostream>
using namespace std;

class AIPlayer
{
protected:
	string name;
public:
	virtual Move doMove(GRID g, Piece me, vector<Move> m) = 0;
	string getName() { return name; };
protected:
	int evalGrid(const GRID g, Piece me);
	void performMove(const GRID g, GRID &res, Move m);
};

class AIDummy : public AIPlayer {
public: 
	AIDummy();
	Move doMove(GRID g, Piece me, vector<Move> m);
};

class AIBest : public AIPlayer {
public:
	AIBest();
	Move doMove(GRID g, Piece me, vector<Move> m);
};

class AIABP : public AIPlayer {
public:
	AIABP();
	int minimax(GRID g, Piece playing, Player p, int depth, int a, int b, bool max);
	Move doMove(GRID g, Piece me, vector<Move> m);
};


