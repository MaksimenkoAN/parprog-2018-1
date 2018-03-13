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

	FILE * in;
	in = fopen(argv[1], "rb");//�������� ����� ��� ��������� ������

	if (in == nullptr) {
		std::cout << "���� ��� ������ �� ����� ���� ������" << std::endl;
		return 2;
	}

	int N;//������ �������
	double time;//����� ������

	fread(&time, sizeof(time), 1, in);
	fread(&N, sizeof(N), 1, in);

	Sole * S = new Sole(N);//������ ����

	for (int i = 0; i < N; i++)
		fread(S->A[i], sizeof(**S->A), N, in);
	fread(S->b, sizeof(*S->b), N, in);
	fread(S->x, sizeof(*S->x), N, in);

	fclose(in);

	std::cout << "����� ������ " << time << std::endl;
	S->Print();

	return 0;
}
