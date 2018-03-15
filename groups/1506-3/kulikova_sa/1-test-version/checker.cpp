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


//argv[1] - ��� ����� ���������, argv[2] - ��� ����� ����
int main(int argc, char * argv[]) {
	setlocale(LC_ALL, "Russian");//���������� ����������� ���������

	if (argc != 3) {
		std::cout << "������������ ������" << std::endl;
		return 1;
	}

	// ��������� ���� �������� ������ � ����� ���������  
	FILE * buo = fopen(argv[1], "rb"); 
	FILE * bua = fopen(argv[2], "rb");

	if (buo == nullptr) {
		std::cout << "���� ��������� �� ����� ���� ������" << std::endl;
		return 2;
	}

	if (bua == nullptr) {
		std::cout << "���� ���� �� ����� ���� ������" << std::endl;
		return 3;
	}

	// ����� ������ ���������
	double res_time;

	// ��������� ����� ������ ��������� ���������
	fread(&res_time, sizeof(res_time), 1, buo);

	int n; 
	// ��������� ����������� ������ 
	fread(&n, sizeof (n), 1, buo);

	if (n < 1) {
		std::cout << "�� ������������� ������ �������" << std::endl;
		fclose(buo);
		fclose(bua);
		return 3;
	}

	// �������� ������ ��� ����, ������ ���� � ������ ��������� 
	Sole * S = new Sole(n);// ���������
	double * ans = new double[n];

	// ��������� ����
	for (int i = 0; i < n; i++)
		fread(S->A[i], sizeof(**S->A), n, buo);
	fread(S->b, sizeof(*S->b), n, buo);

	// ��������� ����� ��������� � ����
	fread(S->x, sizeof (*S->x), n, buo);
	fread(ans, sizeof(*ans), n, bua);

	double res1 = 0, res2 = 0;
	for (int i = 0; i < n; i++) {
		res1 += S->A[0][i] * S->x[i];
		res2 += S->A[0][i] * ans[i];
	}
	std::cout << res1 << " - " << res2 << " = " << S->b[0] << std::endl;

	fclose(bua);
	fclose(buo);

	// ��������� ������, ��� ������� ����� �������� ������� 
	double diff = 0.0; 
	for (int i = 0; i < n; i++) 
		diff += (ans[i] - S->x[i]) * (ans[i] - S->x[i]);

	// ���������, ��� ������ ����, ����� ��������, ��� ������� ���������, ����� - �����������. 
	if (diff < 1e-6) { 
		std::cout << "���������" << std::endl;
		checker_result.write_message ("AC. Numbers are equal."); 
		checker_result.write_verdict (verdict::AC); 
	} 
	else { 
		std::cout << "�� ���������" << std::endl;
		checker_result.write_message ("WA. Output is not correct."); 
		checker_result.write_verdict (verdict::WA); 
	}

	delete[] ans;

	// ���������� ����� � ���������� ����������� (��������� �� 100 �� = 10 ^ (-7) ���). 
	checker_result.write_time (res_time * 1e7);

	return 0;
}
