#include <iostream>
#include <iomanip>
using namespace std;

const int MAX_TAM = 100;

// función para leer datos
void leerDatos(int* ID, float* Valor, int n) {
    for (int i = 0; i < n; i++) {
        cout << "ID[" << i + 1 << "]: ";
        cin >> *(ID + i);
        cout << "Valor[" << i + 1 << "]: ";
        cin >> *(Valor + i);
    }
}

// función para imprimir listas
void imprimirLista(int* ID, float* Valor, int n) {
    for (int i = 0; i < n; i++) {
        cout << "(" << *(ID + i) << ", " << fixed << setprecision(1)
            << *(Valor + i) << ")" << endl;
    }
}

// Algoritmo MergeSort
void merge(int* ID, float* Valor, int inicio, int medio, int fin) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    int LID[MAX_TAM], RID[MAX_TAM];
    float LVal[MAX_TAM], RVal[MAX_TAM];

    for (int i = 0; i < n1; i++) {
        LID[i] = *(ID + inicio + i);
        LVal[i] = *(Valor + inicio + i);
    }
    for (int j = 0; j < n2; j++) {
        RID[j] = *(ID + medio + 1 + j);
        RVal[j] = *(Valor + medio + 1 + j);
    }

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (LID[i] <= RID[j]) {
            *(ID + k) = LID[i];
            *(Valor + k) = LVal[i];
            i++;
        }
        else {
            *(ID + k) = RID[j];
            *(Valor + k) = RVal[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        *(ID + k) = LID[i];
        *(Valor + k) = LVal[i];
        i++;
        k++;
    }
    while (j < n2) {
        *(ID + k) = RID[j];
        *(Valor + k) = RVal[j];
        j++;
        k++;
    }
}

void mergeSort(int* ID, float* Valor, int inicio, int fin) {
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2; // Más seguro para evitar overflow
        mergeSort(ID, Valor, inicio, medio);
        mergeSort(ID, Valor, medio + 1, fin);
        merge(ID, Valor, inicio, medio, fin);
    }
}

// Algoritmo de búsqueda binaria
void busquedaBinaria(int* ID, float* Valor, int n, int buscado) {
    int inicio = 0, fin = n - 1;
    int encontrado = -1;

    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2; 
        if (*(ID + medio) == buscado) {
            encontrado = medio;
            break;
        }
        else if (*(ID + medio) > buscado) {
            fin = medio - 1;
        }
        else {
            inicio = medio + 1;
        }
    }

    if (encontrado == -1) {
        cout << "No se encontraron mediciones para el sensor " << buscado << endl;
        return;
    }

    cout << "--- Resultados ---" << endl;

    // Retroceder a la primera ocurrencia
    int i = encontrado;
    while (i > 0 && *(ID + i - 1) == buscado) 
        i--;

    // Imprimir todas las consecutivas
    while (i < n && *(ID + i) == buscado) {
        cout << "(" << *(ID + i) << ", " << fixed << setprecision(1)
            << *(Valor + i) << ")" << endl;
        i++;
    }
}


int main() {
    int n;
    int ID[MAX_TAM];
    float Valor[MAX_TAM];

    cout << "Ingrese número de mediciones: ";
    cin >> n;

    if (n > MAX_TAM || n <= 0) {
        cout << "Número de mediciones inválido!" << endl;
        return 1;
    }

    leerDatos(ID, Valor, n);

    cout << "--- Lista original ---" << endl;
    imprimirLista(ID, Valor, n);

    mergeSort(ID, Valor, 0, n - 1);

    cout << "--- Lista ordenada por ID (estable) ---" << endl;
    imprimirLista(ID, Valor, n);

    int buscado;
    cout << "Buscar mediciones del sensor ID = ";
    cin >> buscado;

    busquedaBinaria(ID, Valor, n, buscado);

    return 0;
}