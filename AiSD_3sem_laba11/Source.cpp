#include <iostream>
#include <vector>
#include <random>

using namespace std;

bool findNumber(int prisoner, vector<int>& boxes, bool randomChoice)
{
    int attempts = 0;
    int currentBox = randomChoice ? rand() % 100 : prisoner - 1;

    while (attempts < 50) 
    {
        if (boxes[currentBox] == prisoner)
            return true;

        currentBox = randomChoice ? rand() % 100 : boxes[currentBox] - 1;
        ++attempts;
    }

    return false;
}

bool simulate(bool randomChoice) {
    vector<int> boxes(100);
    for (int i = 0; i < 100; ++i) 
        boxes[i] = i + 1;

    shuffle(boxes.begin(), boxes.end(), mt19937(random_device()()));

    for (int prisoner = 1; prisoner <= 100; ++prisoner) 
        if (!findNumber(prisoner, boxes, randomChoice)) 
            return false; 

    return true; 
}

int main() 
{
    setlocale(LC_ALL, "ru");

    cout << "Введите количество раундов для сравнения: ";
    long long rounds;
    cin >> rounds;

    int randomSuccessCount = 0;
    int optimalSuccessCount = 0;

    for (long long i = 0; i < rounds; ++i) {
        if (simulate(true)) randomSuccessCount++;
        if (simulate(false)) optimalSuccessCount++;
    }

    cout << "Результаты после " << rounds << " раундов:" << endl;
    cout << "Случайный выбор: " << randomSuccessCount << " успешных исходов." << endl;
    cout << "Оптимальный выбор: " << optimalSuccessCount << " успешных исходов.";

    return 0;
}