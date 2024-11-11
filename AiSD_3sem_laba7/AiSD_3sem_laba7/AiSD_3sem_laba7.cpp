#include <iostream>
#include <vector>
#include <algorithm> //Для reverse

using namespace std;

vector<int> findLIS(vector<int> start_vector)
{
    int n = (int)start_vector.size(); //Длина изначальной последовательности
    int *prev = new int[n-1]; //prev — массив, который сохраняет индексы предыдущих элементов для восстановления самой длинной возрастающей подпоследовательности.
    int* d = new int[n - 1]; //d[i] - длина наибольшей возрастающей подпоследовательности

    //1-ая подзадача - получение длины подпоследовательности и массива индексов максимальной подпоследовательности
    for (int i = 0; i < n; i++)
    {
        d[i] = 1; //Минимальная длина подпоследовательности
        prev[i] = -1; // -1 означает, что предыдущего значения нет

        for (int j = 0; j < i; j++)
        {
            //Проверка, на максимальную длину подпоследовательности
            if (start_vector[j] < start_vector[i] && d[j] + 1 > d[i])
            {
                d[i] = d[j] + 1;
                prev[i] = j;
            }
                
        }
    }

    int pos = 0;//Индекс последнего элемента новой подпоследовательности
    int length = d[0]; //Длина новой подпоследовательности
    
    //2-ая подзадача - поиск конца максимальной подпоследовательности
    for(int i = 0; i < n; i++)
    {
        if (d[i] > pos)
        {
            pos = i; // Находим позицию максимального элемента максимальной подпоследовательности
            length = d[i]; // Длина новой максмальной подпоследовательности
        }
    }

    //Переносим все в вектор
    vector<int> answer; 

    //3-ая подзадача - восстановление максимальной подпоследовательности
    while (pos != -1)
    {
        answer.push_back(start_vector[pos]);
        pos = prev[pos];
    }
    reverse(answer.begin(), answer.end()); //Реверсим, так как она заполняется с конца, а не с начала

    return answer;

}

int main()
{
    setlocale(LC_ALL, "ru");
    vector<int> start_vector = { 5, 10, 6, 12, 3, 24, 7, 8 };

    vector<int> end_vector = findLIS(start_vector);

    cout << "Максимальная подпоследовательность: " << endl;

    for (int i = 0; i < end_vector.size(); i++)
    {
        cout << end_vector[i] << " ";
    }

    cout << endl << "Длина данной подпоследовательности: " << end_vector.size() << endl;

    return 0;
}


