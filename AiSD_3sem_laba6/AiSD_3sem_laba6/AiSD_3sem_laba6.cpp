#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

// Узел
struct Node {
    char symbol;
    int frequency;
    Node* left;
    Node* right;

    Node(char symbol, int frequency) : symbol(symbol), frequency(frequency), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;  // Меньшая частота — выше приоритет
    }
};

Node* buildHuffmanTree(const unordered_map<char, int>& frequencies) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto pair : frequencies) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* merged = new Node('\0', left->frequency + right->frequency);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    return pq.top();  // Корень дерева — единственный оставшийся элемент
}

void buildHuffmanCodes(Node* root, const string& str, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCodes[root->symbol] = str;
    }

    buildHuffmanCodes(root->left, str + "0", huffmanCodes);
    buildHuffmanCodes(root->right, str + "1", huffmanCodes);
}

string encode(const string& text, const unordered_map<char, string>& huffmanCodes) {
    string encodedText = "";
    for (char ch : text) {
        encodedText += huffmanCodes.at(ch);
    }
    return encodedText;
}

// Функция для декодирования закодированного текста
string decode(const string& encodedText, Node* root) {
    string decodedText = "";
    Node* currentNode = root;
    for (char bit : encodedText) {
        if (bit == '0') {
            currentNode = currentNode->left;
        }
        else {
            currentNode = currentNode->right;
        }

        if (!currentNode->left && !currentNode->right) {
            decodedText += currentNode->symbol;
            currentNode = root;  // Возвращаемся к корню для поиска следующего символа
        }
    }
    return decodedText;
}

unordered_map<char, int> calculateFrequencies(const string& text) {
    unordered_map<char, int> frequencies;
    for (char ch : text) {
        frequencies[ch]++;
    }
    return frequencies;
}

void printFrequencies(const unordered_map<char, int>& frequencies) {
    cout << "Частоты символов:\n";
    for (auto pair : frequencies) {
        cout << pair.first << ": " << pair.second << "\n";
    }
}

void printHuffmanCodes(const unordered_map<char, string>& huffmanCodes) {
    cout << "\nКоды символов:\n";
    for (auto pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << "\n";
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string text;

    cout << "Введите текст: ";
    std::getline(cin, text);

    unordered_map<char, int> frequencies = calculateFrequencies(text);
    Node* root = buildHuffmanTree(frequencies);

    unordered_map<char, string> huffmanCodes;
    buildHuffmanCodes(root, "", huffmanCodes);

    string encodedText = encode(text, huffmanCodes);
    string decodedText = decode(encodedText, root);  // Декодируем сообщение

    printFrequencies(frequencies);
    printHuffmanCodes(huffmanCodes);
    cout << "\nЗакодированное сообщение: " << encodedText << "\n";
    cout << "Декодированное сообщение: " << decodedText << "\n";  // Выводим декодированное сообщение

    return 0;
}