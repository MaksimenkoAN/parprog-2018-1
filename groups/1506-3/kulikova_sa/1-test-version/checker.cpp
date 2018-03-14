#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <cmath> 
#include <string>
#include "Sole.h"

// ������������ ��� �������������� � ����������� ��������
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

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class result {
private: 
	FILE * bur; 
public: 
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };

	result(bool read = false) { 
		if (read) 
			bur = fopen("result.txt", "r"); 
		else 
			bur = fopen("result.txt", "w"); 
	} 

	~result() { 
		fclose(bur); 
	} 

	void write_type(ext_cls t) { 
		fwrite(&t, sizeof(t), 1, bur); 
	}

	// �������� ����������� �������, ��� ������� �������� ���� �� ��������� verdict 
	void write_verdict(verdict v) { 
		write_type(ext_cls::VERDICT); 
		fwrite(&v, sizeof (v), 1, bur); 
	}

	// �������� ��������� �� checker'a ������������. 
	// ��������, ��� ������� ������, ��� ��������. 
	// ������������ ������ ��������� ����� � ����� ���������� 
	void write_message(std::string str) { 
		write_type(ext_cls::MESSAGE); 
		int l = str.size (); 
		fwrite(&l, sizeof (l), 1, bur); 
		fwrite (&str[0], sizeof (str[0]), l, bur); 
	}

	// �������� ����������� ������� ����� ������ ��������� ���������, 
	// ����������� � ������� before_code 
	// x ����� ����������� 100 �� = 10 ^ (-7) ��� 
	void write_time(long long x) { 
		write_type(ext_cls::TIME); 
		fwrite(&x, sizeof (x), 1, bur); 
	}

	// �������� ����������� �������, ������ ������������� ���������� ��������� 
	void write_memory(unsigned long long x) { 
		write_type(ext_cls::MEMORY); 
		fwrite(&x, sizeof (x), 1, bur); 
	} 

} checker_result;


//argv[1] - ��� ��������� �����, argv[2] - ��� ����� ������
int main(int argc, char * argv[]) {
	// ��������� ���� �������� ������ � ����� ���������  
	FILE * buo = fopen(argv[1], "rb"); 
	FILE * bua = fopen(argv[2], "rb");

	// ����� ������ ��������� � ����� ������ ����
	double ans_time, res_time;

	// ��������� ����� ������ ��������� ��������� � ����
	fread(&res_time, sizeof(res_time), 1, buo);
	fread(&ans_time, sizeof(ans_time), 1, bua);

	int n; 
	// ��������� ����������� ������ 
	fread(&n, sizeof (n), 1, buo);

	// �������� ������ ��� ����, ������ ���� � ������ ��������� 
	Sole * S = new Sole(n);// ���������
	double * ans = new double[n], * res = new double[n]; 

	// ��������� ����
	for (int i = 0; i < n; i++)
		fread(S->A[i], sizeof(**S->A), n, buo);
	fread(S->b, sizeof(*S->b), n, buo);

	// ��������� ����� ��������� 
	fread(res, sizeof (*res), n, buo);

	// ��������� ����� ���� 
	fread(ans, sizeof (*ans), n, bua);

	// ��������� ������, ��� ������� ����� �������� ������� 
	double diff = 0.0; 
	for (int i = 0; i < n; i++) 
		diff += (ans[i] - res[i]) * (ans[i] - res[i]);

	// ���������, ��� ������ ����, ����� ��������, ��� ������� ���������, ����� - �����������. 
	if (diff < 1e-6) { 
		checker_result.write_message ("AC. Numbers are equal."); 
		checker_result.write_verdict (verdict::AC); 
	} 
	else { 
		checker_result.write_message ("WA. Output is not correct."); 
		checker_result.write_verdict (verdict::WA); 
	}

	// ���������� ����� � ���������� ����������� (��������� �� 100 �� = 10 ^ (-7) ���). 
	checker_result.write_time (res_time * 1e7);

	fclose(bua); 
	fclose(buo);

	return 0;
}
