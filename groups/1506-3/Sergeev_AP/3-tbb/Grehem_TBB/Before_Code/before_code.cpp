#include "Grehem_Parallel.h"
#include <stdio.h>

//������ ����� ��������� ������ � ������ 1) ���-�� �������, 2) ��� ����� � �������� �������, 3)��� ����� �������� ������
int main(int argc, char * argv[])
{
	int nThreads = atoi(argv[1]);
	FILE * in_data = fopen(argv[2], "rb");
	//��������� ������
	int size;
	fread(&size, sizeof(size), 1, in_data);
	dot* dotArray = new dot[size + 1];
	fread(dotArray, sizeof(*dotArray), size, in_data);
	fclose(in_data);

	//   ������ ������� ������� � ���������� ��������� � ����
	//���������� �������� �������� (tbb ������)
	std::pair<dot*, int> answer = grehemMethod_TBB(dotArray, size + 1, nThreads);
	//������ �������� � ����
	FILE * result_file = fopen(argv[3], "wb");
	fwrite(&answer.second, sizeof(int), 1, result_file);
	fwrite(answer.first, sizeof(*answer.first), answer.second, result_file);
	fclose(result_file);

	return 0;
}