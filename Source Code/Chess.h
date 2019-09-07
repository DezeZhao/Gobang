#pragma once
class Chess {
private:
	int color;
	int x;
	int y;
public:
	Chess(int color, int x, int y);
	int GetColor();
	void GetPoint(int &x, int &y);
	void SetColor(int color);
	void SetPoint(int x, int y);
};

