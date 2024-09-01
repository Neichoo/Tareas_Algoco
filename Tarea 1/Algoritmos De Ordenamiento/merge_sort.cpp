//Código Extraído de https://youtu.be/LeWuki7AQLo?si=11tiNyxOU6ECOTUZ (Merge Sort | C Programming Example)
//Modificado para hacer que la entrada de archivos, medición de tiempo y traducción a C++.
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

/*
***** Funcion: merge_sorted_arrays
*** Parámetros:
* int arreglo[]: Arreglo de enteros que se quiere ordenar.
* int indice_inicio: Índice del primer elemento en el subarreglo.
* int indice_medio: Índice del elemento medio del subarreglo.
* int indice_final: Índice del último elemento en el subarreglo.
*** Return:
* No retorna nada debido a que es de tipo void.
*** Descripción:
* La función combina dos subarreglos ordenados en un solo arreglo ordenado. 
* Crea dos arreglos temporales para almacenar los subarreglos izquierdo y derecho, 
* los copia desde el arreglo principal, y luego fusiona estos subarreglos en el 
* arreglo principal en orden. Finalmente, libera la memoria de los arreglos temporales.
*****
*/
void merge_sorted_arrays(int arreglo[], int indice_inicio, int indice_medio, int indice_final) {
    int left_length = indice_medio - indice_inicio + 1;
    int right_length = indice_final - indice_medio;
    int* temp_left = new int[left_length];
    int* temp_right = new int[right_length];
    for (int i = 0; i < left_length; i++)
        temp_left[i] = arreglo[indice_inicio + i];
    for (int i = 0; i < right_length; i++)
        temp_right[i] = arreglo[indice_medio + 1 + i];
    int i = 0, j = 0, k = indice_inicio;
    while (i < left_length && j < right_length) {
        if (temp_left[i] <= temp_right[j]) {
            arreglo[k++] = temp_left[i++];
        } else {
            arreglo[k++] = temp_right[j++];
        }
    }
    while (i < left_length) {
        arreglo[k++] = temp_left[i++];
    }
    while (j < right_length) {
        arreglo[k++] = temp_right[j++];
    }
    delete[] temp_left;
    delete[] temp_right;
}

/*
***** Funcion: merge_sort_recursion
*** Parámetros:
* int arreglo[]: Arreglo de enteros que se quiere ordenar.
* int indice_inicio: Índice del primer elemento del subarreglo.
* int indice_final: Índice del último elemento del subarreglo.
*** Return:
* No retorna nada debido a que es de tipo void.
*** Descripción:
* La función realiza el ordenamiento del arreglo utilizando el algoritmo de ordenamiento por mezcla.
* Divide el arreglo en dos mitades, ordena recursivamente cada mitad y luego combina las dos mitades ordenadas 
* utilizando la función 'merge_sorted_arrays'. 
*****
*/
void merge_sort_recursion(int arreglo[], int indice_inicio, int indice_final) {
    if (indice_inicio < indice_final) {
        int m = indice_inicio + (indice_final - indice_inicio) / 2;
        merge_sort_recursion(arreglo, indice_inicio, m);
        merge_sort_recursion(arreglo, (m + 1), indice_final);
        merge_sorted_arrays(arreglo, indice_inicio, m, indice_final);
    }
}

/*
***** Funcion: merge_sort
*** Parámetros:
* int arreglo[]: Arreglo de enteros que se quiere ordenar.
* int largo_arreglo: Tamaño del arreglo que se va a ordenar.
*** Return:
* No retorna nada debido a que es de tipo void.
*** Descripción:
* La función principal para realizar el ordenamiento por mezcla. 
* Llama a la función 'merge_sort_recursion' con los índices de inicio y final del arreglo.
*****
*/
void merge_sort(int arreglo[], int largo_arreglo) {
    merge_sort_recursion(arreglo, 0, (largo_arreglo - 1));
}

/*
***** Funcion: main
*** Parámetros:
* Los necesarios para la entrada de información por consola.
*** Return:
* 0 Si el programa se ejecuta con éxito.
*** Descripción:
* La función principal del programa, lee un archivo txt llamado 'dataset.txt', en el cual, la primera
* línea contiene el tamaño del arreglo y la segunda línea contiene los elementos del arreglo separados
* por un espacio. Posteriormente, se asigna la primera línea a la variable 'largo_arreglo' y se crea un
* puntero a un arreglo de enteros de tamaño 'largo_arreglo'. Luego, se leen los elementos del arreglo y
* se almacenan en el arreglo. Se llama a la función 'merge_sort' para ordenar el arreglo y finalmente
* se imprime el tiempo de ejecución de la función.
*****
*/

int main() {
    int largo_arreglo;
    ifstream archivo("dataset.txt");
    if (!archivo) {
        cerr << "No se pudo abrir el archivo" << endl;
        return 1;
    }
    archivo >> largo_arreglo;
    int* arreglo = new int[largo_arreglo];
    for (int i = 0; i < largo_arreglo; ++i) {
        archivo >> arreglo[i];
    }
    archivo.close();
    auto s1 = high_resolution_clock::now();
    merge_sort(arreglo, largo_arreglo);
    auto e1 = high_resolution_clock::now();
    auto d1 = duration_cast<duration<double, milli>>(e1 - s1);
    cout << fixed << setprecision(4);
    double tiempo_ms = d1.count();
    cout << "Tiempo de ejecución: " << tiempo_ms << " ms" << endl;
    delete[] arreglo;
    return 0;
}