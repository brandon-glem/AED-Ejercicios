#include <iostream>

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

int main() {
    int hojas[8] = { 20,13,16,18,21,8,25,17 };
    int n = sizeof(hojas) / sizeof(hojas[0]);

    Nodo* arbol = tree(hojas, 0, n - 1);

    inorder(arbol);

    return 0;
}