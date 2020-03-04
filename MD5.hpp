#ifndef _MD5_HPP_
#define _MD5_HPP_

#include<iostream>
#include<string>
using namespace std;

//����ѭ�����ƺ��� 
#define RPTATE_SHIFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

//����F,G,H,I���� 
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))    
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

//����Ĵ���word A,B,C,D

#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476
//strBaye�ĳ���
unsigned int strlength = 0;
//A,B,C,D����ʱ����
int tempA = 0, tempB = 0, tempC = 0, tempD = 0;
//����k���飬����ѹ������ 
const unsigned int k[] = {
	0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
	0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,0xa679438e,0x49b40821,
	0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
	0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
	0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
	0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
	0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
	0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391 };

//������洢����λ�������������
//ÿһ�� ��ʾһ�ֵ���λ���� �� ���� RFC 1321�ı�׼�������� 
const unsigned int s[] = { 7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21 };

//����ת��16���� 
const char str16[] = "0123456789abcdef";


string getMD5Code(string source);
unsigned int* padding(string str);
void MD5compress(unsigned int M[]);
string changeToHex(int num);


string getMD5Code(string source) {
	//��ʼ��

	tempA = A;
	tempB = B;
	tempC = C;
	tempD = D;

	//��string��ɶ����ƣ� ͬʱ�������λ 
	unsigned int *strByte = padding(source);

	//   ����i = 0��N / 16-1 ����i���Ƶ�X.
	//     ����j = 0��15��
	//       ��X [j]����ΪM [i * 16 + j]��
	//   ����ѹ���������� 

	for (int i = 0; i<strlength / 16; i++) {

		unsigned int num[16];

		for (int j = 0; j<16; j++) {
			num[j] = strByte[i * 16 + j];
		}

		MD5compress(num);
	}
	//�ѵõ���ժҪ2���Ʊ��16�����ַ������ 
	return changeToHex(tempA).append(changeToHex(tempB)).append(changeToHex(tempC)).append(changeToHex(tempD));
}

/*
*��亯��
*�����Ӧ����bits��448(mod512)
*��䷽ʽΪ�ȼ�һ��1,����λ����
*������64λ��ԭ������
*/
unsigned int* padding(string str) {
	//��512λ,64���ֽ�Ϊһ�飬 num��ʾ������ �����������ֱ�ӵõ�����

	unsigned int num = ((str.length() + 8) / 64) + 1;

	//����һ����Ҫ16���������洢 16*4=64�� strByte��ʾ���ַ�����2���Ʊ�ʾ��������int�����ʾ�� 
	unsigned int *strByte = new unsigned int[num * 16];

	//��ʼ���ַ����ĳ��ȣ�������16*������ 
	strlength = num * 16;

	//��ʼ�� strByte���� 
	for (unsigned int i = 0; i < num * 16; i++) {
		strByte[i] = 0;
	}
	//һ�������洢�ĸ��ֽڣ�һ��unsigned int��Ӧ4���ֽڣ�����4���ַ���Ϣ

	for (unsigned int i = 0; i <str.length(); i++) {
		strByte[i / 4] |= (str[i]) << ((i % 4) * 8);
	}
	//β�����1 һ��unsigned int����4���ַ���Ϣ,������128����
	strByte[str.length() / 4] |= 0x80 << (((str.length() % 4)) * 8);
	/*
	*���ԭ���ȣ�����ָλ�ĳ��ȣ�����Ҫ��8��Ȼ����С�������Է��ڵ����ڶ���,���ﳤ��ֻ����32λ
	*/
	strByte[num * 16 - 2] = str.length() * 8;
	return strByte;

}


//MD5 ѹ������ Hmd5 
void MD5compress(unsigned int M[]) {
	int f = 0, g = 0;
	int a = tempA, b = tempB, c = tempC, d = tempD;

	/*��1�ֵ�����
	*X[j] , j = 1..16.
	*��2�ֵ�����
	*X[p2(j)], p2(j) = (1 + 5j) mod 16, j = 1..16.
	*��3�ֵ�����
	*X[p3(j)], p3(j) = (5 + 3j) mod 16, j = 1..16.
	*��2�ֵ�����
	*X[p4(j)], p4(j) = 7j mod 16, j = 1..16*/

	for (int i = 0; i < 64; i++) {

		if (i<16) {
			f = F(b, c, d);
			g = i;
		}
		else if (i<32) {
			f = G(b, c, d);
			g = (5 * i + 1) % 16;
		}
		else if (i<48) {
			f = H(b, c, d);
			g = (3 * i + 5) % 16;
		}
		else {
			f = I(b, c, d);
			g = (7 * i) % 16;
		}
		//ÿ��ѭ��ʹ����ͬ�ĵ����߼��� 4*16 �������Ԥ�������, Ҳ����ǰ���k�� 
		unsigned int tmp = d;
		d = c;
		c = b;
		b = b + RPTATE_SHIFT((a + f + k[i] + M[g]), s[i]);
		a = tmp;

	}
	tempA = a + tempA;
	tempB = b + tempB;
	tempC = c + tempC;
	tempD = d + tempD;
}


//�����ֱ�Ϊ2���� ���ַ������ 
string changeToHex(int num) {
	int b;
	string tmp;
	string str = "";

	for (int i = 0; i<4; i++) {
		tmp = "";
		b = ((num >> i * 8) % (1 << 8)) & 0xff;   //������ÿ���ֽ�
		for (int j = 0; j < 2; j++) {
			tmp.insert(0, 1, str16[b % 16]);
			b = b / 16;
		}
		str += tmp;
	}
	return str;
}




#endif  _MD5_HPP_
