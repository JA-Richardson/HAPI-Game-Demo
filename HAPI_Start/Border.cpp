#include "Border.h"


Border::~Border()
{

}
//checks if two sprites are touching
bool Border::Inside(const Border& other)
{
	if (left < other.left) { return false; }
	if (top < other.top) { return false; }
	if (right > other.right) { return false; }
	if (bottom > other.bottom) { return false; }
	return false;
}

bool Border::Outside(const Border& other)
{
	if (left > other.right) { return true; }
	if (top > other.bottom) { return true; }
	if (right < other.left) { return true; }
	if (bottom < other.top) { return true; }
	return false;
}

void Border::Translate(int bx, int by)
{
	left += bx;
	right += bx;
	top += by;
	bottom += by;
}

void Border::ClipTo(const Border& other)
{
	if (left < other.left)
		left = other.left;
	if (right > other.right)
		right = other.right;
	if (top < other.top)
		top = other.top;
	if (bottom > other.bottom)
		bottom = other.bottom;
}




