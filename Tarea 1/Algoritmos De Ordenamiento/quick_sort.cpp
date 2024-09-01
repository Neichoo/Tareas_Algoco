//Código extraído de https://www.geeksforgeeks.org/quick-sort-algorithm/ (Quick Sort Algorithm)
//Modificado ligeramente para la entrada de archivos y cálculo de tiempo.
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

/*
***** Funcion: partition
*** Parámetros:
* int arr[]: Arreglo de enteros que se quiere particionar.
* int low: Índice del primer elemento del subarreglo.
* int high: Índice del último elemento del subarreglo.
*** Return:
* int: Retorna el índice del pivote después de la partición.
*** Descripción:
* La función selecciona un pivote (último elemento del subarreglo) y organiza los elementos
* de tal manera que todos los elementos menores que el pivote queden a la izquierda de él
* y todos los mayores queden a la derecha. Luego, devuelve el índice donde se encuentra el pivote.
*****
*/
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);  
    return i + 1;
}

/*
***** Funcion: quickSort
*** Parámetros:
* int arr[]: Arreglo de enteros que se quiere ordenar.
* int low: Índice del primer elemento del subarreglo.
* int high: Índice del último elemento del subarreglo.
*** Return:
* No retorna nada debido a que es de tipo void.
*** Descripción:
* La función implementa el algoritmo de ordenamiento QuickSort. 
* Divide el arreglo utilizando la función 'partition', luego ordena
* recursivamente las dos mitades del arreglo.
*****
*/
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
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
* se almacenan en el arreglo. Se llama a la función 'quickSort' para ordenar el arreglo y finalmente
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
    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::duration;
    using chrono::milliseconds;
    auto t1 = high_resolution_clock::now();
    quickSort(arreglo, 0, largo_arreglo - 1);
    auto t2 = high_resolution_clock::now();
    duration<double, milli> ms_double = t2 - t1;
    cout << ms_double.count() << " ms\n";
    delete[] arreglo;
    return 0;
}
