#pragma once
#include "Unit.h"
#include "stdlib.h"

class CSudoku
{
public:
	CSudoku(){}
	CSudoku(int lattice[9][9]);
	~CSudoku(){}
	
	bool StartCount();
private:
	CUnit m_lattice[9][9];			//表示数独格子的矩阵

	void getStartPos(int i, int j, int &s_i, int &s_j);			//获取i, j所在九宫格的初始坐标
	int BitCount(int bit);			//计算二进制数有多少个1
};

