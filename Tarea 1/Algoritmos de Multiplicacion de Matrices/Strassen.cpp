//Código Extraído de https://www.geeksforgeeks.org/strassens-matrix-multiplication-algorithm-implementation/
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
typedef long long lld;

/*
***** Funcion: MatrixMultiply
*** Parámetros:
* lld** a: Primera matriz a multiplicar.
* lld** b: Segunda matriz a multiplicar.
* int n: Número de filas de la primera matriz.
* int l: Número de columnas de la primera matriz (y número de filas de la segunda matriz).
* int m: Número de columnas de la segunda matriz.
*** Return:
* lld**: Matriz resultado de la multiplicación de matrices.
*** Descripción:
* Realiza la multiplicación de matrices tradicional. Crea una matriz resultado 'c' de tamaño n x m
* y la llena con el producto de las matrices 'a' y 'b'.
*****
*/
inline lld** MatrixMultiply(lld** a, lld** b, int n, int l, int m) {
    lld** c = new lld*[n];
    for (int i = 0; i < n; i++)
        c[i] = new lld[m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i][j] = 0;
            for (int k = 0; k < l; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

/*
***** Función: Strassen
*** Parámetros:
* a: Puntero a la primera matriz de dimensiones n x l.
* b: Puntero a la segunda matriz de dimensiones l x m.
* n: Número de filas de la primera matriz.
* l: Número de columnas de la primera matriz (y filas de la segunda matriz).
* m: Número de columnas de la segunda matriz.
*** Return:
* Un puntero a la matriz resultante de la multiplicación de a y b, de dimensiones n x m.
*** Descripción:
* La función implementa el algoritmo de multiplicación de matrices de Strassen, que es una técnica de
* divide y vencerás que reduce el número de multiplicaciones necesarias en comparación con la multiplicación
* de matrices estándar.
* 1. Si alguna de las dimensiones es 1, realiza la multiplicación de matrices estándar.
* 2. Crea matrices submatrices para dividir las matrices originales en cuatro partes cada una.
* 3. Calcula 10 matrices auxiliares (s) utilizando combinaciones de las submatrices de entrada.
* 4. Calcula 7 productos de Strassen (p) utilizando estas matrices auxiliares.
* 5. Combina los productos parciales para formar la matriz resultado.
* 6. Libera toda la memoria utilizada para las submatrices y matrices auxiliares.
* 7. Retorna la matriz resultante de la multiplicación.
*****
*/
inline lld** Strassen(lld** a, lld** b, int n, int l, int m) {
    if (n == 1 || l == 1 || m == 1)
        return MatrixMultiply(a, b, n, l, m);
    lld** c = new lld*[n];
    for (int i = 0; i < n; i++)
        c[i] = new lld[m];
    int adjN = (n >> 1) + (n & 1);
    int adjL = (l >> 1) + (l & 1);
    int adjM = (m >> 1) + (m & 1);
    lld**** As = new lld***[2];
    lld**** Bs = new lld***[2];
    for (int x = 0; x < 2; x++) {
        As[x] = new lld**[2];
        Bs[x] = new lld**[2];
        for (int y = 0; y < 2; y++) {
            As[x][y] = new lld*[adjN];
            Bs[x][y] = new lld*[adjL];
            for (int i = 0; i < adjN; i++) {
                As[x][y][i] = new lld[adjL];
                for (int j = 0; j < adjL; j++) {
                    int I = i + (x & 1) * adjN;
                    int J = j + (y & 1) * adjL;
                    As[x][y][i][j] = (I < n && J < l) ? a[I][J] : 0;
                }
            }
            for (int i = 0; i < adjL; i++) {
                Bs[x][y][i] = new lld[adjM];
                for (int j = 0; j < adjM; j++) {
                    int I = i + (x & 1) * adjL;
                    int J = j + (y & 1) * adjM;
                    Bs[x][y][i][j] = (I < l && J < m) ? b[I][J] : 0;
                }
            }
        }
    }
    lld*** s = new lld**[10];
    for (int i = 0; i < 10; i++) {
        switch (i) {
            case 0:
                s[i] = new lld*[adjL];
                for (int j = 0; j < adjL; j++) {
                    s[i][j] = new lld[adjM];
                    for (int k = 0; k < adjM; k++) {
                        s[i][j][k] = Bs[0][1][j][k] - Bs[1][1][j][k];
                    }
                }
                break;
            case 1:
                s[i] = new lld*[adjN];
                for (int j = 0; j < adjN; j++) {
                    s[i][j] = new lld[adjL];
                    for (int k = 0; k < adjL; k++) {
                        s[i][j][k] = As[0][0][j][k] + As[0][1][j][k];
                    }
                }
                break;
            case 2:
                s[i] = new lld*[adjN];
                for (int j = 0; j < adjN; j++) {
                    s[i][j] = new lld[adjL];
                    for (int k = 0; k < adjL; k++) {
                        s[i][j][k] = As[1][0][j][k] + As[1][1][j][k];
                    }
                }
                break;
            case 3:
                s[i] = new lld*[adjL];
                for (int j = 0; j < adjL; j++) {
                    s[i][j] = new lld[adjM];
                    for (int k = 0; k < adjM; k++) {
                        s[i][j][k] = Bs[1][0][j][k] - Bs[0][0][j][k];
                    }
                }
                break;
            case 4:
                s[i] = new lld*[adjN];
                for (int j = 0; j < adjN; j++) {
                    s[i][j] = new lld[adjL];
                    for (int k = 0; k < adjL; k++) {
                        s[i][j][k] = As[0][0][j][k] + As[1][1][j][k];
                    }
                }
                break;
            case 5:
                s[i] = new lld*[adjL];
                for (int j = 0; j < adjL; j++) {
                    s[i][j] = new lld[adjM];
                    for (int k = 0; k < adjM; k++) {
                        s[i][j][k] = Bs[0][0][j][k] + Bs[1][1][j][k];
                    }
                }
                break;
            case 6:
                s[i] = new lld*[adjN];
                for (int j = 0; j < adjN; j++) {
                    s[i][j] = new lld[adjL];
                    for (int k = 0; k < adjL; k++) {
                        s[i][j][k] = As[0][1][j][k] - As[1][1][j][k];
                    }
                }
                break;
            case 7:
                s[i] = new lld*[adjL];
                for (int j = 0; j < adjL; j++) {
                    s[i][j] = new lld[adjM];
                    for (int k = 0; k < adjM; k++) {
                        s[i][j][k] = Bs[1][0][j][k] + Bs[1][1][j][k];
                    }
                }
                break;
            case 8:
                s[i] = new lld*[adjN];
                for (int j = 0; j < adjN; j++) {
                    s[i][j] = new lld[adjL];
                    for (int k = 0; k < adjL; k++) {
                        s[i][j][k] = As[0][0][j][k] - As[1][0][j][k];
                    }
                }
                break;
            case 9:
                s[i] = new lld*[adjL];
                for (int j = 0; j < adjL; j++) {
                    s[i][j] = new lld[adjM];
                    for (int k = 0; k < adjM; k++) {
                        s[i][j][k] = Bs[0][0][j][k] + Bs[0][1][j][k];
                    }
                }
                break;
        }
    }
    lld*** p = new lld**[7];
    p[0] = Strassen(As[0][0], s[0], adjN, adjL, adjM);
    p[1] = Strassen(s[1], Bs[1][1], adjN, adjL, adjM);
    p[2] = Strassen(s[2], Bs[0][0], adjN, adjL, adjM);
    p[3] = Strassen(As[1][1], s[3], adjN, adjL, adjM);
    p[4] = Strassen(s[4], s[5], adjN, adjL, adjM);
    p[5] = Strassen(s[6], s[7], adjN, adjL, adjM);
    p[6] = Strassen(s[8], s[9], adjN, adjL, adjM);
    for (int i = 0; i < adjN; i++) {
        for (int j = 0; j < adjM; j++) {
            c[i][j] = p[4][i][j] + p[3][i][j] - p[1][i][j] + p[5][i][j];
            if (j + adjM < m)
                c[i][j + adjM] = p[0][i][j] + p[1][i][j];
            if (i + adjN < n)
                c[i + adjN][j] = p[2][i][j] + p[3][i][j];
            if (i + adjN < n && j + adjM < m)
                c[i + adjN][j + adjM] = p[4][i][j] + p[0][i][j] - p[2][i][j] - p[6][i][j];
        }
    }
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            for (int i = 0; i < adjN; i++) {
                delete[] As[x][y][i];
            }
            delete[] As[x][y];
        }
        delete[] As[x];
    }
    delete[] As;
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            for (int i = 0; i < adjL; i++) {
                delete[] Bs[x][y][i];
            }
            delete[] Bs[x][y];
        }
        delete[] Bs[x];
    }
    delete[] Bs;
    for (int i = 0; i < 10; i++) {
        switch (i) {
        case 0:
        case 3:
        case 5:
        case 7:
        case 9:
            for (int j = 0; j < adjL; j++) {
                delete[] s[i][j];
            }
            break;
        case 1:
        case 2:
        case 4:
        case 6:
        case 8:
            for (int j = 0; j < adjN; j++) {
                delete[] s[i][j];
            }
            break;
        }
        delete[] s[i];
    }
    delete[] s;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < (n >> 1); j++) {
            delete[] p[i][j];
        }
        delete[] p[i];
    }
    delete[] p;
    return c;
}

/*
***** Funcion: main
*** Parámetros:
* Los necesarios para la entrada de información por consola.
*** Return:
* 0 Si el programa se ejecuta con éxito.
*** Descripción:
* La función principal del programa, lee un archivo llamado 'dataset.txt' que contiene las matrices a multiplicar.
* La primera línea del archivo define las dimensiones de la primera matriz, y la siguiente sección del archivo
* contiene los elementos de la primera matriz. La sección siguiente define las dimensiones de la segunda matriz,
* y luego los elementos de la segunda matriz. Después, se llama a la función 'Strassen' para realizar la multiplicación
* de matrices utilizando el algoritmo de Strassen. Finalmente, se imprime el resultado de la multiplicación y el tiempo
* de ejecución.
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
    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::duration;
    using chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    lld** result = Strassen(mat1, mat2, f1, c1, c2);
    auto t2 = high_resolution_clock::now();
    duration<double, milli> ms_double = t2 - t1;

    cout << "Strassen multiplication result:\n";
    for(int i = 0; i < f1; i++) {
        for(int j = 0; j < c2; j++) {
            cout << result[i][j] << "\t";
        }
        cout << endl;
    }
    cout << ms_double.count() << " ms\n";
    for(int i = 0; i < f1; i++) delete[] mat1[i];
    delete[] mat1;
    for(int i = 0; i < f2; i++) delete[] mat2[i];
    delete[] mat2;
    for(int i = 0; i < f1; i++) delete[] result[i];
    delete[] result;
    return 0;
}
