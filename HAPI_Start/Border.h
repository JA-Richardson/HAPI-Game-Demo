#pragma once

class Border
{
public:
	int left{ 0 }, right{ 0 }, top{ 0 }, bottom{ 0 };

	Border() = default;
	~Border();

	
	Border(int L, int R, int T, int B) : left(L), right(R), top(T), bottom(B) {};
	int Width() const { return right - left; }
	int Height() const { return bottom - top; }
	bool Inside(const Border& other);
	bool Outside(const Border& other);

	void Translate(int bx, int by);

	void ClipTo(const Border& other);

	
};

