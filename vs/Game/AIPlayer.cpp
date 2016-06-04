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

int AIPlayer::evalGrid2(const GRID g, Piece me)
{
	int score = 0;
	bool filled0 = (g[0] & g[1] & g[2] & g[3])>9;
	bool filled1 = (g[28] & g[29] & g[30] & g[31])>0;
	for (unsigned j = 0; j < GSIZE; ++j) {
		if (g[j] & me) {
			if (g[j] & QUEEN) score += 200;
			else {
				if (me&BLACK) {
					if (j >= 28 && filled1) score += 30;
					else score += 70-(j / 4) * 10;
				}
				else {
					if (j < 4 && filled0) score += 30;
					else score += (j / 4) * 10;
				}
			}
		}
		else if (g[j] != NONE) {
			if (g[j] & QUEEN) score -= 200;
			else {
				if (me&BLACK) {
					if (j >= 28 && filled1) score -= 30;
					else score -= 70 - (j / 4) * 10;
				}
				else {
					if (j < 4 && filled0) score -= 30;
					else score -= (j / 4) * 10;
				}
			}
		}
	}
	return score;
}

int cornerDiagonal(const GRID g, Piece losing, Piece winning)
{
	int c = 0;
	if (g[0]&losing || g[4]&losing)
	{
		c += 9;
		if (g[0]&winning)
			c -= 3;
		if (g[4]&winning)
			c -= 3;
		if (g[5] & winning)
			c -= 1;
		if (g[8] & winning)
			c -= 1;
		if (g[9] & winning)
			c -= 1;
		if (g[13] & winning)
			c -= 1;
	}
	if (g[27] & losing || g[31] & losing)
	{
		c += 9;
		if (g[18] &winning)
			c -= 1;
		if (g[22] & winning)
			c -= 1;
		if (g[23] & winning)
			c -= 1;
		if (g[26] & winning)
			c -= 1;
		if (g[27] & winning)
			c -= 3;
		if (g[31] & winning)
			c -= 3;
	}
	return c;
}

int AIPlayer::evalGrid3(const GRID g, Piece me)
{
	int a1 = 0, a2 = 0, b = 0, c = 0, d = 0;
	for (unsigned j = 0; j < 32; ++j) {
		if (g[j] & me) {
			c += 1;
			if (g[j] & QUEEN) a1 += 3;
			else {
				a1 += 2;
				if (me&BLACK) {
					if (j >= 28) b += 9;
					else b += 7 - (j / 4);
				}
				else {
					if (j < 4) b += 30;
					else b += (j / 4);
				}
			}
		}
		else if (g[j] != NONE) {
			c -= 1;
			if (g[j] & QUEEN) a2 -= 3;
			else {
				a2 -= 2;
				if (me&BLACK) {
					if (j >= 28) b -= 9;
					else b -= 7 - (j / 4);
				}
				else {
					if (j < 4) b -= 9;
					else b -= (j / 4);
				}
			}
		}
	}
	if (c > 0 && a2 >= -8)
		d -= cornerDiagonal(g,me,me?WHITE:BLACK);
	else if (c < 0 && a1 <= 8)
		d += cornerDiagonal(g, me ? WHITE : BLACK,me);
	a1 *= 10000000;
	a2 *= 10000000;
	b *= 100000;
	c *= 1000;
	d *= 10;
	int e = rand() % 10;
	return a1 + a2 + b + c + d + e;
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
	int best = -1;
	int bestScore = -1;
	for (unsigned i = 0; i < m.size(); ++i) {
		GRID gc;
		performMove(g, gc, m[i]);
		int score = evalGrid(gc, me);
		if (best == -1 || score > bestScore) {
			best = i;
			bestScore = score;
		}
	}
	return m[best];
}

AIBest::AIBest()
{
	name = "EASY";
}

Move AIBest::doMove(GRID g, Piece me, vector<Move> m)
{
	int best = -1;
	int bestScore = -1;
	vector<unsigned> p;
	for (unsigned i = 0; i < m.size(); ++i) {
		GRID gc;
		performMove(g, gc, m[i]);
		vector<Move> next = listPossibleMoves(gc, (me&WHITE)?PLAYER_BLACK:PLAYER_WHITE);
		int worst=10000;
		for (unsigned j = 0; j < next.size(); ++j) {
			GRID gc2;
			performMove(gc, gc2, next[j]);
			int score = evalGrid3(gc2, me);
			if (j == 0 || score<worst) {
				worst = score;
			}
		}
		if (best == -1 || worst > bestScore) {
			best = i;
			bestScore = worst;
			p.clear();
			p = { i };
		}
		else if (worst == bestScore) {
			p.push_back(i);
		}
	}
	return m[p[rand() % p.size()]];
}

AIBest2::AIBest2()
{
	name = "MEDIUM";
}

Move AIBest2::doMove(GRID g, Piece me, vector<Move> m)
{
	int best = -1;
	int bestScore = -1;
	vector<unsigned> p;
	for (unsigned i = 0; i < m.size(); ++i) {
		GRID gc;
		performMove(g, gc, m[i]);
		vector<Move> next = listPossibleMoves(gc, (me&WHITE) ? PLAYER_BLACK : PLAYER_WHITE);
		int worst = 10000;
		for (unsigned j = 0; j < next.size(); ++j) {
			GRID gc2;
			performMove(gc, gc2, next[j]);
			int score = evalGrid(gc2, me);
			if (j == 0 || score<worst) {
				worst = score;
			}
		}
		if (best == -1 || worst > bestScore) {
			best = i;
			bestScore = worst;
			p.clear();
			p = { i };
		}
		else if (worst == bestScore) {
			p.push_back(i);
		}
	}
	return m[p[rand() % p.size()]];
}

AIABP::AIABP()
{
	name = "HARD";
}

int AIABP::minimax(GRID g, Piece playing, Player p, int score0, int depth, int a, int b, bool max) {
	if (depth == 0) {
		int ret = evalGrid3(g, playing);
		if (ret == score0) return score0-1;
		else return ret;
	}
	vector<Move> next = listPossibleMoves(g, p);
	if (next.size() == 0) {
		return evalGrid3(g, playing);
		if (p == PLAYER_WHITE && playing == WHITE || p == PLAYER_BLACK && playing == BLACK) return -1000000000;
		else return 1000000000;
	}
	for (unsigned i = 0; i < next.size(); ++i) {
		GRID gc;
		performMove(g, gc, next[i]);
		if (max) {
			a = std::max(a, minimax(gc,playing, p == PLAYER_BLACK ? PLAYER_WHITE : PLAYER_BLACK, score0, depth - 1, a, b, false));
			if (b <= a)
				return b;
		}
		else {
			b = std::min(b, minimax(gc, playing, p==PLAYER_BLACK?PLAYER_WHITE:PLAYER_BLACK, score0, depth - 1, a, b, true));
			if (b <= a)
				return a;
		}
	}
	return max ? a : b;
}

Move AIABP::doMove(GRID g, Piece me, vector<Move> m)
{
	int a = -std::numeric_limits<int>::max();
	int b = std::numeric_limits<int>::max();
	unsigned best;
	int initscore = evalGrid(g,me);
	for (unsigned i = 0; i < m.size(); ++i) {
		GRID gc;
		performMove(g, gc, m[i]);
		int v = minimax(gc, me, me == WHITE ? PLAYER_BLACK : PLAYER_WHITE,initscore, 5, a, b, false);
		if (v > a) {
			a = v;
			best = i;
		}
	}
	return m[best];
}


