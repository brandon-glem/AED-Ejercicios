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
private:
    int A[10];
    int* i = A, * f = A + 9, * top = NULL;
};

class cola {
private:
    int A[10];
    int* i = A, * f = A + 9, * top = NULL;
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
            else {
                if (top == f) {
                    int* n = A;
                    while (true) {
                        if (*n == NULL) {
                            *n = x;
                            break;
                        }
                        else if (n == i) {
                            cout << "pila llena" << endl;
                            break;
                        }
                        else
                            n++;
                    }
                }

            }
        }
    }
    int pop() {
        int temp = 0;
        if (i) {
            temp = *i;
            *i = NULL;
            i++;
        }
        else
            cout << "pila vacia" << endl;
        return temp;
    }

};

int main() {
    cola A;
    for (int i = 22; i < 42; i = i + 2)
        A.push(i);
    A.pop();
    A.pop();
    A.pop();
    A.pop();

    A.push(6);
    A.push(7);
    A.push(8);
    A.push(9);
    A.push(10);

}