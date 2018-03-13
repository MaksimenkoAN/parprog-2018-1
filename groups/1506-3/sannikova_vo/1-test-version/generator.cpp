#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
using namespace std;
int  n_tests[] = { 1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };
int main(int argc, char * argv[])
{
	// �������������� ����� stdout � ���� arr.in
	freopen("arr.in", "wb", stdout);
	// ������ ��������� ��������� ����� � seed ������ ���������� ������� � ������ �����
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	// ������ ����������� ������������� ��������� �������� ���� double � ��������� 
	//  [-10000, 10000]
	uniform_real_distribution <double> distribution(-1e4, 1e4);
	// ����� ������ ��������
	int n = 1000;
	// ���� �������� ����� ����� � ���������� ��������� ������, �� ���� ������ ��  n_tests
	if (argc > 1)
		n = n_tests[atoi(argv[1])];
	// ���������� � �������� ���� ����������� ������
	fwrite(&n, sizeof(n), 1, stdout);
	// ������ ��������� ������ ��� ������ �������
	double * cur = new double[n];
	// ���������� ������ �������
	for (int i = 0; i < n; i++){
		// ��������� ���������� ������� �� ������������ ������������� ������
		cur[i] = distribution(generator);
	}
	// ���������� ������ � �������� ���� � ����
	fwrite(cur, sizeof(*cur), n, stdout);
	// ���������� ���������� ������ �������
	return 0;
}