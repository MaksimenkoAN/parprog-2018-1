#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <random> 
#include <chrono>

int n_tests[] = { 1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };

//argv[1] - ������ �������, argv[2] - ��� ��������� �����
int main(int argc, char * argv[]) {
	setlocale(LC_ALL, "Russian");//���������� ����������� ���������

	if (argc != 3) {
		std::cout << "������������ ������" << std::endl;
		return 1;
	}

	if (atoi(argv[1]) < 0 || atoi(argv[1]) > 24) {
		std::cout << "������������ ����� �����" << std::endl;
		return 2;
	}

	FILE * out = fopen(argv[2], "wb");

	if (out == nullptr) {
		std::cout << "���� ��� ������ �� ����� ���� ������" << std::endl;
		return 3;
	}
 
	int n = n_tests[atoi(argv[1])];// ����� ������ ������
	double ** cur = new double*[n];
	for (int i = 0; i < n; i++)
		cur[i] = new double[n];
	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution <double> distribution(-100, 100);

	std::cout << "����� ������� �������������? ������� ����� �� 1 �� 7 ������������." << std::endl;
	std::cout << 
		"1. ������������ ������������ ������������" << std::endl <<
		"2. ������������"							<< std::endl <<
		"3. ���������"								<< std::endl <<
		"4. �������"								<< std::endl <<
		"5. ������������"							<< std::endl <<
		"6. �������������"							<< std::endl <<
		"7. ���������"								<< std::endl;

	int c;//�������� ����
	std::cin >> c;

	switch (c) {//���������� �������
	case 1: {//������������ ������������ ������������
		for (int i = 0; i < n; i++)
			for (int j = i; j < n; j++) {
				cur[i][j] = cur[j][i] = distribution(generator);
				if (i == j)
					cur[i][j] += 400;
			}
		break;
	}
	case 2: {//������������
		for (int i = 0; i < n; i++)
			for (int j = i; j < n; j++)
				cur[i][j] = cur[j][i] = distribution(generator);
		break;
	}
	case 3: {//���������
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				cur[i][j] = 0;
				if (i == j)
					cur[i][j] = 1;
			}
		break;
	}
	case 4: {//�������
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cur[i][j] = 0;
		break;
	}
	case 5: {//������������
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				cur[i][j] = 0;
				if (i == j)
					cur[i][j] = distribution(generator);
			}
		break;
	}
	case 6: {//�������������
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cur[i][j] = (int)distribution(generator);
		break;
	}
	case 7: {//���������
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cur[i][j] = distribution(generator);
		break;
	}
	default: {
		std::cout << "�������� ����� ����" << std::endl;
		fclose(out);
		for (int i = 0; i < n; i++)
			delete[] cur[i];
		delete[] cur;

		return 4;
	}
	}

	//������ � �������� ����
	fwrite(&n, sizeof(n), 1, out);
	for (int i = 0; i < n; i++)
		fwrite(cur[i], sizeof(**cur), n, out);

	for (int i = 0; i < n; i++)	//���������� ������ 
		cur[0][i] = distribution(generator);

	fwrite(cur[0], sizeof(**cur), n, out);

	//������������ ������
	fclose(out);
	for (int i = 0; i < n; i++)
		delete[] cur[i];
	delete[] cur;

	return 0;
}
