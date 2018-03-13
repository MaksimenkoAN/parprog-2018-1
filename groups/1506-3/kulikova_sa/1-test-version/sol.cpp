#include <omp.h>
#include "Sole.h"

int size = 0;

double vec(double * x, double * y) {
	double res = 0;
	for (int i = 0; i < size; i++)
		res += x[i] * y[i];
	return res;
}

void NonlinearConjugateGradient(Sole * S) {
	size = S->N;//������� �������

	//��������� ������
	double * x = new double[size];//������ �����������
	double * d = new double[size];//������ �����������
	double * g = new double[size];//��������
	double s;//��������� ���, �������� �������� �� ��������� �����������
	double coef;//����������� �� 2 ����
	double * s_prev = new double[size];//������������ ������� ����������� � �������
	double * x_prev = new double[size];//���������� �����������
	double * d_prev = new double[size];//���������� ������ �����������
	double * g_prev = new double[size];//���������� ��������
 
	//����� ����������� ������ �������� x0 � d0 ���������� ������� ����, � ��� ������� g0 ��������������� �������� -b
	for (int i = 0; i < size; i++) {
		x_prev[i] = 0;
		d_prev[i] = 0;
		g_prev[i] = S->b[i] * (-1);
	}

	//���� �� ���������� ��������
	for (int i = 0; i < size; i++) {
		//1. ���������� ���������
		for (int j = 0; j < size; j++)
			g[j] = vec(S->A[j], x_prev) - S->b[j];

		//2. ���������� ������� �����������
		coef = vec(g, g) / vec(g_prev, g_prev);
		for (int j = 0; j < size; j++)
			d[j] = coef * d_prev[j] - g[j];

		//3. ���������� �������� �������� �� ��������� �����������
		for (int j = 0; j < size; j++)
			s_prev[j] = vec(S->A[j], d);
		s = vec(d, g) / vec(s_prev, d);

		//4. ���������� ������ �����������
		for (int j = 0; j < size; j++)
			x[j] = x_prev[j] - s * d[j];

		//������ ������� �� ����������
		for (int j = 0; j < size; j++) {
			g_prev[j] = g[j];
			d_prev[j] = d[j];
			x_prev[j] = x[j];
		}
	}

	//���������� ����������
	for (int i = 0; i < size; i++)
		S->x[i] = x[i];

	//������������ ������
	delete[] x;
	delete[] d;
	delete[] g;
	delete[] s_prev;
	delete[] x_prev;
	delete[] d_prev;
	delete[] g_prev;
}
