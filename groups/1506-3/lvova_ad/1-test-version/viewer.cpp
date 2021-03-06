#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

//���������� �������� ����

int main(int argc, char * argv[]) 
{
	int size;
	double time;
	FILE * input_file = fopen("../massiv.out", "rb"); 

	if (input_file == nullptr) 
	{
		std::cout << "File can not open to read" << std::endl;
		return 1;
	}

	fread(&time, sizeof(time), 1, input_file);
	fread(&size, sizeof(size), 1, input_file);

	if (size < 1)
	{
		std::cout << "Incorrect size of array" << std::endl;
		fclose(input_file);
		return 2;
	}

	double * A = new double[size];
	fread(A, sizeof(*A), size, input_file);
	
	fclose(input_file);

	std::cout << "Work time" << time << std::endl;
	
	for (int i = 0; i < size; i++)
		std::cout << A[i] << " ";

	delete[] A;
	return 0;
}
