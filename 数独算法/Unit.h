#pragma once

#define NO_FILL			-1
#define ALL_FILL		-2

#define DIGITAL_ERROR	101
#define BIN_ERROR		102
#define POS_ERROR		103

int GetBin(int digital);
int GetDigital(int bin);

class CUnit
{
public:
	int m_fill;			//表示可填的数，是一个9位二进制数
	int m_dig;			//已填的数，0表示什么都没填

	CUnit();

	CUnit &operator =(int dig);
	bool operator ==(int dig);
};