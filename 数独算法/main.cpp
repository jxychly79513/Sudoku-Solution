#include <iostream>
#include "Unit.h"
#include "Sudoku.h"
using namespace std;

int main()
{
	int test[9][9] =
	{
		{0,0,0,1,0,0,0,2,9},
		{0,0,5,0,0,0,0,0,4},
		{0,6,8,0,0,0,0,0,0},
		{0,0,0,7,0,0,5,0,0},
		{0,2,0,0,6,0,0,8,0},
		{0,0,3,0,0,9,0,0,0},
		{0,0,0,0,5,0,1,6,0},
		{4,0,0,0,3,0,0,0,0},
		{7,0,0,0,0,2,0,0,0},
	};
	try
	{
		CSudoku sudo(test);
		if (!sudo.StartCount()) cout<<"Êý¶ÀÎÞ½â"<<endl;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				cout<<sudo.getDigit(i, j)<<" ";
			}
			cout<<endl;
		}
	}
	catch(int error)
	{
		exit(error);
	}

	system("pause");
	return 0;
}