#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace chrono;

//Variables Globales a utilizar
vector<int> cost_insert(26);
vector<int> cost_delete(26);
vector<vector<int>> cost_replace(26, vector<int>(26));
vector<vector<int>> cost_transpose(26, vector<int>(26));
string S1, S2;

/*
*Descripción: Función que lee los costos desde los archivos de texto, luego los guarda en una estructura
de datos, dependiendo de que archivo se trate.
*Parámetros:
*   - nombre: Nombre del archivo a leer.
*Return: Nada, debido a que es de tipo void.
*/
void leer_costos(const string& nombre){
    ifstream archivo(nombre);
    if(!archivo){
        cout << "Error al abrir el archivo" << endl;
        return;
    }
    if(nombre == "cost_replace.txt"){
        for(int i = 0; i < 26; i++){
            for(int j = 0; j < 26; j++){
                archivo >> cost_replace[i][j];
            }
        }
    } else if(nombre == "cost_transpose.txt"){
        for(int i = 0; i < 26; i++){
            for(int j = 0; j < 26; j++){
                archivo >> cost_transpose[i][j];
            }
        }
    } else if(nombre == "cost_insert.txt"){
        for(int i = 0; i < 26; i++){
            archivo >> cost_insert[i];
        }
    } else if(nombre == "cost_delete.txt"){
        for(int i = 0; i < 26; i++){
            archivo >> cost_delete[i];
        }
    } else{
        cout << "Nombre de archivo incorrecto" << endl;
    }
    archivo.close();
}

/*
*Descripción: Función que lee los strings S1 y S2 desde los archivos de texto, luego los guarda en su respectivo string S1 y S2.
*Parámetros: No tiene parámetros la función.
*Return: Nada, debido a que es de tipo void.
*/
void leer_s() {
    ifstream archivo("s1.txt");
    if (!archivo) {
        cout << "Error al abrir el archivo s1.txt" << endl;
        return;
    }
    archivo >> S1;
    archivo.close();
    archivo.open("s2.txt");
    if (!archivo) {
        cout << "Error al abrir el archivo s2.txt" << endl;
        return;
    }
    archivo >> S2;
    archivo.close();
}

/*
*Descripción: Función que implementa el algoritmo de fuerza bruta para calcular la distancia mínima de edición entre dos cadenas
S1 y S2, considerando operaciones de inserción, eliminación, sustitución y transposición con costos variables. La función trabaja
de manera recursiva, explorando todas las combinaciones posibles de operaciones a realizar para transformar la cadena S1 en la cadena S2.
La recursión se detiene cuando se alcanza el final de una de las cadenas, y se calculan los costos de las operaciones restantes (inserciones o eliminaciones).
*Parámetros: 
*   - idx1: Índice actual en la cadena S1.
*   - idx2: Índice actual en la cadena S2.
*Return: Devuelve un entero que representa el costo mínimo de las operaciones necesarias para transformar la cadena S1 en la cadena S2.
*/

int fuerzabruta(int idx1, int idx2) {
    if (idx1 == S1.size()) {
        int coste_insercion = 0;
        for (int i = idx2; i < S2.size(); i++) {
            coste_insercion += cost_insert[S2[i] - 'a'];
        }
        return coste_insercion;
    }
    if (idx2 == S2.size()) {
        int coste_eliminacion = 0;
        for (int i = idx1; i < S1.size(); i++) {
            coste_eliminacion += cost_delete[S1[i] - 'a'];
        }
        return coste_eliminacion;
    }
    int coste_sustitucion = cost_replace[S1[idx1] - 'a'][S2[idx2] - 'a'] + fuerzabruta(idx1 + 1, idx2 + 1);
    int coste_insercion = cost_insert[S2[idx2] - 'a'] + fuerzabruta(idx1, idx2 + 1);
    int coste_eliminacion = cost_delete[S1[idx1] - 'a'] + fuerzabruta(idx1 + 1, idx2);
    int coste_total = min({coste_sustitucion, coste_insercion, coste_eliminacion});
    if (idx1 + 1 < S1.size() && idx2 + 1 < S2.size() && S1[idx1] == S2[idx2 + 1] && S1[idx1 + 1] == S2[idx2]) {
        int coste_transposicion = cost_transpose[S1[idx1] - 'a'][S1[idx1 + 1] - 'a'] + fuerzabruta(idx1 + 2, idx2 + 2);
        coste_total = min(coste_total, coste_transposicion);
    }
    return coste_total;
}

/*
*Descripción: Función main que llama a las funciones necesarias para realizar la fuerza bruta.
*Parámetros: No tiene parámetros la función.
*Return: 0 en caso de éxito.
*/
int main(){
    leer_costos("cost_insert.txt");
    leer_costos("cost_delete.txt");
    leer_costos("cost_replace.txt");
    leer_costos("cost_transpose.txt");
    leer_s();
    auto t1 = high_resolution_clock::now();
    cout << "Distancia mínima de edición (Fuerza Bruta): " << fuerzabruta(0, 0) << endl;
    auto t2 = high_resolution_clock::now();
    duration<double, milli> ms_double = t2 - t1;
    cout << "Tiempo de ejecución del algoritmo (Fuerza Bruta): " << ms_double.count() << " ms\n";
    return 0;
}