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

