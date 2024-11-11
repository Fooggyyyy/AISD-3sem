#include <iostream>
#include <vector>
#include <queue> // Для BFS
#include <stack> // Для DFS

using namespace std;

// Представление графа через список рёбер
vector<pair<int, int>> edges = { {1, 2}, {1, 5}, {2, 7}, {2, 8}, {7, 8}, {4, 6}, {5, 6}, {6, 9}, {9, 10}, {3, 8}, {4, 9} };

// Преобразование списка рёбер в список смежности
vector<vector<int>> AdjList(const vector<pair<int, int>>& edges, int numVertices) 
{
    vector<vector<int>> adjacencyList(numVertices + 1); // +1, чтобы индексы совпадали с вершинами

    for (const auto& edge : edges) 
    {
        int u = edge.first;
        int v = edge.second;
        adjacencyList[u].push_back(v); // Для u добавляем в список элемент v
        adjacencyList[v].push_back(u); // Если граф неориентированный
    }

    return adjacencyList;
}

// Преобразование списка рёбер в матрицу смежности
vector<vector<int>> AdjMatrix(const vector<pair<int, int>>& edges, int numVertices) {
    vector<vector<int>> adjacencyMatrix(numVertices + 1, vector<int>(numVertices + 1, 0));

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        adjacencyMatrix[u][v] = 1;
        adjacencyMatrix[v][u] = 1;
    }

    return adjacencyMatrix;
}

//-------------------------------------------------------------------------------------------------------

// Поиск в ширину BFS
void BFS(const vector<vector<int>>& GRAPH, int start) {
    vector<bool> Visited(GRAPH.size(), false); // Пройденные вершины
    queue<int> q; // Очередь для хранения вершин при обходе

    Visited[start] = true; // Помечаем начальную позицию как посещенную
    q.push(start); // Заносим ее в очередь

    while (!q.empty()) { // BFS продолжается до тех пор, пока очередь не пуста  
        int Handling = q.front(); // Извлекаем верхнюю вершину очереди для обработки
        q.pop(); // Удаляем верхнюю вершину из очереди

        cout << Handling << " "; // Обрабатываем вершину (например, выводим)

        for (int neighbor : GRAPH[Handling]) { // Просматриваем соседей вершины, извлеченной из очереди
            if (!Visited[neighbor]) { // Если вершина не посещена
                Visited[neighbor] = true; // Помечаем ее как посещенную
                q.push(neighbor); // Записываем вершину в очередь
            }
        }
    }
    cout << endl; 
}

// Поиск в глубину DFS
void DFS(const vector<vector<int>>& adjList, int start) {
    vector<bool> visited(adjList.size(), false); // Пройденные вершины
    stack<int> s; // Стек для хранения вершин при обходе

    s.push(start); // Добавляем начальную вершину в стек
    visited[start] = true; // Помечаем начальную вершину как посещённую

    while (!s.empty()) { // DFS продолжается до тех пор, пока стек не пуст
        int Handling = s.top(); // Берём вершину с вершины стека
        s.pop(); // Удаляем её из стека
        cout << Handling << " "; // Обрабатываем вершину (например, выводим)

        // Проходим по всем соседям вершины
        for (int neighbor : adjList[Handling]) {
            if (!visited[neighbor]) { // Если сосед ещё не был посещён
                s.push(neighbor); // Добавляем его в стек
                visited[neighbor] = true; // Помечаем его как посещённого
            }
        }
    }
    cout << endl; 
}

//-------------------------------------------------------------------------------------------------------

// Функция для вывода списка рёбер
void printEdges(const vector<pair<int, int>>& edges) {
    cout << "Список рёбер:" << endl;
    for (const auto& edge : edges) {
        cout << edge.first << " - " << edge.second << endl;
    }
    cout << endl;
}

// Функция для вывода матрицы смежности
void printAdjMatrix(const vector<vector<int>>& adjacencyMatrix) {
    cout << "Матрица смежности:" << endl;
    for (int i = 1; i < adjacencyMatrix.size(); ++i) {
        for (int j = 1; j < adjacencyMatrix[i].size(); ++j) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Функция для вывода списка смежности
void printAdjList(const vector<vector<int>>& adjacencyList) {
    cout << "Список смежности:" << endl;
    for (int i = 1; i < adjacencyList.size(); ++i) {
        cout << i << ": ";
        for (int neighbor : adjacencyList[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//-------------------------------------------------------------------------------------------------------

//O(V+E), V — количество вершин, а E — количество рёбер.
int BigO_AdjList(int V)
{
    return V + (V + 1);
}

//O(V*V), V — количество вершин
int BigO_AdjMatrix(int V)
{
    return V * V;
}

//-------------------------------------------------------------------------------------------------------

int main() {
    setlocale(LC_ALL, "ru");

    int V = 10; // Максимальное количество вершин

    vector<vector<int>> adjacencyList = AdjList(edges, V);
    vector<vector<int>> adjacencyMatrix = AdjMatrix(edges, V);

    printEdges(edges);
    printAdjList(adjacencyList);
    printAdjMatrix(adjacencyMatrix);

    cout << "Результат BFS, начиная с вершины 1:" << endl;
    BFS(adjacencyList, 1);

    cout << "Результат DFS, начиная с вершины 1:" << endl;
    DFS(adjacencyList, 1);

    cout << "Big-O DFS и BFS для списка смежности: O(" << BigO_AdjList(V) << ")\n";
    cout << "Big-O DFS и BFS для матрицы смежности: O(" << BigO_AdjMatrix(V) << ")\n";
    return 0;
}
