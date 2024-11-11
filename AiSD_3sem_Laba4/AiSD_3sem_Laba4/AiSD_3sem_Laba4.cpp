#include <iostream>
#include <vector>

using namespace std;

const int INF = INT32_MAX;

//Структура для представления ребра
struct Edge {
    int dest;   // В какую вершину
    int weight; // Вес
};

//Функция для добавления ребра в граф
void addEdge(vector<vector<Edge>>& graph, int src, int dest, int w1, int w2)
{
    graph[src - 1].push_back({ dest - 1, w1 });
    graph[dest - 1].push_back({ src - 1, w2 });
}

// Функция вывода матриц 6x6
void PrintMatrix(int matrix[6][6])
{
    for (int i = 0; i < 6; i++)
    {
        cout << i + 1 << " | ";
        for (int j = 0; j < 6; j++)
        {
            if (matrix[i][j] == INF)
                cout << "INF ";  
            else
                cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void FloydWarshall(int D[6][6], int S[6][6])
{
    for (int k = 0; k < 6; k++)
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                if (D[i][k] < INF && D[k][j] < INF)
                {
                    if (D[i][j] > D[i][k] + D[k][j])
                    {
                        D[i][j] = D[i][k] + D[k][j];
                        S[i][j] = k + 1; 
                    }
                }
            }
        }
    }
}

// Функция для восстановления пути без рекурсии
void GetPathIterative(int S[6][6], int start, int end, vector<int>& path)
{
    if (S[start][end] == 0 || start == end)
        return;

    int current = start;
    while (current != end)
    {
        path.push_back(S[current][end]); // Добавляем промежуточную вершину
        current = S[current][end] - 1;
    }
}


// Вывод пути и суммы весов
void PrintPath(int C[6][6], int S[6][6], int start, int end)
{
    if (C[start][end] == INF)
    {
        cout << "Нет пути между вершинами " << start + 1 << " и " << end + 1 << endl;
        return;
    }

    vector<int> path = { start + 1 }; // Начинаем с начальной вершины
    GetPathIterative(S, start, end, path);

    cout << "Путь: ";
    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i];
        if (i != path.size() - 1)
            cout << " - ";
    }
    cout << endl;

    cout << "Сумма весов: " << C[start][end] << endl;
}


int BigO(int V)
{
    return V * V * V;
}
int main()
{
    setlocale(LC_ALL, "ru");
    
    int numVertices = 6;
    vector<vector<Edge>> graph(numVertices);
        
    addEdge(graph, 1, 2, 28, 7);
    addEdge(graph, 1, 3, 21, 9);
    addEdge(graph, 1, 4, 59, 8);
    addEdge(graph, 1, 5, 12, 14);
    addEdge(graph, 1, 6, 27, 15);
    addEdge(graph, 2, 3, 24, 32);
    addEdge(graph, 2, 5, 21, 13);
    addEdge(graph, 2, 6, 9, 18);
    addEdge(graph, 3, 4, 13, 5);
    addEdge(graph, 3, 5, 11, 15);
    addEdge(graph, 4, 5, 16, 10);
    addEdge(graph, 5, 6, 22, 6);

    //Матрица кратчайших путей между вершинами без промежуточных вершин
    int C[6][6] = 
    { 
        {0, 28, 21, 59, 12, 27},
        {7, 0, 24, INF, 21, 9},
        {9, 32, 0, 13, 11, INF},
        {8, INF, 5, 0, 16, INF},
        {14, 13, 15, 10, 0, 22},
        {15, 18, INF, INF, 6, 0}
    };

    cout << "Матрица кратчайших путей между вершинами без промежуточных вершин" << endl;
    cout << "   1  2  3  4  5  6" << endl << "   -----------------" << endl;
    PrintMatrix(C);

    //Матрица последовательности вершин
    int S[6][6] =
    {
        {0, 2, 3, 4, 5, 6},
        {1, 0, 3, 4, 5, 6},
        {1, 2, 0, 4, 5, 6},
        {1, 2, 3, 0, 5, 6},
        {1, 2, 3, 4, 0, 6},
        {1, 2, 3, 4, 5, 0},
    };

    cout << "Матрица последовательности вершин" << endl;
    cout << "    1 2 3 4 5 6" << endl << "   ------------" << endl;
    PrintMatrix(S);

    FloydWarshall(C, S);

    cout << "Матрица кратчайших путей после применения алгоритма Флойда-Уоршелла (C):" << endl;
    cout << "   1  2  3  4  5  6" << endl << "   -----------------" << endl;
    PrintMatrix(C);

    cout << "Матрица последовательности вершин после применения алгоритма Флойда-Уоршелла (S):" << endl;
    cout << "    1 2 3 4 5 6" << endl << "   ------------" << endl;
    PrintMatrix(S);
   
    cout << "Сложность Алгоритма: " << BigO(6) << endl;

  // Ввод вершин от пользователя
    int start, end;
    cout << "Введите начальную вершину (1-6): ";
    cin >> start;
    cout << "Введите конечную вершину (1-6): ";
    cin >> end;

    // Проверка корректности ввода
    if (start < 1 || start > 6 || end < 1 || end > 6)
    {
        cout << "Неверный ввод. Пожалуйста, введите вершины от 1 до 6." << endl;
        return 1; // Завершаем программу с ошибкой
    }

    // Вывод пути и суммы весов
    PrintPath(C, S, start - 1, end - 1);

    return 0;

}
