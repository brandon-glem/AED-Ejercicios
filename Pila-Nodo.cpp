#include <iostream>

using namespace std;

struct NodoPila {
    int dato;
    NodoPila* siguiente;
};

class Pila {
private:
    NodoPila* tope;

public:
    Pila() {
        tope = nullptr;
    }

    bool estaVacia() {
        return tope == nullptr;
    }

    void push(int dato) {
        NodoPila* nuevoNodo = new NodoPila;
        nuevoNodo->dato = dato;
        nuevoNodo->siguiente = tope;
        tope = nuevoNodo;
    }

    int pop() {
        if (estaVacia()) {
            cout << "La pila está vacía." << endl;
            return -1;
        }
        NodoPila* temp = tope;
        int dato = temp->dato;
        tope = temp->siguiente;
        delete temp;
        return dato;
    }
};

int main() {
    Pila pila;
    pila.push(1);
    pila.push(2);
    pila.push(3);

    while (!pila.estaVacia()) {
        cout << "Elemento de la pila: " << pila.pop() << endl;
    }
    return 0;
}
