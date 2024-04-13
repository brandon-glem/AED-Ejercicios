#include <iostream>
using namespace std;

bool bimbus(int* ini, int fin, int* pos, int valor) {
    int* left = ini;
    int* right = ini + fin - 1;

    while (left <= right) {
        int* mid = left + (right - left) / 2;

        if (*mid == valor) {
            *pos = mid - ini;
            return true;
        }
        else if (*mid < valor) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return false;
}

int main() {
    int arr[] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 45, 65, 95, 135 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int pos;
    int valor = 5;

    if (bimbus(arr, n, &pos, valor)) {
        cout << "El valor " << valor << " se encuentra en la pos " << pos << endl;
    }
    else {
        cout << "El valor " << valor << " no se encontro en el array." << endl;
    }

    return 0;
}
