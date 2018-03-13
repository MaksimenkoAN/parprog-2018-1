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

//vector <double> vec = { 6,4,1,9,3 };


void qSort(vector<double>::iterator begin, vector<double>::iterator end)
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

					//temp = *(begin + i); // a[i];
					//*(begin + i) = *(begin + j); //a[i] = a[j]; 
					//*(begin + j) = temp; //a[j] = temp;

					temp = *(begin + i); // a[i];
					*(begin + i) = *(begin + j); //a[i] = a[j]; 
					*(begin + j) = temp; //a[j] = temp;

					/*int tmp;
					tmp = *ptra;
					ptra = &(*ptrb);
					ptrb = &tmp;*/

					//temp = *(begin + i);
					//begin + i = &(*(begin + j));
					//begin + j = &temp;

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
					stackpos++; // �����������, ������ � ���� ?????????????????????????????????????????????
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

	//for (int i = 0; i < distance(begin, end);i++) {
	//	//vec[i] = *(begin + i);
	//	cout << *(begin + i) << " ";
	//	//cout << vec[i] <<" ";
	//}
}

void qSort(vector <double>* vec) {
	vector<double>::iterator begin = vec->begin();
	vector<double>::iterator end = vec->end();
	qSort(begin, end);
}


void qSort(double* arr, int size)
{
	int first = 0;
	int last = size - 1;
	int elem = arr[size / 2];

	do {
		while (arr[first] < elem)
			first++;
		while (arr[last] > elem)
			last--;

		if (first <= last) {
			int tmp = arr[first];
			arr[first] = arr[last];
			arr[last] = tmp;
			first++;
			last--;
		}
	} while (first <= last);


	if (last > 0)
		qSort(arr, last + 1);
	if (first < size)
		qSort(&arr[first], size - first);
}

void printArray(double* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void main()
{
	//int a = 0;
	//int* ptra = &a;
	//int b = 1;
	//int* ptrb = &b;
	//int* ptrtmp;
	//cout << a << " " << b << endl;
	//cout << ptra << " " << ptrb << endl;

	//int tmp;
	//tmp = *ptra;
	//ptra = &(*ptrb);
	//ptrb = &tmp;

	//cout << a << " " << b << endl;
	//cout << ptra << " " << ptrb << endl;

	//ptrtmp = ptra;
	//ptra = ptrb;
	//ptrb = ptrtmp;
	//cout << a << " " << b << endl;
	//cout << ptra << " " << ptrb << endl;

	////int tmp;
	//tmp = *ptra;
	//*ptra = *ptrb;
	//*ptrb = tmp;
	//cout << a << " " << b << endl;
	//cout << ptra << " " << ptrb << endl;


	cout << "  array" << endl;

	double* arr = new double[5];
	arr[0] = 6;
	arr[1] = 4;
	arr[2] = 1;
	arr[3] = 9;
	arr[4] = 3;
	printArray(arr, 5);
	qSort(arr, 5);
	printArray(arr, 5);
	delete[] arr;

	cout << "  vector" <<endl;

	vector <double> vec = { 6,4,1,9,3 };
	vector <double>* ptr = &vec;
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
	qSort(ptr);
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}

	//delete[]vec;
	system("pause>>void");
}