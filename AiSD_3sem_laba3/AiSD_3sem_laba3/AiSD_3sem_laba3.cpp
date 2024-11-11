#include <iostream>
#include <vector>
#include <queue>
#include <map> // Для сопоставления вершин с индексами

using namespace std;

// Структура для представления ребра
struct Edge {
    int dest; //В какую вершину
    int weight;// Вес
};

// Функция для добавления ребра в граф
void addEdge(vector<vector<Edge>>& graph, map<char, int>& vertexMap, char src, char dest, int weight)
{
    graph[vertexMap[src]].push_back({ vertexMap[dest], weight });
    graph[vertexMap[dest]].push_back({ vertexMap[src], weight }); // Для неориентированного графа
}

// Функция для выполнения алгоритма Дейкстры
void dijkstra(const vector<vector<Edge>>& graph, map<char, int>& vertexMap, char srcChar) 
{
    int V = graph.size();
    vector<int> dist(V, INT_MAX);
    int src = vertexMap[srcChar];
    dist[src] = 0;

    //Приоритетная очередь, основанная на СД вектор, фильтрующаяся по убыванию
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 
    pq.push({ 0, src });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& edge : graph[u]) { // Перебираем все смежные вершины
            int v = edge.dest;
            int weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({ dist[v], v });
            }
        }
    }

    // Выводим кратчайшие расстояния от srcChar до всех вершин
    cout << "Кратчайшие расстояния от вершины " << srcChar << ":" << endl;
    for (auto& pair : vertexMap) {
        cout << "До вершины " << pair.first << " = " << dist[pair.second] << endl;
    }
}

int main() 
{
    setlocale(LC_ALL, "ru");
    // Имена вершин
    vector<char> vertexNames = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };
    int V = vertexNames.size(); // Количество вершин в графе
    vector<vector<Edge>> graph(V);

    // Маппинг вершин (символ -> индекс)
    map<char, int> vertexMap;
    for (int i = 0; i < V; ++i) {
        vertexMap[vertexNames[i]] = i;
    }
    
    // Добавление рёбер согласно графу
    addEdge(graph, vertexMap, 'A', 'B', 7);
    addEdge(graph, vertexMap, 'A', 'C', 10);
    addEdge(graph, vertexMap, 'B', 'F', 9);
    addEdge(graph, vertexMap, 'B', 'G', 27);
    addEdge(graph, vertexMap, 'C', 'F', 8);
    addEdge(graph, vertexMap, 'C', 'E', 31);
    addEdge(graph, vertexMap, 'F', 'H', 11);
    addEdge(graph, vertexMap, 'E', 'D', 32);
    addEdge(graph, vertexMap, 'H', 'D', 17);
    addEdge(graph, vertexMap, 'D', 'I', 21);
    addEdge(graph, vertexMap, 'G', 'I', 15);
    addEdge(graph, vertexMap, 'B', 'I', 21);


    char init;
    cout << "Введите с какой вершины начать: "; cin >> init;
    
    bool flag = false;
    for (int i = 0; i < vertexNames.size(); i++)
        if (init == vertexNames[i])
            flag = true;
    if (!flag)
    {
        cout << "Не верно введена вершина!!!";
        return -1;
    }
    
    dijkstra(graph, vertexMap, init);

    return 0;
}
