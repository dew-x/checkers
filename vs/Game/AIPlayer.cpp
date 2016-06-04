#include "AIPlayer.h"

int AIPlayer::evalGrid(const GRID g, Piece me)
{
	int score = 0;
	for (unsigned j = 0; j < GSIZE; ++j) {
		if (g[j] & me) {
			score += 2;
			if (g[j] & QUEEN) score += 3;
		}
		else if (g[j] != NONE) {
			score += -2;
			if (g[j] & QUEEN) score += -3;
		}
	}
	return score;
}

void AIPlayer::performMove(const GRID g, GRID & res, Move m)
{
	memcpy(res, g, GSIZE*sizeof(Piece));
	for (unsigned j = 0; j < m.todo.size(); ++j) {
		res[m.todo[j].pos] = m.todo[j].value;
	}
}

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
	name = "EASY";
}

Move AIBest::doMove(GRID g, Piece me, vector<Move> m)
{
	int best = -1;
	int bestScore = -1;
	for (unsigned i = 0; i < m.size(); ++i) {
		GRID gc;
		performMove(g, gc, m[i]);
		int score = evalGrid(gc,me);
		if (best == -1 || score > bestScore) {
			best = i;
			bestScore = score;
		}
	}
	return m[best];
}

AIABP::AIABP()
{
	name = "MEDIUM";
}

	for (unsigned i = 0; i < next.size(); ++i) {
		GRID gc;
		performMove(g, gc, next[i]);
		if (max) {
			if (b <= a)
				return b;
		}
		else {
			if (b <= a)
				return a;
		}
	}
	return max ? a : b;
}

Move AIABP::doMove(GRID g, Piece me, vector<Move> m)
{
	unsigned mID;
	int a = -std::numeric_limits<int>::max();
	int b = std::numeric_limits<int>::max();
	for (unsigned i = 0; i < m.size(); ++i) {
		GRID gc;
		performMove(g, gc, m[i]);
		cout << v << endl;
		if (v > a) {
			a = v;
			mID = i;
		}
	}
	return m[mID];
}


