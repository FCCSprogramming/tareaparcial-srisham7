#include <iostream>
#include <cstring>
using namespace std;

const int MAX_FRASES = 5;
const int MAX_LONG = 100; 
const int MAX_PALABRA = 20;


// Leer frases y guardar en la matriz.
void leerFrases(char frases[][MAX_LONG], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Frase " << i + 1 << ": ";
        cin.getline(frases[i], MAX_LONG);
    }
}

int contarApariciones(const char frase[], const char palabra[]) {
    const char delimitadores[] = " ,.;:!?";
    char copia[MAX_LONG];
    strcpy_s(copia, MAX_LONG, frase);

    int contador = 0;
    char* context = nullptr;
    char* token = strtok_s(copia, delimitadores, &context);

    while (token != nullptr) {
        if (strcmp(token, palabra) == 0) { 
            contador++;
        }
        token = strtok_s(nullptr, delimitadores, &context);
    }

    return contador;
}


// frase con el mayor número de apariciones.
int buscarFraseMaxima(int apariciones[], int n) {
    int max = apariciones[0];
    int indice = 0;
    for (int i = 1; i < n; i++) {
        if (apariciones[i] > max) {
            max = apariciones[i];
            indice = i;
        }
    }
    return indice;
}

void mostrarResultados(char frases[][MAX_LONG], int apariciones[], int n, int indiceMax, const char palabra[]) {
    cout << "---- Resultados ----" << endl;
    bool hayCoincidencias = false;

    // cuántas veces aparece la palabra en cada frase
    for (int i = 0; i < n; i++) {
        cout << "Frase " << i + 1 << " → " << apariciones[i] << " aparición(es)\n";
        if (apariciones[i] > 0)
            hayCoincidencias = true;
    }

    // si la palabra no aparece
    if (!hayCoincidencias) {
        cout << "La palabra " << palabra << " no aparece en ninguna frase." << endl;
        return;
    }

    // Mostrar la frase con más apariciones
    cout << "\nLa palabra aparece más veces en la frase " << indiceMax + 1 << ":\n";
    cout << frases[indiceMax] << endl;
    cout << "Longitud de la frase: " << strlen(frases[indiceMax]) << " caracteres\n";
}


int main() {
    int n;
    char frases[MAX_FRASES][MAX_LONG];
    char palabra[MAX_PALABRA];

    cout << "Ingrese el número de frases (máx. 5): ";
    cin >> n;
    cin.ignore();

    if (n < 1 || n > 5) {
        cout << "Número inválido de frases." << endl;
        return 0;
    }

    leerFrases(frases, n);

    cout << "Ingrese la palabra clave: ";
    cin.getline(palabra, MAX_PALABRA);

    int apariciones[MAX_FRASES];
    for (int i = 0; i < n; i++) {
        apariciones[i] = contarApariciones(frases[i], palabra);
    }

    int indiceMax = buscarFraseMaxima(apariciones, n);

    mostrarResultados(frases, apariciones, n, indiceMax, palabra);

    return 0;
}

