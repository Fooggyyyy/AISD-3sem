#include <iostream>
#include <vector>
using namespace std;

//W - ��� �����
//V - �������� �����
//M - ����������� ��������
//n - ���������� �����
void BackPackTask(int W[], int V[], int M, int n)
{
    // ������� ��������� ������ ��� �������� ������������ ���������
    int** B = new int* [n + 1];
    for (int i = 0; i <= n; ++i) {
        B[i] = new int[M + 1];
    }

    // �������������� ��� �������� 0-��
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= M; j++)
            B[i][j] = 0;

    // ��������� ������� ��������
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

    // ��������� ����� �� ������
    cout << "������������ �������� �������:\t" << B[n][M] << endl;

    cout << "��������� ����: " << endl;

    //��������� ��������
    int remainingCapacity = M;
    for (int currentItem = n; currentItem > 0; currentItem--) {
        if (B[currentItem][remainingCapacity] != B[currentItem - 1][remainingCapacity]) {
            cout << "\t������� " << currentItem
                << " � W = " << W[currentItem - 1]
                << " � V = " << V[currentItem - 1] << endl;
            remainingCapacity -= W[currentItem - 1];
        }
    }

    // ������ ������
    for (int i = 0; i <= n; ++i) {
        delete[] B[i];
    }
    delete[] B;
}

int main()
{
    setlocale(LC_ALL, "ru");
    cout << "������� ������������ ����������� �������: ";
    int M; cin >> M;

    cout << "������� ���������� ����� ��� ����������: ";
    int n; cin >> n;

    int* W = new int[n];
    int* V = new int[n];

    for (int i = 0; i < n; i++) {
        cout << "������� ��� � �������� " << i + 1 << " ��������: ";
        cin >> W[i] >> V[i];
    }

    BackPackTask(W, V, M, n);

    delete[] W;
    delete[] V;

    return 0;
}