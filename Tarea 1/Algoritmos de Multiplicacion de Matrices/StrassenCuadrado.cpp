//Código base https://www.geeksforgeeks.org/strassens-matrix-multiplication-algorithm-implementation/, modificado por ChatGPT
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace chrono;
typedef long long lld;

//Umbral para cambiar a multiplicación tradicional
const int THRESHOLD = 64;

/*
***** Función: MatrixMultiply
*** Parámetros:
* lld** a: Primera matriz a multiplicar.
* lld** b: Segunda matriz a multiplicar.
* int n: Número de filas y columnas de las matrices (matrices cuadradas).
* int l: No se usa (para mantener la firma, pero la función trabaja solo con matrices cuadradas).
* int m: No se usa (para mantener la firma, pero la función trabaja solo con matrices cuadradas).
*** Return:
* lld**: Matriz resultado de la multiplicación de matrices.
*** Descripción:
* Realiza la multiplicación de matrices tradicional. Crea una matriz resultado 'result' de tamaño n x n
* y la llena con el producto de las matrices 'a' y 'b'.
*****
*/
lld** MatrixMultiply(lld** a, lld** b, int n, int l, int m) {
    lld** result = new lld*[n];
    for (int i = 0; i < n; ++i) {
        result[i] = new lld[m];
        for (int j = 0; j < m; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < l; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

/*
***** Función: add
*** Parámetros:
* lld** a: Primera matriz a sumar.
* lld** b: Segunda matriz a sumar.
* lld** result: Matriz resultado de la suma.
* int size: Tamaño de las matrices (matrices cuadradas).
*** Return:
* void
*** Descripción:
* Realiza la suma de matrices 'a' y 'b', almacenando el resultado en 'result'.
*****
*/
void add(lld** a, lld** b, lld** result, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

/*
***** Función: subtract
*** Parámetros:
* lld** a: Primera matriz a restar.
* lld** b: Segunda matriz a restar.
* lld** result: Matriz resultado de la resta.
* int size: Tamaño de las matrices (matrices cuadradas).
*** Return:
* void
*** Descripción:
* Realiza la resta de matrices 'a' y 'b', almacenando el resultado en 'result'.
*****
*/
void subtract(lld** a, lld** b, lld** result, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result[i][j] = a[i][j] - b[i][j];
        }
    }
}

/*
***** Función: Strassen
*** Parámetros:
* lld** a: Primera matriz a multiplicar.
* lld** b: Segunda matriz a multiplicar.
* int n: Tamaño de las matrices (matrices cuadradas).
*** Return:
* lld**: Matriz resultado de la multiplicación de matrices utilizando el algoritmo de Strassen.
*** Descripción:
* La función implementa una versión optimizada del algoritmo de Strassen para multiplicación de matrices.
* Si el tamaño de la matriz es menor o igual que el umbral, se utiliza la multiplicación tradicional.
* En caso contrario, la matriz se divide en submatrices y se calculan 7 productos intermedios utilizando Strassen.
* Finalmente, se combinan los resultados intermedios para obtener la matriz resultante.
*****
*/
lld** Strassen(lld** a, lld** b, int n) {
    if (n <= THRESHOLD) {
        return MatrixMultiply(a, b, n, n, n);
    }
    int newSize = n / 2;
    lld** result = new lld*[n];
    for (int i = 0; i < n; ++i) {
        result[i] = new lld[n];
    }
    lld** A11 = new lld*[newSize]; lld** A12 = new lld*[newSize];
    lld** A21 = new lld*[newSize]; lld** A22 = new lld*[newSize];
    lld** B11 = new lld*[newSize]; lld** B12 = new lld*[newSize];
    lld** B21 = new lld*[newSize]; lld** B22 = new lld*[newSize];

    for (int i = 0; i < newSize; i++) {
        A11[i] = new lld[newSize]; A12[i] = new lld[newSize];
        A21[i] = new lld[newSize]; A22[i] = new lld[newSize];
        B11[i] = new lld[newSize]; B12[i] = new lld[newSize];
        B21[i] = new lld[newSize]; B22[i] = new lld[newSize];

        for (int j = 0; j < newSize; j++) {
            A11[i][j] = a[i][j];
            A12[i][j] = a[i][j + newSize];
            A21[i][j] = a[i + newSize][j];
            A22[i][j] = a[i + newSize][j + newSize];

            B11[i][j] = b[i][j];
            B12[i][j] = b[i][j + newSize];
            B21[i][j] = b[i + newSize][j];
            B22[i][j] = b[i + newSize][j + newSize];
        }
    }
    lld** M1 = new lld*[newSize]; lld** M2 = new lld*[newSize];
    lld** M3 = new lld*[newSize]; lld** M4 = new lld*[newSize];
    lld** M5 = new lld*[newSize]; lld** M6 = new lld*[newSize];
    lld** M7 = new lld*[newSize];
    for (int i = 0; i < newSize; i++) {
        M1[i] = new lld[newSize]; M2[i] = new lld[newSize];
        M3[i] = new lld[newSize]; M4[i] = new lld[newSize];
        M5[i] = new lld[newSize]; M6[i] = new lld[newSize];
        M7[i] = new lld[newSize];
    }
    lld** temp1 = new lld*[newSize];
    lld** temp2 = new lld*[newSize];
    for (int i = 0; i < newSize; i++) {
        temp1[i] = new lld[newSize];
        temp2[i] = new lld[newSize];
    }
    add(A11, A22, temp1, newSize);
    add(B11, B22, temp2, newSize);
    M1 = Strassen(temp1, temp2, newSize);
    add(A21, A22, temp1, newSize);
    M2 = Strassen(temp1, B11, newSize);
    subtract(B12, B22, temp2, newSize);
    M3 = Strassen(A11, temp2, newSize);
    subtract(B21, B11, temp2, newSize);
    M4 = Strassen(A22, temp2, newSize);
    add(A11, A12, temp1, newSize);
    M5 = Strassen(temp1, B22, newSize);
    subtract(A21, A11, temp1, newSize);
    add(B11, B12, temp2, newSize);
    M6 = Strassen(temp1, temp2, newSize);
    subtract(A12, A22, temp1, newSize);
    add(B21, B22, temp2, newSize);
    M7 = Strassen(temp1, temp2, newSize);
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            result[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            result[i][j + newSize] = M3[i][j] + M5[i][j];
            result[i + newSize][j] = M2[i][j] + M4[i][j];
            result[i + newSize][j + newSize] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }
    for (int i = 0; i < newSize; ++i) {
        delete[] A11[i]; delete[] A12[i]; delete[] A21[i]; delete[] A22[i];
        delete[] B11[i]; delete[] B12[i]; delete[] B21[i]; delete[] B22[i];
        delete[] M1[i]; delete[] M2[i]; delete[] M3[i]; delete[] M4[i];
        delete[] M5[i]; delete[] M6[i]; delete[] M7[i];
        delete[] temp1[i]; delete[] temp2[i];
    }
    delete[] A11; delete[] A12; delete[] A21; delete[] A22;
    delete[] B11; delete[] B12; delete[] B21; delete[] B22;
    delete[] M1; delete[] M2; delete[] M3; delete[] M4;
    delete[] M5; delete[] M6; delete[] M7;
    delete[] temp1; delete[] temp2;

    return result;
}

/*
***** Función: main
*** Parámetros:
* void
*** Return:
* int
*** Descripción:
* La función principal se encarga de:
* 1. Leer las matrices desde un archivo llamado "dataset.txt".
* 2. Ejecutar la multiplicación de matrices utilizando el algoritmo de Strassen.
* 3. Medir el tiempo de ejecución de la multiplicación de matrices.
* 4. Imprimir el tiempo de ejecución en milisegundos en la consola.
* 5. Liberar la memoria de las matrices y el resultado.
*****
*/
int main() {
    ifstream file("dataset.txt");
    if (!file.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }
    int f1, c1, f2, c2;
    file >> f1 >> c1;
    lld** mat1 = new lld*[f1];
    for(int i = 0; i < f1; i++) {
        mat1[i] = new lld[c1];
        for(int j = 0; j < c1; j++) {
            file >> mat1[i][j];
        }
    }
    file >> f2 >> c2;
    lld** mat2 = new lld*[f2];
    for(int i = 0; i < f2; i++) {
        mat2[i] = new lld[c2];
        for(int j = 0; j < c2; j++) {
            file >> mat2[i][j];
        }
    }
    file.close();
    auto t1 = high_resolution_clock::now();
    lld** result = Strassen(mat1, mat2, f1);
    auto t2 = high_resolution_clock::now();
    duration<double, milli> ms_double = t2 - t1;
    cout << ms_double.count() << " ms\n";
    for(int i = 0; i < f1; i++) delete[] mat1[i];
    delete[] mat1;
    for(int i = 0; i < f2; i++) delete[] mat2[i];
    delete[] mat2;
    for(int i = 0; i < f1; i++) delete[] result[i];
    delete[] result;
    return 0;
}
