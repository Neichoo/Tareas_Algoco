//Código Extraído de https://youtu.be/PEhwXHEPbmI?si=p4eXEDdfXYZGET3_ (Insertion Sort | C++ Example)
//Modificado levemente, para hacer que la entrada sea un arreglo desde un .txt
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;


/*
***** Funcion: insertion_sort
*** Parámetros:
* int arreglo[]: Arreglo de enteros que se quiere ordenar.
* int largo_arreglo: Tamaño del arreglo que se va a ordenar.
*** Return:
* No retorna nada debido a que es de tipo void.
*** Descripción:
* La función realiza el ordenamiento del arreglo utilizando el algoritmo de ordenamiento por inserción. 
* Comienza en el segundo elemento del arreglo y lo compara con los elementos anteriores, si el elemento actual
* es menor que el anterior, desplaza el anterior hacia la derecha para hacer espacio y lo inserta en la posición
* correcta. Esto se repite hasta que no hayan más elementos por comparar.
*****
*/
void insertion_sort(int arreglo[], int largo_arreglo){
    for (int i = 1; i < largo_arreglo; i++){
        int key = arreglo[i];
        int j = i - 1;
        while((j >= 0) && (arreglo[j] > key)){
            arreglo[j + 1] = arreglo[j];
            j = j - 1;
        }
        arreglo[j + 1] = key;
    }
}

/*
***** Funcion: main
*** Parametros:
* Los necesarios para la entrada de información por consola.
*** Return:
* 0 Si el programa se ejecuta con éxito.
*** Descripcion:
* La función principal del programa, lee un archivo txt llamado 'dataset.txt', en el cual, la primera
* línea contiene el tamaño del arreglo y la segunda línea contiene los elementos del arreglo separados
* por un espacio. Posteriormente, se asigna la primera línea a la variable 'largo_arreglo' y se crea un
* puntero a un arreglo de enteros de tamaño 'largo_arreglo'. Luego, se leen los elementos del arreglo y
* se almacenan en el arreglo. Se llama a la función 'insertion_sort' para ordenar el arreglo y finalmente
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
    auto s1 = high_resolution_clock::now();
    insertion_sort(arreglo, largo_arreglo);
    auto e1 = high_resolution_clock::now();
    auto d1 = duration_cast<duration<double, milli>>(e1 - s1);
    cout << fixed << setprecision(4);
    double tiempo_ms = d1.count();
    cout << "Tiempo de ejecución: " << tiempo_ms << " ms" << endl;
    delete[] arreglo;
    return 0;
}

