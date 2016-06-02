#include "AIPlayer.h"



AIPlayer::AIPlayer()
{
}


AIPlayer::~AIPlayer()
{
}

Move AIPlayer::doMove(GRID g, vector<Move> m)
{
	return m[rand()%m.size()];
}
