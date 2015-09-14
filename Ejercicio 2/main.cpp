#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <sstream>
#include <fstream>
using namespace std;

vector<int> medianas(vector<int> a){
    if (a.size() == 0){
        vector<int> resultado;
        return resultado;
    }
    vector<int> res(a.size(),0);
    res[0] = a[0];
    multiset<int> masGrandes;
    multiset<int> masChicos;
    int minimo;
    int maximo;
    masGrandes.insert(a[0]);
    for (int i = 1; i < a.size(); i++){
        if (a[i] >= res[i-1]){
            masGrandes.insert(a[i]);
        } else {
            masChicos.insert(a[i]);
        }
        if (masGrandes.size() - masChicos.size() == 2){
            minimo = *masGrandes.begin();
            masChicos.insert(minimo);
            masGrandes.erase(masGrandes.find(minimo)); // Aclaracion: utilizamos la funcion find de multiset para encontrar el iterador que contiene al maximo o minimo y asi poder borrarlo, ya que la funcion erase al pasarle como parametro un numero, borra todas sus repeticiones. La complejidad de find es O(log n) con lo cual no modifica la complejidad de nuestro algoritmo
        } else if (masGrandes.size() - masChicos.size() == -2){
            maximo = *masChicos.rbegin();
            masGrandes.insert(maximo);
            masChicos.erase(masChicos.find(maximo));  
        }
        if (masGrandes.size() == masChicos.size()){
            minimo = *masGrandes.begin();
            maximo = *masChicos.rbegin();
            res[i] = (maximo+minimo)/2;
        } else if (masGrandes.size() - masChicos.size() == 1){
            minimo = *masGrandes.begin();
            res[i] = minimo;
        } else if (masGrandes.size() - masChicos.size() == -1){
            maximo = *masChicos.rbegin();            
            res[i] = maximo;
        }
    }
    return res;
}
int main() {
    
    ofstream out;
    out.open("resultado.out");
    ifstream in("ejMejorCaso.in");

    int iteraciones = 0;
    double tiempo_promedio = 0;

    while (in.good()){
        vector<int> vec;
        string st;
        getline(in, st);
        istringstream iss;
        iss.str(st);
        iss.clear();
        int a;
        while(iss>>a){
            vec.push_back(a);
        }        

        while (iteraciones <= 100) {
            clock_t startTime = clock();  //empezamos a medir el tiempo
            vector<int> res = medianas(vec);
            tiempo_promedio += ((double)clock() - startTime) / (CLOCKS_PER_SEC / 1000); //primero sumo los tiempos de las 100 iteraciones.
            if(iteraciones == 0){
                for(int i = 0; i<res.size(); i++){
                    out << res[i] << " ";
                }
                out << endl;
            }
            iteraciones++;
        }
        tiempo_promedio = tiempo_promedio/100.0; //calculo el promedio del tiempo de las 100 iteraciones.
        printf("%f \n", tiempo_promedio);  //se descomenta para saber los tiempos promedios para el gráfico.

        tiempo_promedio = 0.0;
        iteraciones = 0;

    }
    out.close();
    

    
    return 0;
}
