#pragma once
#include "Board.h"
class AIPlayer
{
public:
	AIPlayer();
	~AIPlayer();
	Move doMove(GRID g, vector<Move> m);
};

