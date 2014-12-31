#pragma once
#define NO_FILL -1
#define ALL_FILL -2
#define ERROR -3

int GetBin(int digital);
int GetDigital(int bin);

class CUnit
{
public:
	int m_fill;			//表示可填的数
	int m_dig;			//已填的数，0表示什么都没填

	CUnit();

	CUnit &operator =(int dig);
	bool operator ==(int dig);
};