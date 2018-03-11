#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Sole.h"

//���������� �������� ����
//argv[1] - ��� �������� �����
int main(int argc, char * argv[]) {
	setlocale(LC_ALL, "Russian");//���������� ����������� ���������

	if (argc != 2) {
		std::cout << "������������ ������" << std::endl;
		return 1;
	}

	FILE * out;
	out = fopen(argv[1], "rb");//�������� ����� ��� ��������� ������

	int N;//������ �������
	double time;//����� ������

	fread(&time, sizeof(time), 1, out);
	fread(&N, sizeof(N), 1, out);

	Sole * S = new Sole(N);//������ ����

	for (int i = 0; i < N; i++)
		fread(S->A[i], sizeof(**S->A), N, out);
	fread(S->b, sizeof(*S->b), N, out);
	fread(S->x, sizeof(*S->x), N, out);

	std::cout << "����� ������ " << time << std::endl;
	S->Print();

	return 0;
}
