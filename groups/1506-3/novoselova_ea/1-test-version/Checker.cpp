#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <string>
#include <fstream>
#include<iostream>
using namespace std;
// ������������ ��� �������������� � ����������� ��������
////////////////////////////////////////////////////////////////////////////////////////////
/*
// Checker ����� ������������� ��� ��� ��� ��������:
AC = Accepted = ������� ����� ���������� ��������� �� ������ �����
WA = Wrong Answer = ������� ����� ������������ ��������� �� ������ �����
PE = Presentation Error = ������ ������� �������� ������
// ��������� �������� checker �� ����� �������������
NO = No verdict = ������� �����������
CE = Compilation Error = ������ ����������
ML = Memory Limit Exceeded = ��������� ����������� �� ������
TL = Time Limit Exceeded = ��������� ����������� �� ������� ������
RE = Runtime Error = ������ ������� ���������� ���������
IL = Idle Limit Exceeded = ��������� ����� ������� (�����������) ���������
DE = Deadly Error = ������ ����������� �������
*/
/*enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };
class result
{
private:
	FILE * bur;
public:
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };
	result(bool read = false)
	{
		if (read) bur = fopen("result.txt", "r"); else bur = fopen("result.txt", "w");
	}
	~result() { fclose(bur); }
	void write_type(ext_cls t) { fwrite(&t, sizeof(t), 1, bur); }
	// �������� ����������� �������, ��� ������� �������� ���� �� ��������� verdict
	void write_verdict(verdict v)
	{
		write_type(ext_cls::VERDICT); fwrite(&v, sizeof(v), 1, bur);
	}
	// �������� ��������� �� checker'a ������������.
	// ��������, ��� ������� ������, ��� ��������.
	// ������������ ������ ��������� ����� � ����� ����������
	void write_message(string str)
	{
		write_type(ext_cls::MESSAGE); int l = str.size(); fwrite(&l, sizeof(l), 1, bur);
		fwrite(&str[0], sizeof(str[0]), l, bur);
	}
	// �������� ����������� ������� ����� ������ ��������� ���������,
	// ����������� � ������� before_code
	// x ����� ����������� 100 �� = 10 ^ (-7) ���
	void write_time(long long x)
	{
		write_type(ext_cls::TIME); fwrite(&x, sizeof(x), 1, bur);
	}
	// �������� ����������� �������, ������ ������������� ���������� ���������
	void write_memory(unsigned long long x)
	{
		write_type(ext_cls::MEMORY); fwrite(&x, sizeof(x), 1, bur);
	}
} checker_result;*/

int MUL(int *MatrixA, int *MatrixB, int *MatrixC, int N);
int main(int argc, char *argv[])
{
	// ��������� ���� ������� ������, ���� �������� ������ � ����� ���������
	char *filein = "1";
	char *fileout = "1.ans";
	if (argc > 1)
	{
		filein = argv[1];
		fileout = argv[2];
	}

	int n;
	double time;
	int *a, *b, *ans, *res;
	freopen(filein, "rb", stdin);
	fread(&n, sizeof(n), 1, stdin);
	a = new int[n * n];
	b = new int[n * n];
	fread(a, sizeof(*a), n * n, stdin);
	fread(b, sizeof(*b), n * n, stdin);
	fclose(stdin);
	res = new int[n * n];
	ans = new int[n * n];
	freopen(fileout, "rb", stdin);
	fread(&time, sizeof(time), 1, stdin);
	fread(res, sizeof(*res), n * n, stdin);
	fclose(stdin);
	MUL(a, b, ans, n);
	double diff = 0.0;
	for (int i = 0; i < n * n; i++)
		diff += (ans[i] - res[i]) * (ans[i] - res[i]);
	
	std::ofstream resultFile("result.txt");
	if (diff < 1e-6)
	{
		if (resultFile.is_open())
		{

			resultFile << "AC. Numbers are equal";
		}
		
	}
	else
	{
		if (resultFile.is_open())
		{

			resultFile << "WA. Output is not correct";
		}
	}
	return 0;
}