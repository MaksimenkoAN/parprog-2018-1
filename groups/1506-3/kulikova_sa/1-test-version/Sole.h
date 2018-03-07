#pragma once
#include <iostream>

//����
class Sole {
public:
	double ** A;
	double * b;
	double * x;
	int N;

	Sole(int n) {
		N = n;
		A = new double*[N];
		for (int i = 0; i < N; i++)
			A[i] = new double[N];
		b = new double[N];
		x = new double[N];
	}

	~Sole() {
		for (int i = 0; i < N; i++)
			delete[] A[i];
		delete[] A;
		delete[] b;
		delete[] x;
	}

	void Print() {
		std::cout << "������� �������" << std::endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				std::cout << A[i][j] << " ";
			std::cout << std::endl;
		}
		std::cout << "������� ��������� ������" << std::endl;
		for (int i = 0; i < N; i++)
			std::cout << b[i] << " ";
		std::cout << std::endl << "������� �������" << std::endl;
		for (int i = 0; i < N; i++)
			std::cout << x[i] << " ";
		std::cout << std::endl;
	}
};

