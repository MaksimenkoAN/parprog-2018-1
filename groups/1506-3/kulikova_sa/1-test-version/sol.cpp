#include <omp.h>
#include "Sole.h"

double vec(double * x, double * y, int size) {
	double res = 0;
	for (int i = 0; i < size; i++) {
		res += x[i] * y[i];
	}
	return res;
}

void NonlinearConjugateGradient(Sole * S) {
	//����������� ������� ������ ���� �������������, �.� N > 0

	//������� � ������ ���� �����������, �.� �=��

	//������� � ������ ���� ������������ ����������, �.� x�*�*x > 0

	double * x = new double[S->N];//������ �����������
	double * d = new double[S->N];//������ �����������
	double * g = new double[S->N];//��������
	double s;//��������� ���, �������� �������� �� ��������� �����������
	double * s_prev = new double[S->N];//������������ ������� ����������� � �������
	double * x_prev = new double[S->N];//���������� �����������
	double * d_prev = new double[S->N];//���������� ������ �����������
	double * g_prev = new double[S->N];//���������� ��������
 
	//����� ����������� ������ �������� x0 � d0 ���������� ������� ����, � ��� ������� g0 ��������������� �������� -b
	for (int i = 0; i < S->N; i++) {
		x_prev[i] = 0;
		d_prev[i] = 0;
		g_prev[i] = S->b[i] * (-1);
	}

	//���� �� ���������� ��������
	for (int i = 0; i < S->N; i++) {
		//1. ���������� ���������
		for (int j = 0; j < S->N; j++)
			g[j] = vec(S->A[j], x_prev, S->N) - S->b[j];

		//2. ���������� ������� �����������
		for (int j = 0; j < S->N; j++)
			d[j] = vec(g, g, S->N) / vec(g_prev, g_prev, S->N) * d_prev[j] - g[j];

		//3. ���������� �������� �������� �� ��������� �����������
		for (int j = 0; j < S->N; j++)
			s_prev[j] = vec(S->A[j], d, S->N);
		s = vec(d, g, S->N) / vec(s_prev, d, S->N);

		//4. ���������� ������ �����������
		for (int j = 0; j < S->N; j++)
			x[j] = x_prev[j] - s * d[j];

		//������ ������� �� ����������
		for (int j = 0; j < S->N; j++) {
			g_prev[j] = g[j];
			d_prev[j] = d[j];
			x_prev[j] = x[j];
		}
	}

	//���������� ����������
	for (int i = 0; i < S->N; i++)
		S->x[i] = x[i];
}
