#include <iostream>
#include <vector>
using namespace std;

//W - вес вещей
//V - ценность вещей
//M - вместимость рюказака
//n - количество вещей
void BackPackTask(int W[], int V[], int M, int n)
{
    // Создаем двумерный массив для хранения максимальных ценностей
    int** B = new int* [n + 1];
    for (int i = 0; i <= n; ++i) {
        B[i] = new int[M + 1];
    }

    // Инициализируем все элементы 0-ми
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= M; j++)
            B[i][j] = 0;

    // Формируем матрицу ценности
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= M; j++) {
            B[i][j] = B[i - 1][j];
            if ((j >= W[i - 1]) && (B[i][j] < B[i - 1][j - W[i - 1]] + V[i - 1])) {
                B[i][j] = B[i - 1][j - W[i - 1]] + V[i - 1];
            }
            cout << B[i][j] << " ";  
        }
        cout << endl;
    }

    // Формируем ответ на задачу
    cout << "Максимальная ценность рюкзака:\t" << B[n][M] << endl;

    cout << "Выбранные вещи: " << endl;

    //Выбранные предметы
    int remainingCapacity = M;
    for (int currentItem = n; currentItem > 0; currentItem--) {
        if (B[currentItem][remainingCapacity] != B[currentItem - 1][remainingCapacity]) {
            cout << "\tПредмет " << currentItem
                << " с W = " << W[currentItem - 1]
                << " и V = " << V[currentItem - 1] << endl;
            remainingCapacity -= W[currentItem - 1];
        }
    }

    // Чистим память
    for (int i = 0; i <= n; ++i) {
        delete[] B[i];
    }
    delete[] B;
}

int main()
{
    setlocale(LC_ALL, "ru");
    cout << "Введите максимальную вместимость рюкзака: ";
    int M; cin >> M;

    cout << "Введите количество вещей для заполнения: ";
    int n; cin >> n;

    int* W = new int[n];
    int* V = new int[n];

    for (int i = 0; i < n; i++) {
        cout << "Введите вес и ценность " << i + 1 << " предмета: ";
        cin >> W[i] >> V[i];
    }

    BackPackTask(W, V, M, n);

    delete[] W;
    delete[] V;

    return 0;
}