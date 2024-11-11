#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void buildLIS(const vector<int>& start_vector, const vector<vector<int>>& prev, vector<int>& currentLIS, vector<vector<int>>& allLIS, int index) {
    currentLIS.push_back(start_vector[index]);
    if (prev[index].empty()) {
        vector<int> lis(currentLIS.rbegin(), currentLIS.rend());
        allLIS.push_back(lis);
    }
    else {
        for (int prevIndex : prev[index]) {
            buildLIS(start_vector, prev, currentLIS, allLIS, prevIndex);
        }
    }
    currentLIS.pop_back();
}

vector<vector<int>> findAllLIS(vector<int> start_vector) {
    int n  = (int)start_vector.size();
    vector<int> d(n, 1); // Длина LIS, заканчивающейся на каждом элементе
    vector<vector<int>> prev(n); // Хранит индексы предыдущих элементов в LIS

    // Вычисление длины LIS, заканчивающейся на каждом элементе
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (start_vector[j] < start_vector[i] && d[j] + 1 > d[i]) {
                d[i] = d[j] + 1;
                prev[i].clear();
                prev[i].push_back(j);
            }
            else if (start_vector[j] < start_vector[i] && d[j] + 1 == d[i]) {
                prev[i].push_back(j);
            }
        }
    }

    // Нахождение максимальной длины LIS
    int maxLength = *max_element(d.begin(), d.end());

    // Восстановление всех LIS
    vector<vector<int>> allLIS;
    vector<int> currentLIS;

    for (int i = 0; i < n; ++i) {
        if (d[i] == maxLength) {
            buildLIS(start_vector, prev, currentLIS, allLIS, i);
        }
    }

    return allLIS;
}

int main() {
    setlocale(LC_ALL, "ru");
    vector<int> start_vector;
    int N;
    cout << "Введите длину последовательности:"; cin >> N;
    for (int i = 0; i < N; i++)
    {
        cout << "Введите " << i + 1 << " элемент подпоследовательности: ";
        int a; cin >> a;
        start_vector.push_back(a);
    }

    vector<vector<int>> allLIS = findAllLIS(start_vector);

    cout << "Все максимальные возрастающие подпоследовательности: " << endl;
    for (const auto& lis : allLIS) {
        cout << "Длина последовательности: " << lis.size() << endl;
        for (int num : lis) {
            cout << num << " ";
        }
        cout << endl;
        
    }

    cout << "Количество таких подпоследовательностей: " << allLIS.size() << endl;

    return 0;
}
