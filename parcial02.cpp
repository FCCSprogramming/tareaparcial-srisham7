#include <iostream>
#include <iomanip>
using namespace std;

// Calcular la transpuesta 
void CalcularTranspuesta(double* A, double* AT, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(AT + i * n + j) = *(A + j * n + i);
        }
    }
}

// Calcular la Inercia I = A * B
void CalcularInercia(double* A, double* B, double* I, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(I + i * n + j) = 0;
            for (int k = 0; k < n; k++) {
                *(I + i * n + j) += *(A + i * n + k) * *(B + k * n + j);
            }
        }
    }
}

// Calcular la traza
void TrazaInercia(double* I, int n, double& traza) {
    traza = 0;
    for (int i = 0; i < n; i++) {
        traza += *(I + i * n + i);
    }
}

// Calcular la energía normalizada
void EnergiaNormalizada(double* I, int n, double& E) {
    E = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            E += *(I + i * n + j) * *(I + i * n + j);
        }
    }
    E /= (n * n);
}

// Imprimir la matriz
void ImprimirMatriz(double* M, int n, const string& titulo) {
    cout << titulo << endl;
    cout << fixed << setprecision(2);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(6) << *(M + i * n + j);
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    const int N = 3;
    double A[N][N] = { {1, 2, 3}, {0, 1, 4}, {2, 0, 1} };
    double AT[N][N];
    double I[N][N];
    double traza;
    double E;

    cout << "N = " << N << endl;

    ImprimirMatriz(*A, N, "Matriz A:");

    CalcularTranspuesta(*A, *AT, N);
    CalcularInercia(*A, *AT, *I, N);
    TrazaInercia(*I, N, traza);
    EnergiaNormalizada(*I, N, E);

    ImprimirMatriz(*AT, N, "Transpuesta A^T:");
    ImprimirMatriz(*I, N, "Matriz de Inercia I = A * A^T:");

    cout << "Traza(I) = " << fixed << setprecision(2) << traza << endl;
    cout << "Energía normalizada E = " << fixed << setprecision(2) << E << endl;

    return 0;
}
