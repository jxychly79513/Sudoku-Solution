#pragma once

#include <stack>
#include <stdlib.h>
#include "Unit.h"
using namespace std;



class CSudoku
{
public:
	CSudoku(){}
	CSudoku(int lattice[9][9]);
	~CSudoku(){}

	int getDigit(int i, int j);

	bool StartCount();

private:
	enum Flag
	{
		normal = 0,
		notonly,
		nosln
	};

	class CCache		//缓存状态
	{
	public:
		CCache(CUnit lattice[9][9], int i, int j, int digit);

		CUnit m_lattice[9][9];
		int m_i;
		int m_j;
		int m_digit;
	};
private:
	CUnit m_lattice[9][9];			//表示数独格子的矩阵
	stack<CCache> m_cache;			//存储缓存状态的栈

	void getStartPos(int i, int j, int &s_i, int &s_j);			//获取i, j所在九宫格的初始坐标
	int BitCount(int bit);			//计算二进制数有多少个1
	void updataFill(int i, int j);	//更新指定格子的可填的数
};

