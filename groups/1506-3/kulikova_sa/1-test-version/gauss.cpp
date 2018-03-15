#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Sole.h"

//https://prog-cpp.ru/gauss/
void gauss(double ** a, double * b, double * x, int n) {
	double max;
	int k, index;
	const double eps = 0.00001;  // ��������
	k = 0;
	while (k < n) {
		// ����� ������ � ������������ a[i][k]
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++) {
			if (abs(a[i][k]) > max) {
				max = abs(a[i][k]);
				index = i;
			}
		}
		// ������������ �����
		if (max < eps) {
			// ��� ��������� ������������ ���������
			std::cout << "������� �������� ���������� ��-�� �������� ������� " <<
				index << " ������� A" << std::endl;
			return;
		}
		for (int j = 0; j < n; j++) {
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		double temp = b[k];
		b[k] = b[index];
		b[index] = temp;
		// ������������ ���������
		for (int i = k; i < n; i++) {
			double temp = a[i][k];
			if (abs(temp) < eps) continue; // ��� �������� ������������ ����������
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			b[i] = b[i] / temp;
			if (i == k)  continue; // ��������� �� �������� ���� �� ����
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			b[i] = b[i] - b[k];
		}
		k++;
	}
	// �������� �����������
	for (k = n - 1; k >= 0; k--) {
		x[k] = b[k];
		for (int i = 0; i < k; i++)
			b[i] = b[i] - a[i][k] * x[k];
	}
}

//argv[1] - ��� �������� �����, argv[2] - ��� ��������� �����
int main(int argc, char * argv[]) {
	setlocale(LC_ALL, "Russian");// ���������� ����������� ���������

	if (argc != 3) {
		std::cout << "������������ ������" << std::endl;
		return 1;
	}

	FILE * in = fopen(argv[1], "rb");
	if (in == nullptr) {
		std::cout << "���� ��� ������ �� ����� ���� ������" << std::endl;
		return 2;
	}

	int n;
	fread(&n, sizeof(n), 1, in);

	if (n < 1) {
		std::cout << "�� ������������� ������ �������" << std::endl;
		fclose(in);
		return 3;
	}

	Sole * S = new Sole(n);// ������ ����

	// ������ �� ���������
	for (int i = 0; i < n; i++)
		fread(S->A[i], sizeof(**S->A), n, in);
	fread(S->b, sizeof(*S->b), n, in);

	fclose(in);

	gauss(S->A, S->b, S->x, S->N);

	FILE * out = fopen(argv[2], "wb");
	if (out == nullptr) {
		std::cout << "���� ��� ������ �� ����� ���� ������" << std::endl;
		return 4;
	}

	//���������� ���������� � ��������
	fwrite(S->x, sizeof(*S->x), n, out);

	fclose(out);

	return 0;
}
