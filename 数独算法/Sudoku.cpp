#include "Sudoku.h"

CSudoku::CSudoku(int lattice[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			m_lattice[i][j] = lattice[i][j];
		}
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (m_lattice[i][j] == 0)
			{updataFill(i, j);}
		}
	}
}

void CSudoku::getStartPos(int i, int j, int &s_i, int &s_j)
{
	bool isSuccess = true;

	/**
	j 
	i| 0 1 2 | 3 4 5 | 6 7 8 |
	-+-------+-------+-------+
	0|       |       |       |
	1|   1   |   4   |   7   |
	2|       |       |       |
	-+-------+-------+-------+
	3|       |       |       |
	4|   2   |   5   |   8   |
	5|       |       |       |
	-+-------+-------+-------+
	6|       |       |       |
	7|   3   |   6   |   9   |
	8|       |       |       |
	-+-------+-------+-------+
	*/
	if ( (i >= 0 && i <= 2) && (j >= 0 && j <= 2) )					//1
	{
		s_i = 0;
		s_j = 0;
	}
	else if ( (i >= 3 && i <= 5) && (j >= 0 && j <= 2) )			//2
	{
		s_i = 3;
		s_j = 0;
	}
	else if ( (i >= 6 && i <= 8) && (j >= 0 && j <= 2) )			//3
	{
		s_i = 6;
		s_j = 0;
	}
	else if ( (i >= 0 && i <= 2) && (j >= 3 && j <= 5) )			//4
	{
		s_i = 0;
		s_j = 3;
	}
	else if ( (i >= 3 && i <= 5) && (j >= 3 && j <= 5) )			//5
	{
		s_i = 3;
		s_j = 3;
	}
	else if ( (i >= 6 && i <= 8) && (j >= 3 && j <= 5) )			//6
	{
		s_i = 6;
		s_j = 3;
	}
	else if ( (i >= 0 && i <= 2) && (j >= 6 && j <= 8) )			//7
	{
		s_i = 0;
		s_j = 6;
	}
	else if ( (i >= 3 && i <= 5) && (j >= 6 && j <= 8) )			//8
	{
		s_i = 3;
		s_j = 6;
	}
	else if ( (i >= 6 && i <= 8) && (j >= 6 && j <= 8) )			//9
	{
		s_i = 6;
		s_j = 6;
	}
	else
	{
		isSuccess = false;
	}

	if(!isSuccess)
	{
		throw POS_ERROR;
	}
}

int CSudoku::BitCount(int bit)
{
	int count;
	for (count = 0; bit != 0; bit >>= 1)
	{
		count += bit & 1;
	}
	return count;
}

void CSudoku::updataFill(int i, int j)
{
	if (m_lattice[i][j] == 0)
	{
		for (int _i = 0; _i < 9; _i++)		//列
		{
			m_lattice[i][j].m_fill = m_lattice[i][j].m_fill & ~GetBin(m_lattice[_i][j].m_dig);
		}
		for (int _j = 0; _j < 9; _j++)		//行
		{
			m_lattice[i][j].m_fill = m_lattice[i][j].m_fill & ~GetBin(m_lattice[i][_j].m_dig);
		}
		/*九宫格*/
		int s_i, s_j;
		getStartPos(i, j, s_i, s_j);

		for (int _i = s_i; _i < s_i+3; _i++)
		{
			for (int _j = s_j; _j < s_j+3; _j++)
			{
				m_lattice[i][j].m_fill = m_lattice[i][j].m_fill & ~GetBin(m_lattice[_i][_j].m_dig);
			}
		}
	}
	else
	{
		m_lattice[i][j].m_fill = GetBin(NO_FILL);
	}
}

int CSudoku::getDigit(int i, int j)
{
	return m_lattice[i][j].m_dig;
}

bool CSudoku::StartCount()
{
	int c_fblank = 0;			//为判断是否找到空白单元格
	int c_fsingle = 0;			//为判断是否找到唯一数单元格

	do
	{
		c_fblank = 0;
		c_fsingle = 0;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (m_lattice[i][j] == 0)			//找空白单元格
				{
					updataFill(i, j);
					if ( BitCount(m_lattice[i][j].m_fill) == 1 )		//找唯一单元格
					{
						m_lattice[i][j] = GetDigital(m_lattice[i][j].m_fill);
						c_fsingle++;
					}
					c_fblank++;
				}
			}//end for
		}

		if (c_fsingle == 0)
		{
			//cout<<"无唯一数单元格"<<endl;
			break;
		}

	}while (c_fblank != 0);

	return true;
}