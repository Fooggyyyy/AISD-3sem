#include <iostream>
#include <time.h>

using namespace std;

//n - количество блинов
//i - начальная позиция пирамиды
//k - позиция, на которую надо переставить пирамиду
int kolvo = 0;

int HanoyTower(int n, int i, int k)
{
	
	if (n == 1)//Крайний случай
	{
		cout << "Переместить диск 1 с " << i << " на " << k << " стержень" << endl;//Перемещаем самый нижний блин с начальной на нужную нам позицию
		kolvo++;
	}
	else
	{
		kolvo++;
		int temp = 6 - i - k;//Позиция вспомогательного штыря
		HanoyTower(n - 1, i, temp);//Рекурсивный вызов функции, где все блины (кроме последнего) перелиживаются с начальной, на вспомогатльную позицию

		cout << "Переместить диск " << n <<" с " << i << " на " << k << " стержень" << endl;

		HanoyTower(n - 1, temp, k);//Второй рекурсивный вызов функции, где все блины (кроме последнего) перелаживаются с вспомогательной, на нужную позицию.
	}
	return kolvo;
}

int main()
{
	setlocale(LC_ALL, "ru");
	double startTime, endTime;

	cout << "Введите сколько будет пластин в пирамиде: ";
	int N; cin >> N;
	if (N < 1)
	{
		cout << "Неверное кол во пластин.";
		return 0;
	}
	cout << "Введите c какого колышек ставить пирамиду: ";
	int i; cin >> i;
	if (i != 2 && i != 3 && i != 1)
	{
		cout << "Позиция не возможна.";
		return 0;
	}
	cout << "Введите на какой колышек ставить пирамиду: ";
	int k; cin >> k;
	if (k != 2 && k != 3 && k != 1)
	{
		cout << "Позиция не возможна.";
		return 0;
	}

	if (k == i)
	{
		cout << "Башня уже собрана ";
		return 0;
	}
	
	startTime = clock();
	int kolvo = HanoyTower(N, i, k);
	endTime = clock();

	cout << "Кол-во итераций: " << kolvo << endl;
	cout << "Время рабоы алгоритма: " << endTime - startTime << " мс";

	return 0;
}