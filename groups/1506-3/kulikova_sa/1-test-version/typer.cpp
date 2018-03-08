#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Sole.h"

//��������� ���� ����������� � ��������
//argv[1] - ��� �������� �����, argv[2] - ��� ��������� �����
int main(int argc, char * argv[]) {
	setlocale(LC_ALL, "Russian");//���������� ����������� ���������

	if (argc != 3) {
		std::cout << "������������ ������" << std::endl;
		return 1;
	}

	std::ifstream in(argv[1], std::ios::in);//�������� ����� ��� ������
	FILE * out;
	out = fopen(argv[2], "wb");//�������� ����� ��� �������� ������

	if (!in.is_open()) {
		std::cout << "���� ��� ������ �� ����� ���� ������" << std::endl;
		return 2;
	}

	if (out == nullptr) {
		std::cout << "���� ��� ������ �� ����� ���� ������" << std::endl;
		return 3;
	}

	int N;//������ �������
	in >> N;//��������� ������ �������

	if (N < 1) {
		std::cout << "������������ ������ �������" << std::endl;
		return 4;
	}

	fwrite(&N, sizeof(N), 1, out);
	Sole * S = new Sole(N);//������ ����

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			in >> S->A[i][j];//������ �������
			fwrite(&S->A[i][j], sizeof(S->A[i][j]), 1, out);
		}
	}
	for (int i = 0; i < N; i++) {
		in >> S->b[i];//������ ������� ��������� ������
		fwrite(&S->b[i], sizeof(S->b[i]), 1, out);
	}

	in.close();//�������� ������
	fclose(out);

	return 0;
}