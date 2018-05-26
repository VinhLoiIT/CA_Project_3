#include<iostream>
#include<stdio.h>
#include<string>
#include<cmath>
#define MAXLEN 100
using namespace std;

char serial[MAXLEN] = "";
char name[MAXLEN] = "";
char unknow[MAXLEN] = "";

void call_1(char*ESI, char*EDX, char*EDI)
{
	ESI = name;
	EDX = name;
	EDI = unknow;

	int i = 4;
	while (i != 0)
	{
		EDI[0] = (((ESI[0] ^ EDX[0]) & 95) | 64) | 9;
		EDI++;
		ESI++;
		EDX++;
		i--;
	}
	EDI[0] = 36;
}

void call_2(char*ESI, char*EDX, char*EDI)
{
	ESI = name;
	EDX = name;
	EDI = unknow + 5;

	int i = 4;
	while (i != 0)
	{
		EDI[0] = (((ESI[0] ^ EDX[0]) & 63) | 48) | 9;
		EDI++;
		ESI++;
		EDX++;
		i--;
	}
	EDI[0] = 0;
}

string keygen()
{
	char*ESI = nullptr, *EDX = nullptr, *EDI = nullptr;

	call_1(ESI, EDX, EDI);
	call_2(ESI, EDX, EDI);
	char result[MAXLEN] = "";
	ESI = result;
	EDX = unknow;
	while (EDX[0] != 0)
	{
		ESI[0] = EDX[0] ^ 9;
		EDX++;
		ESI++;
	}
	ESI[0] = 0;
	return string(result);
}

int main()
{
	string s;
	cout << "----------------------BAI 2.1-------------------" << endl;
	while (s.length() < 5)
	{
		cout << "Nhap name (>=5 ki tu): ";
		getline(cin, s);
	}
	strcpy_s(name, s.c_str());
	cout << "Serial: "<<keygen() << endl;
	getchar();
	return 0;
}