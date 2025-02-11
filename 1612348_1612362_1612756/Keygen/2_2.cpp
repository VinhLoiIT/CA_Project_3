// Keygen.cpp : Defines the entry point for the console application.
//
#include <Windows.h>

#define _CRT_SECURE_NO_WARNINGS

#define BUFFER_SIZE 256
#define KEY_LEN (BUFFER_SIZE * 2)
#define SERIAL_LEN 7
#define USERNAME_LEN 5

const char* cra = "admirable";
const char* hac = "154";

bool is_number(const char* str)
{
	for (unsigned int i = 0; i < strlen(str); i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

void keygen(const char* username, const char* serial, char* key)
{
	char fi[2], si[2], th[2], fo[2], fif[3];
	memset(fi, 0, 2);
	memset(si, 0, 2);
	memset(fo, 0, 2);
	memset(th, 0, 2);
	memset(fif, 0, 3);

	// set fi=%N:~2,1%
	strncpy(fi, username + 2, 1); fi[1] = 0;
	// set si=%N:~3,1%
	strncpy(si, username + 3, 1); si[1] = 0;
	// set th=%N:~1,1%
	strncpy(th, username + 1, 1); th[1] = 0;
	// set fo=%N:~4,1%
	strncpy(fo, username + 4, 1); fo[1] = 0;
	// set fif=%N:~0,2%
	strncpy(fif, username + 0, 2); fif[2] = 0;
	// set name=%fif%%fo%%si%%fi%%th%
	char name[7];
	memset(name, 0, 7);
	sprintf(name, "%s%s%s%s%s", fif, fo, si, fi, th);

	//set /a m=%one%*%two%*%three%*%four%*%five%*%six%*%seven%*3
	int num = 3;
	for (int i = 0; i < SERIAL_LEN; i++)
	{
		num *= (serial[i] - '0');
	}

	char num_str[BUFFER_SIZE];
	memset(num_str, 0, BUFFER_SIZE);
	sprintf(num_str, "%d", num);

	char se1[5], se2[3], se3[2], se4[4];
	memset(se1, 0, 5);
	memset(se2, 0, 3);
	memset(se3, 0, 2);
	memset(se4, 0, 4);
	//set se1=%m:~0,4%
	strncpy(se1, num_str + 0, 4); se1[4] = 0;
	//set se2=%m:~0,2%
	strncpy(se2, num_str + 0, 2); se2[2] = 0;
	//set se4=%m:~1,3%
	strncpy(se4, num_str + 1, 3); se4[3] = 0;
	//set se3=%m:~2,1%
	strncpy(se3, num_str + 2, 1); se3[1] = 0;

	//set se5=%se4%%th%%se3%%si%%se1%%fi%%fif%%se2%
	char se5[BUFFER_SIZE];
	memset(se5, 0, BUFFER_SIZE);
	sprintf(se5, "%s%s%s%s%s%s%s%s", se4, th, se3, si, se1, fi, fif, se2);

	//set la=%se5%%cra%%hac%%name%
	memset(key, 0, KEY_LEN);
	sprintf(key, "%s%s%s%s", se5, cra, hac, name);
}

int main(void)
{
	char username[BUFFER_SIZE];
	char serial[BUFFER_SIZE];
	char key[KEY_LEN];

	memset(username, 0, BUFFER_SIZE);
	memset(serial, 0, BUFFER_SIZE);
	memset(key, 0, KEY_LEN);

	printf("Enter username:\n");
	fgets(username, BUFFER_SIZE, stdin);
	username[strlen(username) - 1] = '\0';


	do
	{
		printf("Enter serial (must be number and 7 digits or more):\n");
		fgets(serial, BUFFER_SIZE, stdin);
		serial[strlen(serial) - 1] = '\0';
	} while (strlen(serial) < SERIAL_LEN || !is_number(serial));

	keygen(username, serial, key);
	printf("Key: %s\n", key);


	return 0;
}