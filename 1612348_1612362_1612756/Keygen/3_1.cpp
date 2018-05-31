#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

#define CHAR_MAX 255

template <class T>
void Swap(T& a, T& b) {
     T temp = a;
     a = b;
     b = temp;
}

string operator^(const string& a, const string& b) {
	if (a.length() != b.length())
		return "";
	string result;
	for (int i = 0; i < a.size(); i++)
		result.push_back(a[i] ^ b[i]);
	return result;
}

string operator^=(string& a, const string& b) {
       a = a ^ b;
       return a;
}

string getSubId(string id);

//256 ký tự: 00 - FF
string getDataString();

//Hoán vị các phần tử trong data dựa vào username
void fixData(string& data, string id);

//Lấy ra 8 bộ dữ liệu (mỗi bộ 4 ký tự từ data)
vector<string> pickUpData(string data);

//Lấy ra 16 ký tự từ Data
//Những ký tự này là key đúng lúc chạy 3_1.exe
string getSubPass(string data, string subId);

//Chuyển SubPass thành các ký tự được sinh ra từ password trong 3_1.exe
string convertSubPass(string subPass, const vector<string>& pickUp);

void Reverse(string& a);

void Xor(string& a, string& b, const vector<string>& pickUp);

//Lấy password đúng
string getPass(string subPass);

char fixPass(char pass);



void main() {
	string username;
	cout << "Enter username: ";
	getline(cin, username);
	while (username.size() < 7) {
		cout << "Username must be at least 7 characters!" << endl << "Again: ";
		getline(cin, username);
	}
    string data = getDataString();
    fixData(data, username);
    vector<string> pickUp = pickUpData(data);
    string subPass = getSubPass(data, getSubId(username));
    string p = convertSubPass(subPass, pickUp);
    p = getPass(p);
	cout << "Password: " << p << endl;
	system("pause");
}

string getSubId(string id) {
    string s, result;
    result = id;
    result.resize(16, '\0');
    int i = 0;
    while (i < 16) {
          int j = i % id.size();
          char c2 = result[j];
          c2 += id.size();
          c2 %= 255;
          result[i] = c2;
          i++;
    }
    return result;
}

string getDataString() {
       string result;
       for (int i = 0; i <= CHAR_MAX; i++)
           result.push_back(i);
       return result;       
}

void fixData(string& data, string id) {
     int i = 0, pos = 0;
     while (i <= CHAR_MAX) {
           pos += (data[i] + id[i % id.size()]);
           pos &= 0xFF;
           Swap(data[i], data[pos]);
           i++;
     }
}

vector<string> pickUpData(string data) {
               vector<string> result;
               string s;
               s = data[0x21];
               s += data[0x16];
               s += data[0xC];
               s += data[0];
               result.push_back(s);
               s = data[0x94];
               s += data[0x21];
               s += data[0x29];
               s += data[0xA];
               result.push_back(s);
               s = data[0xBE];
               s += data[0x11];
               s += data[0xF];
               s += data[0x14];
               result.push_back(s);
               s = data[0xBC];
               s += data[0x37];
               s += data[0x3D];
               s += data[0x1E];
               result.push_back(s);
               s = data[0xE6];
               s += data[0x1D];
               s += data[0x58];
               s += data[0x28];
               result.push_back(s);
               s = data[0xFA];
               s += data[0x3F];
               s += data[0xA];
               s += data[0x32];
               result.push_back(s);
               s = data[0xCA];
               s += data[0x49];
               s += data[0x5B];
               s += data[0x3C];
               result.push_back(s);
               s = data[0xFF];
               s += data[0x7C];
               s += data[0xA];
               s += data[0x46];
               result.push_back(s);
               return result;
}

//16 ky tu sau ham 8bb
string getSubPass(string data, string subId) {
       string result;
       for (int i = 0; i < subId.size(); i++) {
           int j = subId[i];
           j &= 0xFF;
           result += data[j];
       }
       return result;
}

string convertSubPass(string subPass, const vector<string>& pickUp) {
     string a1, a2, b1, b2;
     b1 = subPass.substr(0, 4);
     a1 = subPass.substr(4, 4);
     b2 = subPass.substr(8, 4);
     a2 = subPass.substr(12, 4);
     
     Reverse(a1);
     Reverse(a2);
     Reverse(b1);
     Reverse(b2);
     
     Xor(a1, b1, pickUp);
     Xor(a2, b2, pickUp);
     
     Reverse(a1);
     Reverse(a2);
     Reverse(b1);
     Reverse(b2);
     
     return (a1 + b1 + a2 + b2);
}

void Reverse(string& a) {
     for (int i = 0; i < a.size() / 2; i++)
         Swap(a[i], a[a.size() - 1 - i]);     
}

void Xor(string& a, string& b, const vector<string>& pickUp) {
        int i = 0;
        while (i < pickUp.size()) {
              b ^= a;
              b ^= pickUp[i];
              string t = a;
              a = b;
              b = t;
              i++;
        }
}

string getPass(string subPass) {
       string result;
       subPass += char(0);
       subPass += char(0);
       
       int i = 0;
       while (i < subPass.size()) {
             int a = subPass[i], b = subPass[i + 1], c = subPass[i + 2];
             a &= 0xFF; b &= 0xFF; c &= 0xFF;
             
             char x = 0, y = 0, z = 0, t = 0;
             t = c;
             z |= ((c & 0xC0) >> 6);
			 t &= ((1 << 6) - 1);
             
             z |= ((b & 0x3F) << 2);
             y |= ((b & 0xF0) >> 4);
			 z &= ((1 << 6) - 1);
             
             y |= ((a & 0x0F) << 4);
             x |= ((a & 0xFC) >> 2);
			 y &= ((1 << 6) - 1);
       
             result += fixPass(x);
             result += fixPass(y);
             result += fixPass(z);
             result += fixPass(t);
             
             i+=3;  
       }
       
       return result;
}



char fixPass(char pass) {
     char result;
     string tempData = "|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq.";
     if (pass != 0xFF) {
        pass += 0x3E;
        result = tempData.find_first_of(pass);
        result += 0x2B;
     }
	 else {
		 result = 0x41;
	 }
     return result;
}