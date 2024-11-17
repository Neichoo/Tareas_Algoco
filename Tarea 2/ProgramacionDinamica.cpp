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
*Parámetros: string nombre, el cual es el nombre del archivo a leer.
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
*Descripción: Función que implementa el algoritmo de programación dinámica para calcular la distancia mínima de edición entre
dos cadenas S1 y S2, considerando operaciones de inserción, eliminación, sustitución y transposición con costos variables.
Utiliza una matriz de programación dinámica (dp) para almacenar los resultados parciales, evitando la recalculación de subproblemas.
El valor final de la distancia mínima de edición se encuentra en dp[m][n], donde m y n son los tamaños de las cadenas S1 y S2, respectivamente.
*Parámetros: No recibe parámetros. Utiliza las cadenas globales S1 y S2, y los vectores de costos globales para las operaciones.
*Return: Devuelve un entero que representa la distancia mínima de edición entre las cadenas S1 y S2.
*/
int programaciondinamica() {
    int m = S1.size();
    int n = S2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        dp[i][0] = dp[i - 1][0] + cost_delete[S1[i - 1] - 'a'];
    }
    for (int j = 1; j <= n; ++j) {
        dp[0][j] = dp[0][j - 1] + cost_insert[S2[j - 1] - 'a'];
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (S1[i - 1] == S2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                int coste_sustitucion = cost_replace[S1[i - 1] - 'a'][S2[j - 1] - 'a'] + dp[i - 1][j - 1];
                int coste_insercion = cost_insert[S2[j - 1] - 'a'] + dp[i][j - 1];
                int coste_eliminacion = cost_delete[S1[i - 1] - 'a'] + dp[i - 1][j];
                dp[i][j] = min({coste_sustitucion, coste_insercion, coste_eliminacion});

                if (i > 1 && j > 1 && S1[i - 1] == S2[j - 2] && S1[i - 2] == S2[j - 1]) {
                    int coste_transposicion = cost_transpose[S1[i - 2] - 'a'][S1[i - 1] - 'a'] + dp[i - 2][j - 2];
                    dp[i][j] = min(dp[i][j], coste_transposicion);
                }
            }
        }
    }
    return dp[m][n];
}

/*
*Descripción: Función main que llama a las funciones necesarias para realizar la programación dinámica.
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
    cout << "Distancia mínima de edición (Programación Dinámica): " << programaciondinamica() << endl;
    auto t2 = high_resolution_clock::now();
    duration<double, milli> ms_double = t2 - t1;
    cout << "Tiempo de ejecución del algoritmo (Programación Dinámica): " << ms_double.count() << " ms\n";
    return 0;
}
