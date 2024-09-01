#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <algorithm>
using namespace std;
using namespace chrono;

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
* se almacenan en el arreglo. Se llama a la función 'std::sort' para ordenar el arreglo y finalmente
* se imprime el tiempo de ejecución de la función.
*****
*/
int main(int argc, char *argv[]){
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
    sort(arreglo, arreglo + largo_arreglo);
    auto t2 = high_resolution_clock::now();
    duration<double, milli> ms_double = t2 - t1;
    cout << ms_double.count() << " ms\n";
    delete[] arreglo;
    return 0;
}