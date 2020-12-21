//#pragma once
#include <iostream>
using namespace std;

typedef enum { en, de } MODE;
typedef const unsigned char TABLE;

// 初始置换IP表
static TABLE IP_Table[64] =
{
	58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};

// 逆初始置换IP1表
static TABLE IP1_Table[64] =
{
	40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25
};

// 扩展置换E表
static TABLE EXTENSION_Table[48] =
{
	32,  1,  2,  3,  4,  5,
	 4,  5,  6,  7,  8,  9,
	 8,  9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32,  1
};

// P盒置换表
static TABLE P_Table[32] =
{
	16, 7, 20, 21, 29, 12, 28, 17,  1, 15, 23, 26,  5, 18, 31, 10,
	 2, 8, 24, 14, 32, 27,  3,  9, 19, 13, 30,  6, 22, 11,  4, 25
};

// 密钥置换表
static TABLE KEY_Table[56] =
{
	57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
};

// 压缩置换表
static TABLE PC2_Table[48] =
{
	14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

// 每轮移动的位数
static TABLE SHIFT_Table[16] =
{
	1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

// S盒设计
static TABLE S_Box[8][4][16] =
{
	// S盒1
	14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
	 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
	 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
	15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
	// S盒2
	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
	// S盒3
	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
	// S盒4
	 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
	// S盒5
	 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
	// S盒6
	12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,
	// S盒7
	 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
	// S盒8
	13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};

//string byte2bit(string byte);
//string bit2byte(string bit);
//string hex2bit(string hex);
//string bit2hex(string bit);
//void output(string s);

string help_B2C(int i) {
	switch (i)
	{
	case 0: return "0000";
	case 1: return "0001";
	case 2: return "0010";
	case 3: return "0011";
	case 4: return "0100";
	case 5: return "0101";
	case 6: return "0110";
	case 7: return "0111";
	case 8: return "1000";
	case 9: return "1001";
	case 10: return "1010";
	case 11: return "1011";
	case 12: return "1100";
	case 13: return "1101";
	case 14: return "1110";
	case 15: return "1111";
	default:
		break;
	}
}

string transform(string bit, TABLE* table, int length)
{	//矩阵置换
	string tmp(length, '0');
	for (int i = 0; i < length; i++)
		tmp[i] = bit[table[i] - 1];
	return tmp;
}

void get_subkey(string* subkey, string key)
{//获取子密钥
	string transformed_key = transform(key, KEY_Table, 56);
	string C(transformed_key, 0, 28);
	string D(transformed_key, 28, 28);

	for (int i = 0; i < 8; i++)
	{
		C = C.substr(SHIFT_Table[i]) + C.substr(0, SHIFT_Table[i]);
		D = D.substr(SHIFT_Table[i]) + D.substr(0, SHIFT_Table[i]);
		subkey[i] = transform(C + D, PC2_Table, 48);
	}
}

string string_xor(string a, string b)
{//字符串异或
	string r;
	for (int i = 0; i < a.length(); i++) {
		if (a[i] == b[i])
			r = r + '0';
		else
			r = r + '1';
	}
		//a[i] = a[i] ^ b[i];
	return r;
}

string B2C(string B, int i)
{//使用S盒
	int iB[6];
	for (int j = 0; j < 6; j++) {
		if (B[j] == '0')
			iB[j] = 0;
		else
			iB[j] = 1;
	}
	int row = iB[0] * 2 + iB[5];
	int col = iB[1] * 8 + iB[2] * 4 + iB[3] * 2 + iB[4];
	int s = S_Box[i][row - 1][col - 1];
	string C;
	C = help_B2C(s);
	return C;
}

string function(string R, string K)
{//f函数
	string ER = transform(R, EXTENSION_Table, 48);
	string BS = string_xor(ER, K);
	string f;
	for (int i = 0; i < 8; i++)
	{
		string B(BS.substr(i * 6, 6));
		string C = B2C(B, i);
		f = f + C;
	}
	return f;
}

string iterative(string L, string R, string* K, MODE mode)
{//8轮迭代
	if (mode == en)
	{
		for (int i = 0; i < 8; i++)
		{
			string tmp(L);
			L = R;
			R = string_xor(tmp, function(R, K[i]));

			/*cout << "L" << i + 1 << ":\t";
			output(L);
			cout << "R" << i + 1 << ":\t";
			output(R);*/
		}
	}
	else
	{
		for (int i = 7; i >= 0; i--)
		{
			string tmp(R);
			R = L;
			L = string_xor(tmp, function(L, K[i]));

			/*cout << "L" << 16 - i << ":\t";
			output(L);
			cout << "R" << 16 - i << ":\t";
			output(R);*/
		}
	}
	return transform(L + R, IP1_Table, 64);
	cout << endl;
}

string des(string data, string key, MODE mode)
{//DES实现单块加解密
	/*string bit_data;
	if (mode == en)
		bit_data = byte2bit(data);
	else
		bit_data = hex2bit(data);*/
	//cout << "bit_data: ";
	//output(bit_data);

	data = transform(data, IP_Table, 64);
	string L(data, 0, 32);
	string R(data, 32, 32);

	string subkey[8];
	get_subkey(subkey, key);

	string result = iterative(L, R, subkey, mode);
	return result;
	/*if (mode == en)
		return bit2hex(result);
	else
		return bit2byte(result);*/
}


string CBC(string data, string key, string init_vector, MODE mode)
{//分组链接模式
	string result;
	string block;
	string tmp;
	string vector(init_vector);
	if (mode == en)
	{
		for (int i = 0; i < data.length() / 64; i++)
		{
			block = data.substr(i * 64, 64);
			//cout << block << endl;
			tmp = des(string_xor(block, vector), key, mode);
			//cout << "第 " << i + 1 << " 块:\t" << "cipher: " << tmp << endl << endl;
			vector = tmp;
			result = result + tmp;
		}
		cout << "Successfully encode! " << endl;
	}
	else
	{
		for (int i = 0; i<data.length() / 64; i++)
		{
			tmp = data.substr(i * 64, 64);
			block = string_xor(des(tmp, key, mode), vector);
			//cout << "第 " << i + 1 << " 块:\t" << "plaintext: " << block << endl << endl;
			vector = tmp;
			result = result + block;
		}
		cout << "Successfully decode! " << endl;
	}
	//cout << result << endl << endl;
	return result;
}