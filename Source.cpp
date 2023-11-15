#include <iostream>
#include <vector>

using namespace std;
//1)Алгоритм "Поиск оптимального пути в треугольнике (на максимум)
int findMaxPathSum(vector<vector<int>>& triangle) {
    int n = triangle.size();

    // Инициализация дополнительного треугольника для хранения сумм путей
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Начальное значение равно значению в вершине треугольника
    dp[0][0] = triangle[0][0];

    // Заполнение динамического треугольника
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            // Рассматриваем два возможных пути сверху
            int fromAboveLeft = (j > 0) ? dp[i - 1][j - 1] : 0;
            int fromAboveRight = (j < i) ? dp[i - 1][j] : 0;

            // Выбираем максимальный путь сверху
            dp[i][j] = triangle[i][j] + max(fromAboveLeft, fromAboveRight);
        }
    }

    // Находим максимальное значение в последнем ряду треугольника
    int maxSum = dp[n - 1][0];
    int maxIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (dp[n - 1][i] > maxSum) {
            maxSum = dp[n - 1][i];
            maxIndex = i;
        }
    }

    // Вывод оптимального пути
    cout << "Максимальное суммарное значение нагрузок: " << maxSum << endl;
    cout << "Оптимальный путь: ";

    // Восстановление оптимального пути
    int row = n - 1;
    int col = maxIndex;
    cout << triangle[row][col] << " ";
    for (int i = row - 1; i >= 0; --i) {
        if (col > 0 && dp[i][col - 1] > dp[i][col]) {
            col = col - 1;
        }
        cout << triangle[i][col] << " ";
    }

    cout << endl;

    return maxSum;
}
//2)
const int INF = INT_MAX; // Значение "бесконечность"

// Структура для представления ребра графа
struct Edge {
    int to;
    int weight;
};

// Функция для поиска оптимального пути с использованием алгоритма Дейкстры
void dijkstra(const vector<vector<Edge>>& graph, int start, vector<int>& distance, vector<int>& parent) {
    int n = graph.size();
    distance.assign(n, INF);
    parent.assign(n, -1);

    distance[start] = 0;

    vector<bool> visited(n, false);

    for (int i = 0; i < n - 1; ++i) {
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (u == -1 || distance[j] < distance[u])) {
                u = j;
            }
        }

        visited[u] = true;

        for (const Edge& edge : graph[u]) {
            if (distance[u] + edge.weight < distance[edge.to]) {
                distance[edge.to] = distance[u] + edge.weight;
                parent[edge.to] = u;
            }
        }
    }
}

// Функция для восстановления пути из начальной вершины к конечной
vector<int> reconstructPath(const vector<int>& parent, int start, int end) {
    vector<int> path;
    for (int at = end; at != -1; at = parent[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}
//3)


std::vector<int> optimalSequence(int n) {
    std::vector<int> dp(n + 1, 0);  // Массив для хранения оптимального количества операций для каждого числа
    std::vector<int> sequence;     // Вектор для хранения последовательности операций

    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + 1;  // Первая операция: умножение на 2

        if (i % 2 == 0 && dp[i / 2] < dp[i]) {
            dp[i] = dp[i / 2] + 1;  // Вторая операция: возведение в квадрат
        }
    }

    // Восстановление последовательности операций
    int current = n;
    while (current > 1) {
        sequence.push_back(current);
        if (current % 2 == 0 && dp[current / 2] == dp[current] - 1) {
            current /= 2;
        }
        else {
            current -= 1;
        }
    }
    sequence.push_back(1);

    return sequence;
}
//4)
string findLongestCommonSubsequence(const string& str1, const string& str2) {
    int m = str1.length();
    int n = str2.length();

    // Создаем таблицу для хранения длин наибольших общих подцепочек
    vector<vector<int>> L(m + 1, vector<int>(n + 1));

    // Заполняем таблицу с использованием алгоритма динамического программирования
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (str1[i - 1] == str2[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
                cout << "Выполнена операция с (" << i << ", " << j << ")" << endl;
            }
            else {
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
            }
        }
    }

    // Восстанавливаем наибольшую общую подцепочку из таблицы
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            lcs = str1[i - 1] + lcs;
            --i;
            --j;
        }
        else if (L[i - 1][j] > L[i][j - 1]) {
            --i;
        }
        else {
            --j;
        }
    }

    return lcs;
}
//5)
// Структура для предмета
struct Item {
    int weight;
    int value;
};

// Функция для решения задачи о рюкзаке
void knapsack(int max_weight, vector<Item>& items) {
    int num_items = items.size();
    vector<vector<int>> dp(num_items + 1, vector<int>(max_weight + 1, 0));
    vector<vector<bool>> keep(num_items + 1, vector<bool>(max_weight + 1, false));

    for (int i = 1; i <= num_items; ++i) {
        for (int w = 1; w <= max_weight; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
                if (dp[i][w] != dp[i - 1][w])
                    keep[i][w] = true;
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int max_value = dp[num_items][max_weight];
    cout << "Максимально возможная суммарная полезность: " << max_value << endl;

    int remaining_weight = max_weight;
    cout << "Номера предметов, которые необходимо положить в рюкзак: ";
    for (int i = num_items; i > 0 && max_value > 0; --i) {
        if (keep[i][remaining_weight]) {
            cout << i << " ";
            max_value -= items[i - 1].value;
            remaining_weight -= items[i - 1].weight;
        }
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RUS");
    int x;
    cout << "введите 1 или 2 или 3 или 4 или 5" << endl;
    cin >> x;
    //1)Алгоритм "Поиск оптимального пути в треугольнике (на максимум)
    if (x == 1) {
        int n;
        cout << "Введите количество строк в треугольнике: ";
        cin >> n;

        vector<vector<int>> triangle(n, vector<int>(n, 0));

        cout << "Введите нагрузки на вершины треугольника:" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= i; ++j) {
                cout << "Введите нагрузку для вершины " << i + 1 << "-" << j + 1 << ": ";
                cin >> triangle[i][j];
            }
        }

        int maxPathSum = findMaxPathSum(triangle);

        return  main();
    }
    //2)
     // Ввод количества вершин
    if (x == 2) {
        int n;
        cout << "Введите количество вершин (4): ";
        cin >> n;

        // Создание графа
        vector<vector<Edge>> graph(n);

        // Ввод нагрузок на рёбра графа
        cout << "Введите нагрузки на рёбра графа:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int weight;
                cout << "Нагрузка между вершиной " << i << " и " << j << " (если нет связи, введите -1): ";
                cin >> weight;

                if (weight != -1) {
                    graph[i].push_back({ j, weight });
                }
            }
        }

        // Ввод начальной и конечной вершин
        int start, end;
        cout << "Введите начальную вершину (0): ";
        cin >> start;
        cout << "Введите конечную вершину (3): ";
        cin >> end;

        // Вызов алгоритма Дейкстры
        vector<int> distance, parent;
        dijkstra(graph, start, distance, parent);

        // Вывод результатов
        cout << "Минимальное суммарное значение нагрузок: " << distance[end] << endl;
        cout << "Оптимальный путь: ";
        vector<int> path = reconstructPath(parent, start, end);
        for (int vertex : path) {
            cout << vertex << " ";
        }
        cout << " " << endl;
        return  main();
    }
    //3)
    if (x == 3) {
        int exponent;
        cout << "Введите положительную степень числа: ";
        cin >> exponent;

        vector<int> sequence = optimalSequence(exponent);

        cout << "Оптимальное количество операций: " << sequence.size() - 1 << std::endl;
        cout << "Последовательность операций: ";
        for (int i = sequence.size() - 1; i >= 0; --i) {
            cout << sequence[i];
            if (i != 0) cout << " -> ";
        }
        cout << endl;

        return main();
    }
    //4)
    if (x == 4) {
        string str1, str2;
        cout << "Введите первую цепочку символов: ";
        cin >> str1;
        cout << "Введите вторую цепочку символов: ";
        cin >> str2;

        string lcs = findLongestCommonSubsequence(str1, str2);
        cout << "Максимально совпадающая общая подцепочка: " << lcs << endl;

        return main();
    }
    //5)
    if (x == 5) {
        int max_weight, num_items;

        cout << "Введите максимально возможный вес рюкзака: ";
        cin >> max_weight;

        cout << "Введите количество предметов: ";
        cin >> num_items;

        vector<Item> items(num_items);
        cout << "Введите вес и полезность каждого предмета:\n";
        for (int i = 0; i < num_items; ++i) {
            cout << "Предмет " << i + 1 << ":\n";
            cout << "Вес: ";
            cin >> items[i].weight;
            cout << "Полезность: ";
            cin >> items[i].value;
        }

        knapsack(max_weight, items);

        return main();
    }
}