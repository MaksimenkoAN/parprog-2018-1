#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <random> 
#include <ctime> 
#include <chrono>
#include <iostream>

using namespace std;

int n_tests[] = { 1, 2, 3, 4, 5, 7, 8, 9, 10, 10, 100, 200, 300, 500, 750, 1000, 100000, 500000, 1000000, 5000000 };

int main(int argc, char * argv[])
{
	if (argc != 2 || atoi(argv[1]) < 1 || atoi(argv[1]) > 20)
	{
		cout << "Use 'generator [test number (1 - 20)]'" << endl;
		return 1;
	}
	int N = n_tests[atoi(argv[1])-1];

	freopen(argv[1], "wb", stdout);
	default_random_engine generator(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
	uniform_int_distribution <int> distribution(0, 1000);
	
	fwrite(&N, sizeof(unsigned int), 1, stdout);
	fwrite(&N, sizeof(N), 1, stdout);

	int *arr = new int[N];
	if (atoi(argv[1]) == 10) { // ���������� ����� � �������
		int val = distribution(generator);
		for (int i = 0; i < N; i++)	arr[i] = val;
	}
	else // ��������� ����� � �������
		for (int i = 0; i < N; i++) arr[i] = distribution(generator);
	
	fwrite(arr, sizeof(*arr), N, stdout);
	return 0;
}