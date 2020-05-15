#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

using matrix = vector<vector<int>>;//bool = can we change the value?
using coord = pair<int, int>;


class Sudoku
{
private:
	matrix board;
	bool solve(matrix& _board);
	bool valid(matrix& _board, coord pos, int num);
	coord find(matrix& _board);
public:
	Sudoku();
	Sudoku(const string& filename);
	void print_board();
	void open_board(const string& filename);


	void test();
	void solve();
	
};


void Sudoku::test()
{
	cout << "testing " << endl;
}

Sudoku::Sudoku()
{
	open_board("puzzle_01.txt");
}

Sudoku::Sudoku(const string& filename)
{
	open_board(filename);
}

void Sudoku::open_board(const string& filename)
{
	ifstream read; read.open(filename);
	string line;
	vector<int> conv;
	while (read >> line)
	{
		for (const char& c : line)
		{
			int val = (int)c - 48;
			conv.push_back(val);
		}
		this->board.push_back(conv);
		conv.clear();
	}
	read.close();
}

void Sudoku::solve()
{
	solve(this->board);
}

bool Sudoku::solve(matrix& _board)
{
	coord f = find(_board);
	int r, c;
	if (f.first != -1)
	{
		r = f.first;
		c = f.second;
	}
	else
		return true;
	for (int x = 1; x < 10; ++x)
	{
		if (valid(_board, coord(r,c), x))
		{
			_board[r][c] = x;
			if (solve(_board))
				return true;
			_board[r][c] = 0;
		}
	}
	return false;
}


bool Sudoku::valid(matrix& _board,coord pos, int num)
{
	//check in current row
	for (int x{}; x < 9; ++x)
	{
		if (_board[pos.first][x] == num
			&& x != pos.second)
			return false;
	}
	//check in current col
	for (int x{}; x < 9; ++x)
	{
		if (_board[x][pos.second] == num
			&& x != pos.second)
			return false;
	}

	//check in box
	int x = pos.first / 3;
	int y = pos.second / 3;
	for (int i = x * 3; i < x * 3 + 3; ++i)
	{
		for (int j = y * 3; j < y * 3 + 3; ++j)
		{
			if (_board[i][j] == num && i != pos.first && j != pos.second)
				return false;
		}
	}
	return true;
}

coord Sudoku::find(matrix& _board)
{
	//returns the first coordinates that are a 0
	for (int x{}; x < 9; ++x)
	{
		for (int y{}; y < 9; ++y)
		{
			if (_board[x][y] == 0)
				return coord(x, y);
		}
	}
	return (coord(-1, -1));
}

void Sudoku::print_board()
{
	cout << "Board:" << endl;
	for (const vector<int>& row : this->board)
	{
		for (const int& val : row)
			cout << " " << val;
		cout << endl;
	}
	cout << endl;
}