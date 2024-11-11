#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <Windows.h>

using namespace std;

#define V 8          
#define GENES ABCDE   // Определение набора генов
#define START 0       

int child = 0;             // Количество потомков при каждом скрещивании
int populationSize = 0;    // Размер популяции (число маршрутов)
int evoCount = 0;          // Количество поколений 

int cities[V][V] = { { INT_MAX, 25, 40, 31, 27, 10, 5, 9},
                    { 5, INT_MAX, 17, 30, 25, 15, 20, 10},
                    { 19, 15, INT_MAX, 6, 1, 20, 30, 25},
                    { 9, 50, 24, INT_MAX, 6, 10, 5, 9 },
                    { 22, 8, 7, 10, INT_MAX, 15, 20, 10 },
                    { 10, 15, 20, 10, 15, INT_MAX, 17, 30 },
                    { 5, 20, 30, 5, 20, 17, INT_MAX, 6 },
                    { 9, 10, 25, 9, 10, 30, 6, INT_MAX } };

struct individual {
    string gnome;    // Геном - представление маршрута
    int fitness;     
};


int rand_num(int start, int end) {
    int r = end - start;
    int rnum = start + rand() % r;
    return rnum;
}

// Проверка, повторяется ли город (ген) в строке маршрута (геноме)
bool repeat(string s, char ch) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ch)
            return true;
    }
    return false;
}

// Мутация маршрута  - случайная перестановка двух городов
string mutatedGene(string gnome) {
    while (true) {
        int r = rand_num(1, V);  
        int r1 = rand_num(1, V); 
        if (r1 != r) {
            char temp = gnome[r];
            gnome[r] = gnome[r1];
            gnome[r1] = temp;
            break;
        }
    }
    return gnome;
}

// Функция создания начального маршрута в случайном порядке
string create_gnome() {
    string gnome = "0"; // Начинаем с города 0
    while (true) {
        if (gnome.size() == V) {
            gnome += gnome[0]; // Возвращение к стартовому городу для замкнутого маршрута
            break;
        }
        int temp = rand_num(1, V);
        if (!repeat(gnome, (char)(temp + 48)))
            gnome += (char)(temp + 48);
    }
    return gnome;
}

// Функция для вычисления длины маршрута 
int cal_fitness(string gnome) {
    int f = 0;
    for (int i = 0; i < gnome.size() - 1; i++) {
        if (cities[gnome[i] - 48][gnome[i + 1] - 48] == INT_MAX)
            return INT_MAX; // Возвращаем максимальное значение, если города не соединены
        f += cities[gnome[i] - 48][gnome[i + 1] - 48];
    }
    return f;
}

// Функция сравнения для сортировки популяции по приспособленности
bool lessthan(struct individual t1, struct individual t2) {
    return t1.fitness < t2.fitness;
}

// Основная функция генетического алгоритма для нахождения минимального пути
void Genetic_algo(int cities[V][V]) {
    int gen = 1;          // Номер текущего поколения
    int gen_thres = evoCount; // Ограничение по числу поколений

    vector<struct individual> population; // Текущая популяция
    struct individual temp;

    // Инициализация начальной популяции
    for (int i = 0; i < populationSize; i++) {
        temp.gnome = create_gnome();
        temp.fitness = cal_fitness(temp.gnome);
        population.push_back(temp);
    }

    // Вывод начальной популяции
    cout << "\nСтартовая популяция: " << endl;
    cout << "Геном популяции \t||вес генома\n";
    for (int i = 0; i < populationSize; i++)
        cout << population[i].gnome << "\t\t\t" << population[i].fitness << endl;
    cout << "\n";


    // Сортировка популяции по приспособленности
    sort(population.begin(), population.end(), lessthan);

    // Эволюционный цикл
    while (gen <= gen_thres) {
        cout << endl << "Лучший геном: " << population[0].gnome;
        cout << " его вес: " << population[0].fitness << "\n\n";

        vector<struct individual> new_population; // Новое поколение

        // Генерация потомков
        for (int i = 0; i < child; i++) {
            struct individual p1 = population[i]; // Родитель

            while (true) {
                // Мутация родителя для создания потомка
                string new_g = mutatedGene(p1.gnome);
                struct individual new_gnome;
                new_gnome.gnome = new_g;
                new_gnome.fitness = cal_fitness(new_gnome.gnome);

                // Добавляем нового потомка, если он не хуже родителя
                if (new_gnome.fitness <= population[i].fitness) {
                    new_population.push_back(new_gnome);
                    break;
                }
                else {
                    new_gnome.fitness = INT_MAX;
                    new_population.push_back(new_gnome);
                    break;
                }
            }
        }

        // Объединение старого поколения с потомками и сортировка
        for (int i = 0; i < child; i++) {
            population.push_back(new_population[i]);
        }
        sort(population.begin(), population.end(), lessthan);

        // Удаление лишних особей для поддержания размера популяции
        for (int i = 0; i < child; i++) {
            population.pop_back();
        }

        // Вывод информации о текущем поколении
        cout << "Поколение " << gen << " \n";
        cout << "Геном популяции \t||вес генома\n";
        for (int i = 0; i < populationSize; i++)
            cout << population[i].gnome << "\t\t\t" << population[i].fitness << endl;
        gen++;
    }
    // Вывод оптимального маршрута
    cout << "\n\nНаиболее оптимальный маршрут, найденный генетическим алгоритмом с текущими параметрами: ";
    cout << population[0].gnome;
    cout << "\n\n";
}

int main() {
    setlocale(LC_ALL, "ru");
    do {
        cout << "Введите размер популяций: ";
        cin >> populationSize;
        cin.clear();
        cin.ignore(32767, '\n');
    } while (populationSize <= 0);

    do {
        cout << "Введите количество потомков в одной популяции: ";
        cin >> child;
        cin.clear();
        cin.ignore(32767, '\n');
    } while (child <= 0);

    do {
        cout << "Введите количество эволюций: ";
        cin >> evoCount;
        cin.clear();
        cin.ignore(32767, '\n');
    } while (evoCount <= 0);

    // Запуск генетического алгоритма
    Genetic_algo(cities);
}
