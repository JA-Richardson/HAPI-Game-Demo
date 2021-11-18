#pragma once
class Border
{
public:
	int left{ 0 }, right, top, bottom;

	Border() = default;

	
	Border(int L, int R, int T, int B) : left(L), right(R), top(T), bottom(B)
	{

	}
	int Width() const { return right - left; }
	int Height() const { return bottom - top; }

	void Translate(int dx, int dy)
	{
		left += dx;
		right += dx;
		top += dy;
		bottom += dy;
	}

	void ClipTo(const Border& other)
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
};

