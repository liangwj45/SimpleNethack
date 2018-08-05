// Direction.hpp
#ifndef _DIREACTION_
#define _DIREACTION_

struct Direction{
	Direction();
	Direction(int t);
	Direction(int tx, int ty);
	Direction& operator++();
	Direction& operator--();
	Direction& operator+=(int t);
	Direction& operator-=(int t);
	int dx_;
	int dy_;
private:
	int i_;
	int dir_[8][2] = { { -1,0 },{ 0,1 },{ 1,0 },{ 0,-1 },{ -1,1 },{ 1,1 },{ 1,-1 },{ -1,-1 } };
};

#endif // !_DIREACTION_