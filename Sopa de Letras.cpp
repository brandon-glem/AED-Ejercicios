#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Función para encontrar la cantidad de veces que una palabra se repite en la sopa de letras
int contarRepeticiones(vector<string> sopa, string palabra) {
    int filas = sopa.size();
    int columnas = sopa[0].size();
    int contador = 0;

    // Búsqueda horizontal normal y al revés
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            string subcadena = sopa[i].substr(j, palabra.length());
            string subcadenaReversa = subcadena;
            reverse(subcadenaReversa.begin(), subcadenaReversa.end());

            if (subcadena == palabra || subcadenaReversa == palabra) {
                contador++;
            }
        }
    }

    // Búsqueda vertical normal y al revés
    for (int j = 0; j < columnas; ++j) {
        for (int i = 0; i < filas; ++i) {
            string vertical;
            string verticalReversa;
            for (int k = 0; k < palabra.length(); ++k) {
                if (i + k < filas) {
                    vertical += sopa[i + k][j];
                }
                if (i - k >= 0) {
                    verticalReversa += sopa[i - k][j];
                }
            }

            if (vertical == palabra || verticalReversa == palabra) {
                contador++;
            }
        }
    }

    return contador;
}

int main() {
    // Sopa de letras
    vector<string> sopa = {
        "ajpato",
        "mlotap",
        "ntthlo",
        "khatol",
        "ttpojm"
    };

    string palabra = "pato";

    int repeticiones = contarRepeticiones(sopa, palabra);

    cout << "La palabra '" << palabra << "' se repite " << repeticiones << " veces en la sopa de letras." << endl;

    return 0;
}
