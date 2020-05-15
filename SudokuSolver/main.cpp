#include <iostream>
#include <vector>
#include <string>
#include "sudoku.hpp"

using namespace std;

int main()
{
	Sudoku s;
	cout << "--GIVEN--" << endl;
	s.print_board();

	s.solve();
	cout << "--SOLVED--" << endl;
	s.print_board();



	cin.get();
	return 0;
}