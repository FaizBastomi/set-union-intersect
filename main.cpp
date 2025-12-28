#include "interUni.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;

vector<int> splitToInt(const string &str, char delimiter)
{
    vector<int> numbers;
    stringstream ss(str);
    string item;
    while (getline(ss, item, delimiter))
    {
        if (!item.empty())
        {
            numbers.push_back(stoi(item));
        }
    }
    return numbers;
}

int main()
{
    List H1, H2, resUnion, resIntersection, seen;
    createList(H1);
    createList(H2);
    createList(resUnion);
    createList(resIntersection);
    createList(seen);

    cout << "Masukkan elemen himpunan pertama (pisahkan dengan koma): ";
    string input1;
    getline(cin, input1);
    vector<int> elements1 = splitToInt(input1, ',');
    for (int elem : elements1)
    {
        adrNode newNode = createNewNode(elem);
        insertNewNode(H1, newNode);
    }

    cout << "Masukkan elemen himpunan kedua (pisahkan dengan koma): ";
    string input2;
    getline(cin, input2);
    vector<int> elements2 = splitToInt(input2, ',');
    for (int elem : elements2)
    {
        adrNode newNode = createNewNode(elem);
        insertNewNode(H2, newNode);
    }

    printList(H1);
    printList(H2);

    auto start = chrono::high_resolution_clock::now();
    unionIteratif(H1, H2, resUnion);
    auto end = chrono::high_resolution_clock::now();
    auto unionIteratifDuration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Hasil union iteratif: ";
    adrNode p = resUnion.first;
    while (p != nullptr)
    {
        cout << p->info << " ";
        p = p->next;
    }
    cout << "Waktu eksekusi union iteratif: " << unionIteratifDuration << " mikrodetik" << endl;

    deleteAllNodes(resUnion); /* Reset */
    start = chrono::high_resolution_clock::now();
    unionRecursive(H1.first, resUnion);
    unionRecursive(H2.first, resUnion);
    end = chrono::high_resolution_clock::now();
    auto unionRecursiveDuration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Hasil union rekursif: ";
    p = resUnion.first;
    while (p != nullptr)
    {
        cout << p->info << " ";
        p = p->next;
    }
    cout << "Waktu eksekusi union rekursif: " << unionRecursiveDuration << " mikrodetik" << endl;

    start = chrono::high_resolution_clock::now();
    intersectionIteratif(H1, H2, resIntersection);
    end = chrono::high_resolution_clock::now();
    auto intersectionIteratifDuration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Hasil irisan iteratif: ";
    p = resIntersection.first;
    while (p != nullptr)
    {
        cout << p->info << " ";
        p = p->next;
    }
    cout << "Waktu eksekusi irisan iteratif: " << intersectionIteratifDuration << " mikrodetik" << endl;

    deleteAllNodes(resIntersection); /* Reset */
    start = chrono::high_resolution_clock::now();
    intersectionRecursive(H1.first, H2, resIntersection);
    end = chrono::high_resolution_clock::now();
    auto intersectionRecursiveDuration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Hasil irisan rekursif: ";
    p = resIntersection.first;
    while (p != nullptr)
    {
        cout << p->info << " ";
        p = p->next;
    }
    cout << "Waktu eksekusi irisan rekursif: " << intersectionRecursiveDuration << " mikrodetik" << endl;

    deleteAllNodes(resUnion);
    deleteAllNodes(resIntersection);
    deleteAllNodes(H1);
    deleteAllNodes(H2);
    return 0;
}