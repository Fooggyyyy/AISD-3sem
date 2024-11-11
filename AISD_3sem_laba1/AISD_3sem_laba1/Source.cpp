#include <iostream>
#include <time.h>

using namespace std;

//n - ���������� ������
//i - ��������� ������� ��������
//k - �������, �� ������� ���� ����������� ��������
int kolvo = 0;

int HanoyTower(int n, int i, int k)
{
	
	if (n == 1)//������� ������
	{
		cout << "����������� ���� 1 � " << i << " �� " << k << " ��������" << endl;//���������� ����� ������ ���� � ��������� �� ������ ��� �������
		kolvo++;
	}
	else
	{
		kolvo++;
		int temp = 6 - i - k;//������� ���������������� �����
		HanoyTower(n - 1, i, temp);//����������� ����� �������, ��� ��� ����� (����� ����������) �������������� � ���������, �� �������������� �������

		cout << "����������� ���� " << n <<" � " << i << " �� " << k << " ��������" << endl;

		HanoyTower(n - 1, temp, k);//������ ����������� ����� �������, ��� ��� ����� (����� ����������) �������������� � ���������������, �� ������ �������.
	}
	return kolvo;
}

int main()
{
	setlocale(LC_ALL, "ru");
	double startTime, endTime;

	cout << "������� ������� ����� ������� � ��������: ";
	int N; cin >> N;
	if (N < 1)
	{
		cout << "�������� ��� �� �������.";
		return 0;
	}
	cout << "������� c ������ ������� ������� ��������: ";
	int i; cin >> i;
	if (i != 2 && i != 3 && i != 1)
	{
		cout << "������� �� ��������.";
		return 0;
	}
	cout << "������� �� ����� ������� ������� ��������: ";
	int k; cin >> k;
	if (k != 2 && k != 3 && k != 1)
	{
		cout << "������� �� ��������.";
		return 0;
	}

	if (k == i)
	{
		cout << "����� ��� ������� ";
		return 0;
	}
	
	startTime = clock();
	int kolvo = HanoyTower(N, i, k);
	endTime = clock();

	cout << "���-�� ��������: " << kolvo << endl;
	cout << "����� ����� ���������: " << endTime - startTime << " ��";

	return 0;
}