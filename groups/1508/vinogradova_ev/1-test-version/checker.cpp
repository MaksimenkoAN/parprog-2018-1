//�������� ������������ ������������ ������
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <string> 

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

	//   �������� ����������� �������, ��� ������� �������� ���� �� ��������� verdict
	void write_verdict(verdict v) {
		write_type(ext_cls::VERDICT);
		fwrite(&v, sizeof (v), 1, bur);
	} 

	//   �������� ��������� �� checker'a ������������.
	//   ��������, ��� ������� ������, ��� ��������.
	//   ������������ ������ ��������� ����� � ����� ����������

	void write_message(string str) {
		write_type(ext_cls::MESSAGE);
		int l = str.size();
		fwrite(&l, sizeof (l), 1, bur);
		fwrite(&str[0], sizeof (str[0]), l, bur);
	} 

	//   �������� ����������� ������� ����� ������ ��������� ���������,
	//   ����������� � ������� before_code
	//   x ����� ����������� 100 �� = 10 ^ (-7) ���

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


int main(int argc, char * argv[]) {
	char* help = "Expected parameters: <output file name> <answer file name>";
	if (argc != 3 || !strcmp(argv[1], "help")) {
		printf("%s", help);
		return 0;
	}

	FILE * buo = fopen(argv[1], "rb");
	FILE * bua = fopen(argv[2], "rb"); 
	int width = 0,
		height = 0,
		type = 0;

	fread(&width, sizeof(width), 1, buo);
	fread(&height, sizeof(height), 1, buo);
	fread(&type, sizeof(type), 1, buo);

	int *res = new int[width * height],
		*ans = new int[width * height];
	double res_time = 0; 

	fread(res, sizeof(*res), width * height, buo);
	fread(&res_time, sizeof(res_time), 1, buo);

	int buf;
	fread(&buf, sizeof(buf), 1, bua);
	fread(&buf, sizeof(buf), 1, bua);
	fread(&buf, sizeof(buf), 1, bua);
	fread(ans, sizeof(*ans), width * height, bua);

	int diff = 0;
	for (int i = 0; i < width * height; i++)
		diff += ans[i] - res[i]; 

	if (diff == 0) {
		checker_result.write_message ("AC. Numbers are equal.");
		checker_result.write_verdict (verdict::AC);
	}
	else {
		checker_result.write_message ("WA. Output is not correct.");
		checker_result.write_verdict (verdict::WA);
	}

	checker_result.write_time (res_time * 1e7); 
	fclose(bua);
	fclose(buo);
	delete[] res;
	delete[] ans;
	return 0;
}