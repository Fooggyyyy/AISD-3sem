#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <climits> 

using namespace std;

// Структура для представления ребра
struct Edge1
{
    int dest; // В какую вершину
    int weight; // Вес
};

struct Edge
{
    int src; // Из какой вершины
    int dest; // В какую вершину
    int weight; // Вес
};

// Функция для добавления ребра в граф
void addEdge(vector<vector<Edge1>>& graph, int src, int dest, int weight) {
    graph[src].push_back({ dest, weight });
    graph[dest].push_back({ src, weight }); // Для неориентированного графа
}


// Функция для нахождения корня множества с применением сжатия путей
int findSet(int v, vector<int>& parent) {
    if (v == parent[v])
        return v;
    return parent[v] = findSet(parent[v], parent); // Сжатие пути
}

// Функция для объединения двух множеств 
void unionSets(int a, int b, vector<int>& parent) {
    a = findSet(a, parent);
    b = findSet(b, parent);
    if (a != b) {
        parent[b] = a; // Просто присваиваем b корень a
    }
}


// Алгоритм Краскала 
pair<int, vector<pair<int, int>>> kruskalMST(int V, vector<Edge>& edges) {
    // Сортируем ребра по возрастанию веса
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
        });

    vector<int> parent(V); // Массив для хранения родительских вершин

    // Инициализируем каждую вершину как свой собственный родитель
    for (int i = 0; i < V; ++i)
        parent[i] = i;

    vector<pair<int, int>> mstEdges; // Список для хранения ребер минимального остовного дерева
    int mstWeight = 0; // Общий вес остовного дерева

    // Обрабатываем каждое ребро в порядке возрастания веса
    for (auto& edge : edges) {
        int u = edge.src;
        int v = edge.dest;
        int weight = edge.weight;

        // Проверяем, принадлежат ли u и v разным компонентам
        if (findSet(u, parent) != findSet(v, parent)) {
            // Если принадлежат, то добавляем ребро в остовное дерево
            mstWeight += weight;
            mstEdges.push_back({ u, v });
            unionSets(u, v, parent); // Объединяем множества
        }
    }

    return { mstWeight, mstEdges }; // Возвращаем вес и список ребер остовного дерева
}


// Преобразование списка смежности в матрицу смежности
vector<vector<int>> adjListToMatrix(const vector<vector<Edge1>>& graph, int V) {
    vector<vector<int>> matrix(V, vector<int>(V, INT_MAX));

    for (int u = 0; u < V; ++u) {
        for (auto& edge : graph[u]) {
            int v = edge.dest;
            matrix[u][v] = edge.weight;
            matrix[v][u] = edge.weight; // Для неориентированного графа
        }
        matrix[u][u] = 0; // Вес петли 0
    }

    return matrix;
}

// Алгоритм Прима с матрицей смежности
pair<int, vector<pair<int, int>>> primMSTMatrix(const vector<vector<int>>& matrix, int V) {
    // Создаем вектор ключей (минимальные веса ребер) и инициализируем их максимальным значением (INT_MAX)
    vector<int> key(V, INT_MAX);

    // Создаем вектор, который отслеживает, какие вершины включены в MST (начально все false)
    vector<bool> inMST(V, false);

    // Вектор для хранения родителя каждой вершины в MST
    vector<int> parent(V, -1);

    // Устанавливаем ключ для первой вершины в 0, чтобы начать с нее
    key[0] = 0;

    // Переменная для хранения суммарного веса минимального остовного дерева
    int mstWeight = 0;

    // Повторяем, пока все вершины не будут добавлены в MST
    for (int count = 0; count < V; ++count) {
        int u = -1;

        // Находим вершину, которая еще не в MST и имеет минимальный ключ
        for (int i = 0; i < V; ++i) {
            if (!inMST[i] && (u == -1 || key[i] < key[u])) {
                u = i;  // Обновляем индекс вершины с минимальным ключом
            }
        }

        // Включаем найденную вершину в MST
        inMST[u] = true;

        // Добавляем вес ключа этой вершины к общему весу MST
        mstWeight += key[u];

        // Обновляем ключи для соседних вершин, если найдено более короткое ребро
        for (int v = 0; v < V; ++v) {
            // Проверяем, что вершина v еще не в MST и есть ребро между u и v (не бесконечное значение)
            if (!inMST[v] && matrix[u][v] != INT_MAX && matrix[u][v] < key[v]) {
                // Обновляем ключ для вершины v
                key[v] = matrix[u][v];
                // Устанавливаем вершину u как родителя для вершины v
                parent[v] = u;
            }
        }
    }

    // Создаем вектор для хранения ребер MST
    vector<pair<int, int>> mstEdges;

    // Строим список ребер MST по родительскому массиву
    for (int i = 1; i < V; ++i) {
        if (parent[i] != -1) {
            mstEdges.push_back({ parent[i], i }); // Добавляем ребро (родитель, вершина)
        }
    }

    // Возвращаем общий вес MST и список ребер
    return { mstWeight, mstEdges };
}


// Прима: Матрица O(V^2), Список смежности O(E*logV);
// Краскала: O(E*logV)
int main() {
    setlocale(LC_ALL, "ru");
    int V = 8; // Количество вершин в графе
    vector<vector<Edge1>> graph(V);

    // Добавляем ребра
    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 3, 8);
    addEdge(graph, 0, 4, 2);
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 1, 3, 10);
    addEdge(graph, 1, 4, 5);
    addEdge(graph, 2, 4, 12);
    addEdge(graph, 2, 7, 7);
    addEdge(graph, 3, 4, 14);
    addEdge(graph, 3, 5, 3);
    addEdge(graph, 3, 6, 1);
    addEdge(graph, 4, 5, 11);
    addEdge(graph, 4, 6, 4);
    addEdge(graph, 4, 7, 8);
    addEdge(graph, 5, 6, 6);
    addEdge(graph, 6, 7, 9);


    cout << "Цикламатическое число: " << 16 - 8 + 1 << endl;

    cout << "Алгоритм Прима (Матрица):" << endl;
    vector<vector<int>> matrix = adjListToMatrix(graph, V);
    pair<int, vector<pair<int, int>>> resultMatrix = primMSTMatrix(matrix, V);
    cout << "Вес минимального остовного дерева (MST): " << resultMatrix.first << endl;
    cout << "Ребра минимального остовного дерева (MST):" << endl;

    for (auto& edge : resultMatrix.second) {
        int u = edge.first;
        int v = edge.second;
        int weight = 0;
        for (auto& e : graph[u]) {
            if (e.dest == v) {
                weight = e.weight;
                break;
            }
        }
        cout << u + 1 << " - " << v + 1 << " : " << weight << endl;
    }



    cout << "Алгоритм Краскала: " << endl;

    //Структура для полного Графа
    vector<Edge> edges = {
        {0, 1, 2}, {0, 3, 8}, {0, 4, 2}, {1, 2, 3}, {1, 3, 10},
        {1, 4, 5}, {2, 4, 12}, {2, 7, 7}, {3, 4, 14}, {3, 5, 3},
        {3, 6, 1}, {4, 5, 11}, {4, 6, 4}, {4, 7, 8}, {5, 6, 6},
        {6, 7, 9}
    };

    pair<int, vector<pair<int, int>>> resultKruskal = kruskalMST(V, edges);

    cout << "Вес минимального остовного дерева (MST): " << resultKruskal.first << endl;
    cout << "Ребра минимального остовного дерева (MST):" << endl;
        for (auto& edge : resultKruskal.second) {
            int u = edge.first;
            int v = edge.second;
            int weight = 0;
            for (auto& e : edges) {
                if ((e.src == u && e.dest == v) || (e.src == v && e.dest == u)) {
                    weight = e.weight;
                    break;
                }
            }
            cout << u + 1 << " - " << v + 1 << " : " << weight << endl;
        }

    return 0;
}
