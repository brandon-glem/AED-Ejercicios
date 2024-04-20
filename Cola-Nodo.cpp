#include <iostream>

using namespace std;

struct NodoCola {
    int dato;
    NodoCola* siguiente;
};

class Cola {
private:
    NodoCola* frente;
    NodoCola* final;

public:
    Cola() {
        frente = nullptr;
        final = nullptr;
    }

    bool estaVacia() {
        return frente == nullptr;
    }

    void push(int dato) {
        NodoCola* nuevoNodo = new NodoCola;
        nuevoNodo->dato = dato;
        nuevoNodo->siguiente = nullptr;
        if (estaVacia()) {
            frente = nuevoNodo;
        } else {
            final->siguiente = nuevoNodo;
        }
        final = nuevoNodo;
    }

    int pop() {
        if (estaVacia()) {
            cout << "La cola está vacía." << endl;
            return -1;
        }
        NodoCola* temp = frente;
        int dato = temp->dato;
        frente = temp->siguiente;
        if (frente == nullptr) {
            final = nullptr;
        }
        delete temp;
        return dato;
    }
};

int main() {
    Cola cola;
    cola.push(1);
    cola.push(2);
    cola.push(3);

    while (!cola.estaVacia()) {
        cout << "Elemento de la cola: " << cola.pop() << endl;
    }
    return 0;
}
