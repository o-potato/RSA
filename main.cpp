#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "des.h"
#include "rsa.h"

using namespace std;

int main()
{
	int mode;
	cout << "请选择加密模式 or 解密模式：" << endl << "0 - 加密" << endl << "1 - 解密" << endl;
	cin >> mode;

	string file_path;
	cout << "请输入密钥文件(.txt文件)路径：" << endl;
	cin >> file_path;

	//创建一个文件流对象,并打开存储密钥的.txt文件
	ifstream keyfile(file_path.c_str());
	if (!keyfile) {
		cout << "Unable to open the file!" << endl;
		exit(1);
	}
	//获取密钥
	string key;
	keyfile >> key;
    
    //RSA
    ofstream ci_key_rsa("ci_key_ras.txt");
    ofstream pl_key_rsa("pl_key_rsa.txt");
    key_pair * p = gen_key_pair();
    //cout << p->d << endl;
    //cout << p->e << endl;
    //cout << p->n << endl;
    //cout << "key:    " << key.c_str() << endl;
    char * ci_key = encrypt(key.c_str(), p->n, p->e);
    //cout << "ci_key; " << ci_key << endl;
    ci_key_rsa << ci_key;
    char * pl_key = decrypt(ci_key, p->n, p->d);
    //cout << "pl_key: " << pl_key << endl;
    pl_key_rsa << pl_key;

    
	cout << "请输入需加密/解密文件(.txt文件)的路径：" << endl;
	cin >> file_path;
	//打开存储需加密/解密的文件
	ifstream datafile(file_path.c_str());
	if (!datafile) {
		cout << "Unable to open the file!" << endl;
		exit(1);
	}
	//将文件读入到ostringstream字符串流对象buf中
	ostringstream buf;
	buf << datafile.rdbuf(); // 把文件流中的字符输入到字符串流中
	//返回与流对象buf关联的字符串
	string text = buf.str();
	//cout << "data: ";
	//cout << text << endl << endl;

	//char c = '0';
	//cout << text.length() << endl;
	//cout << text << endl;
	while ((text.length() - 1) % 64 != 0)	//明文不足64位自动补0
		text = text + '0';
	//cout << text.length() << endl;
	//cout << text << endl;

	string cipher;
	string plaintext;
	ofstream result_file("result.txt");

	//使用分组链接模式
	string init_vector = pl_key;	//设定分组链接的初始向量为密钥
	if (mode == 0) {
		cipher = CBC(text, pl_key, init_vector, en);
		result_file << cipher;
	}
	if (mode == 1) {
		plaintext = CBC(text, pl_key, init_vector, de);
		result_file << plaintext;
	}

	cout << "Your result is saved in result.txt!" << endl;

	keyfile.close();
	datafile.close();
	result_file.close();

	//system("pause");
	return 0;
}


//string byte2bit(string byte)
//{//字符串转比特串
//	int length = byte.length();
//	string bit(length * 8, 0);
//	for (int i = 0; i < length; i++) {
//		for (int j = 0; j < 8; j++) {
//			bit[i * 8 + j] = (byte[i] >> (7 - j)) & 1;
//		}
//	}
//	return bit;
//}

//string bit2byte(string bit)
//{//比特串转字符串
//	int length = bit.length() / 8;
//	string byte(length, 0);
//	for (int i = 0; i < length; i++)
//	{
//		byte[i] = 0;
//		for (int j = 0; j < 8; j++)
//			byte[i] = (byte[i] << 1) + bit[i * 8 + j];
//	}
//	return byte;
//}

//string hex2bit(string hex)
//{//十六进制字符串转比特串
//	int length = hex.length();
//	string bit(length * 4, 0);
//	for (int i = 0; i < length; i++)
//	{
//		hex[i] -= 48;
//		if (hex[i] > 9)
//			hex[i] -= 7;
//		for (int j = 0; j < 4; j++)
//			bit[i * 4 + j] = (hex[i] >> (3 - j)) & 1;
//	}
//	return bit;
//}

//string bit2hex(string bit)
//{//比特串转十六进制字符串
//	int length = bit.length() / 4;
//	string hex(length, 0);
//	for (int i = 0; i < length; i++)
//	{
//		hex[i] = 0;
//		for (int j = 0; j < 4; j++)
//			hex[i] = (hex[i] << 1) + bit[i * 4 + j];
//		hex[i] += 48;
//		if (hex[i] > 57)
//			hex[i] += 7;
//	}
//	return hex;
//}

//void output(string s)
//{//输出二进制字符串
//	cout << s.length() << "\t";
//	for (int i = 0; i < s.length(); i++)
//	{
//		if (s[i] == 1)
//			cout << 1;
//		else
//			cout << 0;
//	}
//	cout << endl;
//}

