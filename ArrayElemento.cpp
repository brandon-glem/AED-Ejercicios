#include <iostream>

using namespace std;

const int MAX_SIZE = 5;
struct Nodo {
    int valores[MAX_SIZE];
    int cantidad;
    Nodo* siguiente;
    Nodo() : cantidad(0), siguiente(nullptr) {}
};
void insertarOrdenado(Nodo*& cabeza, int valor) {
    if (cabeza == nullptr) {
        cabeza = new Nodo();
        cabeza->valores[0] = valor;
        cabeza->cantidad++;
        return;
    }
    Nodo* actual = cabeza;
    Nodo* anterior = nullptr;
    while (actual != nullptr && actual->cantidad == MAX_SIZE) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == nullptr) {
        anterior->siguiente = new Nodo();
        actual = anterior->siguiente;
    }
    int i = actual->cantidad - 1;
    while (i >= 0 && actual->valores[i] > valor) {
        actual->valores[i + 1] = actual->valores[i];
        i--;
    }
    actual->valores[i + 1] = valor;
    actual->cantidad++;
    if (actual->cantidad == MAX_SIZE) {
        actual->siguiente = new Nodo();
    }
}
void imprimirLista(Nodo* cabeza) {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        for (int i = 0; i < actual->cantidad; ++i) {
            cout << actual->valores[i] << " ";
        }
        actual = actual->siguiente;
    }
}
void eliminar(Nodo*& cabeza, int valor) {
    Nodo* actual = cabeza;
    Nodo* anterior = nullptr;
    while (actual != nullptr) {
        bool encontrado = false;
        for (int i = 0; i < actual->cantidad; ++i) {
            if (actual->valores[i] == valor) {
                encontrado = true;
                for (int j = i; j < actual->cantidad - 1; ++j) {
                    actual->valores[j] = actual->valores[j + 1];
                }
                actual->cantidad--;
                if (actual->siguiente != nullptr) {
                    Nodo* siguiente = actual->siguiente;
                    actual->valores[actual->cantidad] = siguiente->valores[0];
                    for (int k = 0; k < siguiente->cantidad - 1; ++k) {
                        siguiente->valores[k] = siguiente->valores[k + 1];
                    }
                    siguiente->cantidad--;
                    actual->cantidad++;
                    if (siguiente->cantidad == 0) {
                        actual->siguiente = siguiente->siguiente;
                        delete siguiente;
                    }
                }
                break;
            }
        }
        if (encontrado) {
            break;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
}

int main() {
    Nodo* cabeza = nullptr;

    insertarOrdenado(cabeza, 15);
    insertarOrdenado(cabeza, 48);
    insertarOrdenado(cabeza, 2);
    insertarOrdenado(cabeza, 21);
    insertarOrdenado(cabeza, 13);
    insertarOrdenado(cabeza, 69);
    imprimirLista(cabeza);
    eliminar(cabeza,21);
    return 0;
}
