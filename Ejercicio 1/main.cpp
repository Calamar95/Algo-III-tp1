#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <time.h>

using namespace std;

int conectar(vector<int> v , int longCable) {

	int resTemp = 1;
	int start = 0;
	int actual = 0;
	int aux = 0;

	while (longCable > 0 && v[actual] != v.back()) {
		aux = longCable;
		longCable = longCable -(v[actual+1] - v[actual]); //si comparamos con otro elemento, a longCable le restamos la diferencia entre dicho elemento y su próximo.
				
		if (longCable >= 0) {
			resTemp++; //actualizamos resTemp solo si longCable sigue siendo positivo.
			actual++;
		}
	
	}

	int conectadas = resTemp;

	if (resTemp == 1) {
		resTemp = 0; //si resTemp sigue en 1 como lo definimos, es porque no se conectó ninguna ciudad, entonces lo seteamos en 0.
	}

	if (longCable < 0) {
		longCable = aux; //si nos pasamos y longCable queda negativo, volvemos al valor anterior.
	}


	while (v[actual] != v.back()) { //mientras que el elemento actual no sea el último..
		
		if (resTemp == 0) {
			conectadas = 0; //si no conectamos ninguna ciudad, contectadas será 0, start 1, actual+1
			start++;
			actual++;

		} else {
			
			if(conectadas>0){
			conectadas = conectadas - 1; //si conectamos alguna ciudad, 'conectadas' será la cant de ciudades conectadas - 1.
			}
			longCable = longCable + (v[start+1]-v[start]);
			start++;
			
		}

		while (longCable >= 0 && v[actual]!= v.back()) {
			aux = longCable;			
			longCable = longCable - (v[actual+1]- v[actual]);	
										
			if (longCable >= 0) {
				conectadas++;
				actual++;
			}

			if (conectadas == 1){
			conectadas = 2;				//pues si conecto por primera vez en realidad tengo 2 ciudades conectadas	
			}		
		}
		

		if (longCable < 0) {
		longCable = aux; //si nos pasamos y longCable queda negativo, volvemos al valor anterior.
		}

		
		if (conectadas > resTemp) {
			resTemp = conectadas;
		}

	}

	if (resTemp == 1) {
		resTemp = 2;
	}

	//imprimimos por pantalla el tiempo transcurrido para cada iteracion de 'conectar'.
	//printf("Tiempo en segundos transcurrido de un ramal: %f \n", ((double)clock() - startTime) / CLOCKS_PER_SEC);

	return resTemp;
}


int main() {

	ofstream out;
	out.open("resultado.out");
    ifstream in("Tp1Ej1.in");

    int iteraciones = 0;
    double tiempo_promedio = 0;

    while (in.good()) {
    	vector<int> vec;
    	vec.push_back(0);

	    string st;
	    getline(in,st);
	    istringstream iss;
	    iss.str(st);
	    iss.clear();

	    int a;
	    iss>>a;

	    
	    getline(in,st);	    
	    iss.str(st);
	    iss.clear();
	    int b;
	    
	    while (iss>>b) {
	    	vec.push_back(b);
	    }

	    
		while (iteraciones <= 100) {
			clock_t startTime = clock();  //empezamos a medir el tiempo

			int f = conectar(vec,a); //f es la cantidad máxima de ciudades conectadas de un ramal.

			tiempo_promedio += ((double)clock() - startTime) / (CLOCKS_PER_SEC / 1000); //primero sumo los tiempos de las 100 iteraciones.

			if(iteraciones == 0){
				out << f << endl; //en el archivo de salida guardo una vez la cantidad maxima de ciudades conectadas del ramal.
			}
			iteraciones++;
	    }



	    tiempo_promedio = tiempo_promedio/100.0; //calculo el promedio del tiempo de las 100 iteraciones.
	    //printf("%f \n", tiempo_promedio);  //se descomenta para saber los tiempos promedios para el gráfico.

	    tiempo_promedio = 0.0;
	    iteraciones = 0;
    
    }

    out.close();
	return 0;
}