#include <iostream>

using namespace std;

class pila
{
public:
    void push(int x) {
        if (!top) {
            top = A;
            *top = x;
        }
        else {
            if (top < f) {
                top++;
                *top = x;
            }
            else
                cout << "pila llena" << endl;
        }
    }
    int pop() {
        int temp = 0;
        if (top) {
            temp = *top;
            top--;
        }
        else
            cout << "pila vacia" << endl;
        return temp;
    }
    
    void mostrar() {
        int* temp = top;
        cout << "Contenido de la pila: ";
        while (temp >= i) {
            cout << *temp << " ";
            temp--;
        }
        cout << endl;
    }

private:
    int A[10];
    int* i = A, * f = A + 9, * top = NULL;
};

class cola {
private:
    int A[10];
    int* i = A, * f = A + 10, * top = NULL;
public:
    void push(int x) {
        if (!top) {
            top = A;
            *top = x;
            top++;
        }
        else if (top == f) {
            if (*A > NULL) {
                cout << "Cola llena" << endl;
            }
            else {
                top = A;
                *top = x;
                top++;
            }
        }
        else {
            if (top < f && top != i) {
                *top = x;
                top++;
            }
            else {
                cout << "cola llena" << endl;
            }

        }
    }
    int pop() {
        int temp = NULL;
        if (i == f) {
            if (*A != NULL) {
                i = A;
                temp = *i;
                *i = NULL;
                i++;
            }
            else {
                cout << "pila vacia" << endl;
                i = A;
                top = NULL;
            }
        }
        else if (i < f && *i != NULL) {
            temp = *i;
            *i = NULL;
            i++;
        }
        else {
            cout << "pila vacia" << endl;
            i = A;
            top = NULL;
        }
        return temp;
    }

    void mostrar() {
        int* temp = i;
        cout << "Contenido de la cola: ";
        while (temp < f) {
            cout << *temp << " ";
            temp++;
        }
        cout << endl;
    }
};

int main() {
    pila A;
    for (int i = 22; i < 32; i = i + 2)
        A.push(i);
    A.pop();
    A.pop();

    A.push(6);
    A.push(7);

    A.push(9);
    A.push(10);
    A.push(11);
    A.pop();
    A.pop();
    A.pop();
   

    A.mostrar();
}
