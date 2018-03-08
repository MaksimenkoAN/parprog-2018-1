#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include "Sole.h"

//���������� �������� ����
//argv[1] - ��� �������� �����
int main(int argc, char * argv[]) {
	setlocale(LC_ALL, "Russian");//���������� ����������� ���������

	if (argc != 2) {
		std::cout << "������������ ������" << std::endl;
		return 1;
	}

	freopen(argv[1], "rb", stdin);//�������� ����� ��� ��������� ������

	int N;//������ �������
	double time;//����� ������

	fread(&time, sizeof(time), 1, stdin);
	fread(&N, sizeof(N), 1, stdin);

	Sole * S = new Sole(N);//������ ����

	for (int i = 0; i < N; i++)
		fread(S->A[i], sizeof(**S->A), N, stdin);
	fread(S->b, sizeof(*S->b), N, stdin);
	fread(S->x, sizeof(*S->x), N, stdin);

	std::cout << "����� ������ " << time << std::endl;
	S->Print();

	return 0;
}