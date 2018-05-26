#include<iostream>
#include<string>
#include<cmath>

using namespace std;

int main()
{
	string ESI;
	cout << "----------------------BAI 1.1-------------------" << endl;
	cout << "Hardcoded: " << "Reversing raiser knowledge!"<<endl;
	cout << "Nhap name: ";
	getline(cin,ESI);
	int ECX = ESI.length();
	int EBX= 0;
	char EAX;
	while (ECX > 0)
	{
		EAX = ESI[ECX - 1];
	loop:
		{
			EBX++;
			EAX = EAX ^ EBX;
			if (EAX < 68 || EAX>77)
				goto loop;
		}
		ESI[ECX - 1] = EAX - 20;
		ECX--;
	}
	cout << "Serial: " <<ESI << endl;
	getchar();
	return 0;

}