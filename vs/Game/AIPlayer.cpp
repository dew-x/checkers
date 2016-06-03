#include "AIPlayer.h"

AIDummy::AIDummy()
{
	name = "DUMMY";
}

Move AIDummy::doMove(GRID g, Piece me, vector<Move> m)
{
	return m[rand()%m.size()];
}

AIBest::AIBest()
{
	name = "BEST MOVE";
}

Move AIBest::doMove(GRID g, Piece me, vector<Move> m)
{
	int best = -1;
	int bestScore = -1;
	for (unsigned i = 0; i < m.size(); ++i) {
		GRID gc;
		memcpy(gc, g, GSIZE*sizeof(Piece));
		for (unsigned j = 0; j < m[i].todo.size(); ++j) {
			gc[m[i].todo[j].pos] = m[i].todo[j].value;
		}
		int score = 0;
		for (unsigned j = 0; j < GSIZE; ++j) {
			if (gc[j] & me) {
				score += 2;
				if (gc[j] & QUEEN) score += 3;
			}
			else if (gc[j]!=NONE) {
				score += -2;
				if (gc[j] & QUEEN) score += -3;
			}
		}
		if (best == -1 || score > bestScore) {
			best = i;
			bestScore = score;
		}
	}
	return m[best];
}
