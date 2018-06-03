#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <chrono>
#include <iostream>
#include <random>
#include "math.h"
#define MAXSTACK 2048
using namespace std;

void qSort_NO_recursion(vector<double>::iterator begin, vector<double>::iterator end)
{
	long i, j; // ���������, ����������� � ����������
	long lb, ub; // ������� ������������ � ����� ���������

	long lbstack[MAXSTACK], ubstack[MAXSTACK]; // ���� ��������
											   // ������ ������ �������� ����� ��������,
											   // � ������: �����(lbstack) � ������(ubstack)
											   // ��������� ����������
	long stackpos = 1; // ������� ������� �����
	long ppos; // �������� �������

	double pivot; // ������� �������
	//vector<double>::iterator temp;
	double temp;

	lbstack[1] = 0;
	ubstack[1] = distance(begin, end)-1;

	do {
		// ����� ������� lb � ub �������� ������� �� �����.
		lb = lbstack[stackpos];
		ub = ubstack[stackpos];
		stackpos--;

		do {
			// ��� 1. ���������� �� �������� pivot
			ppos = (lb + ub) >> 1; //�������� 
			i = lb; 
			j = ub; 
			pivot = *(begin + ppos); // vec[ppos];
			do {
				while (/*a[i]*/ *(begin+i) < pivot) 
					i++;
				while (pivot < /*a[j]*/ *(begin+j)) 
					j--;
				if (i <= j) {
					temp = *(begin + i); // a[i];
					*(begin + i) = *(begin + j); //a[i] = a[j]; 
					*(begin + j) = temp; //a[j] = temp;
					i++; 
					j--;
				}
			} while (i <= j);

			// ������ ��������� i ��������� �� ������ ������� ����������,
			// j - �� ����� ������ (��. ����������� ����), lb ? j ? i ? ub.
			// �������� ������, ����� ��������� i ��� j ������� �� ������� �������

			// ���� 2, 3. ���������� ������� ����� � ���� � ������� lb,ub
			if (i < ppos) { // ������ ����� ������
				if (i < ub) { // ���� � ��� ������ 1 �������� - �����
					stackpos++; // �����������, ������ � ����
					lbstack[stackpos] = i;
					ubstack[stackpos] = ub;
				}
				ub = j; // ��������� �������� ����������
						// ����� �������� � ����� ������
			}
			else { // ����� ����� ������
				if (j > lb) {
					stackpos++;
					lbstack[stackpos] = lb;
					ubstack[stackpos] = j;
				}
				lb = i;
			}
		} while (lb < ub); // ���� � ������� ����� ����� 1 ��������
	} while (stackpos != 0); // ���� ���� ������� � �����
}

//������� ������� ��� ���������� ������
void qSort(vector<double>::iterator begin, vector<double>::iterator end)
{
	int first = 0;
	int length = distance(begin, end);
	int last = distance(begin, end) - 1;
	double elem = *(begin + ((first + last) >> 1));

	do {
		while (*(begin + first) < elem)
			first++;
		while (*(begin + last) > elem)
			last--;

		if (first <= last) {
			double temp = *(begin + first);
			*(begin + first) = *(begin + last);
			*(begin + last) = temp;
			first++;
			last--;
		}
	} while (first <= last);


	if (last > 0)
		qSort(begin, begin + last + 1);
	if (first < distance(begin, end))
		qSort(begin + first, end);
}

//�������
void qSort(vector <double>* vec) {
	vector<double>::iterator begin = vec->begin();
	vector<double>::iterator end = vec->end();
	qSort(begin, end);
}

void qSort_array_recursion(double* arr, int size)
{
	int first = 0;
	int last = size - 1;
	double elem = arr[size / 2];

	do {
		while (arr[first] < elem)
			first++;
		while (arr[last] > elem)
			last--;

		if (first <= last) {
			double tmp = arr[first];
			arr[first] = arr[last];
			arr[last] = tmp;
			first++;
			last--;
		}
	} while (first <= last);


	if (last > 0)
		qSort_array_recursion(arr, last + 1);
	if (first < size)
		qSort_array_recursion(&arr[first], size - first);
}

//������ ������� ��� ���� � �����
void printArray(double* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
