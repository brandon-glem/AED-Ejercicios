#include <iostream>
#include <thread>
#include <vector>

using namespace std;

struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(int val) {
        valor = val;
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

void inorder(Nodo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    inorder(nodo->izquierdo);
    cout << nodo->valor << " ";
    inorder(nodo->derecho);
}

Nodo* tree(int hojas[], int inicio, int fin) {
    if (inicio == fin) {
        return new Nodo(hojas[inicio]);
    }

    int suma = 0;
    for (int i = inicio; i <= fin; i++) {
        suma += hojas[i];
    }

    Nodo* raiz = new Nodo(suma);
    int mitad = (inicio + fin) / 2;

    raiz->izquierdo = tree(hojas, inicio, mitad);
    raiz->derecho = tree(hojas, mitad + 1, fin);

    return raiz;
}

void buildSubTree(vector<int>& hojas, int inicio, int fin, Nodo* nodo) {
    if (inicio == fin) {
        nodo->valor = hojas[inicio];
        return;
    }

    int suma = 0;
    for (int i = inicio; i <= fin; i++) {
        suma += hojas[i];
    }

    nodo->valor = suma;

    int mitad = (inicio + fin) / 2;

    Nodo* nodoIzquierdo = new Nodo(0);
    Nodo* nodoDerecho = new Nodo(0);

    thread t1(buildSubTree, ref(hojas), inicio, mitad, nodoIzquierdo);
    thread t2(buildSubTree, ref(hojas), mitad + 1, fin, nodoDerecho);

    t1.join();
    t2.join();

    nodo->izquierdo = nodoIzquierdo;
    nodo->derecho = nodoDerecho;
}

void tree(vector<int>& hojas, Nodo* arbol) {
    buildSubTree(hojas, 0, hojas.size() - 1, arbol);
}

int main() {
    vector<int> hojas = { 31, 2, 20, 12, 29, 8, 10, 23, 18, 4, 6, 17, 7, 15, 5, 21, 26, 11, 14, 24 };
    Nodo* arbol = new Nodo(0);

    tree(hojas, arbol);

    inorder(arbol);
    cout << endl;

    delete arbol;

    return 0;
}

/*
int main() {

    int hojas[8] = { 20,13,16,18,21,8,25,17 };
    int n = sizeof(hojas) / sizeof(hojas[0]);

    Nodo* arbol = tree(hojas, 0, n - 1);

    inorder(arbol);

    /////////////////////////////////////////////////
    //int hojas[8] = { 20, 13, 16, 18, 21, 8, 25, 17 };
    /*
    int hojas[20] = {31, 2, 20, 12, 29, 8, 10, 23, 18, 4, 6, 17, 7, 15, 5, 21, 26, 11, 14, 24};

    int n = sizeof(hojas) / sizeof(hojas[0]);

    Nodo* arbolS_T = tree(hojas, 0, n - 1);

    inorder(arbolS_T);
    cout << endl;
    
    delete arbolS_T;
    return 0;
}*/