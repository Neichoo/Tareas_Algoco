//Código Extraído de https://www.geeksforgeeks.org/c-program-multiply-two-matrices/ (Program to multiply two matrices) (Strassen’s Matrix Multiplication Algorithm | Implementation)
//Modificado levemente para la entrada de archivos .txt
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

/*
***** Funcion: mulMat
*** Parámetros:
* const vector<vector<long long>>& mat1: Primera matriz a multiplicar.
* const vector<vector<long long>>& mat2: Segunda matriz a multiplicar.
* int R1: Número de filas de la primera matriz.
* int C1: Número de columnas de la primera matriz (y número de filas de la segunda matriz).
* int R2: Número de filas de la segunda matriz.
* int C2: Número de columnas de la segunda matriz.
*** Return:
* No retorna nada debido a que es de tipo void.
*** Descripción:
* La función realiza la multiplicación de dos matrices de tamaño (R1 x C1) y (R2 x C2) 
* y almacena el resultado en la matriz 'rslt'. Utiliza tres bucles anidados para 
* realizar la multiplicación y suma de los productos correspondientes.
*****
*/
void mulMat(const vector<vector<long long>>& mat1, const vector<vector<long long>>& mat2, int R1, int C1, int R2, int C2) {
    vector<vector<long long>> rslt(R1, vector<long long>(C2, 0));
    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C2; j++) {
            for (int k = 0; k < C1; k++) {
                rslt[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

/*
***** Funcion: main
*** Parámetros:
* Los necesarios para la entrada de información por consola.
*** Return:
* 0 Si el programa se ejecuta con éxito.
*** Descripción:
* La función principal del programa, lee un archivo txt llamado 'dataset.txt', en el cual,
* la primera línea contiene las dimensiones de la primera matriz (número de filas y columnas).
* La segunda línea contiene los elementos de la primera matriz. Luego, la tercera línea contiene 
* las dimensiones de la segunda matriz y la cuarta línea los elementos de la segunda matriz.
* Después, se llama a la función 'mulMat' para multiplicar las matrices y finalmente se imprime
* el tiempo de ejecución de la función.
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
    vector<vector<long long>> mat1(f1, vector<long long>(c1));
    for(int i = 0; i < f1; i++) {
        for(int j = 0; j < c1; j++) {
            file >> mat1[i][j];
        }
    }
    file >> f2 >> c2;
    vector<vector<long long>> mat2(f2, vector<long long>(c2));
    for(int i = 0; i < f2; i++) {
        for(int j = 0; j < c2; j++) {
            file >> mat2[i][j];
        }
    }
    file.close();

    auto t1 = high_resolution_clock::now();
    mulMat(mat1, mat2, f1, c1, f2, c2);
    auto t2 = high_resolution_clock::now();
    duration<double, milli> ms_double = t2 - t1;
    cout << ms_double.count() << " ms\n";
    return 0;
}
