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

int AIABP::minimax(GRID g, Piece playing,Player p, int depth, int a, int b, bool max) {
	if (depth == 0) return evalGrid(g,playing);
	vector<Move> next = listPossibleMoves(g, p);
	if (next.size()==0) return evalGrid(g, playing);
	for (unsigned i = 0; i < next.size(); ++i) {
		GRID gc;
		performMove(g, gc, next[i]);
		if (max) {
			a = std::max(a, minimax(g,playing, p == PLAYER_BLACK ? PLAYER_WHITE : PLAYER_BLACK, depth - 1, a, b, false));
			if (b <= a)
				return b;
		}
		else {
			b = std::min(b, minimax(g, playing, p==PLAYER_BLACK?PLAYER_WHITE:PLAYER_BLACK, depth - 1, a, b, true));
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
		int v = minimax(gc, me, me == WHITE ? PLAYER_BLACK : PLAYER_WHITE, 3, a, b, false);
		if (v > a) {
			a = v;
			mID = i;
		}
	}
	return m[mID];
}


