#include <iostream>
#include "Unit.h"
#include "Sudoku.h"
using namespace std;

int main()
{
	int test[9][9] =
	{
		{6,1,0,0,0,0,9,2,0},
		{3,0,5,6,9,2,0,1,0},
		{0,0,0,0,8,1,6,0,7},
		{4,5,6,0,1,0,0,3,0},
		{1,2,3,4,0,0,7,6,8},
		{9,0,7,2,0,0,5,4,0},
		{5,0,0,0,0,0,0,8,0},
		{0,0,0,1,5,0,0,7,5},
		{0,6,0,0,0,0,4,9,0}
	};

	CSudoku sudo(test);
	sudo.StartCount();

	system("pause");
}