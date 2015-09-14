using namespace std;
#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <map>
#include <time.h>
//#include <stdio.h>

//PARA COMPILAR g++ -std=c++11 -o ej3 ej3.cpp

class Ronda {
	public:
		Ronda();
		
		Ronda(vector<char> exploradoras, vector< vector<char> > amigas);
		
		vector<char> amigasDe(char e);
		
		vector<char> rondaActual();
		
		bool cambiarOrden();

		tuple<int, int> sumaDistancias();

		int mejorOrden();

		void ordenAlfabetico();

		void imprimirRonda();

		void imprimirAmistades();

	private:

		map<char, vector<char> > friends;
		vector<char> explorers;

		// El vector explorers representa la ronda, y friends es un diccionario en el que guardamos las amigas de cada exploradora.

		void completarAmigas (vector<char>& exploradoras, vector<vector<char> >& amigas);
		bool pertenece (vector<char> v , char e);
		bool perteneceConPos (vector<char> v , char e, int& posicion);
};


//**************************************************************************
//FUNCIONES PUBLICAS DE LA CLASE RONDA
//**************************************************************************

// Constructor de ronda vacia.
Ronda::Ronda(){}								//O(1)

//**************************************************************************

// Constructor de ronda a partir de una lista de exploradoras y una lista con las amigas de cada una (cada exploradora se asocia a su grupo de amigas mediante el indice de las listas).
Ronda::Ronda(vector<char> exploradoras, vector< vector<char> > amigas) {	//O(e)
	explorers = exploradoras;													//O(e)
	completarAmigas(explorers, amigas);										
	for ( int i = 0; i < explorers.size(); i++ ) {
		friends.insert(pair<char, vector<char> >(explorers[i], amigas[i]));
	}
}

// e = cantidad de exploradoras
// a = cantidad de amistades

//**************************************************************************

// Dada una exploradora perteneciente a la ronda, devuelve un vector que contiene a sus amigas.
vector<char> Ronda::amigasDe(char e) {	//O(e)
	return friends[e];						//O(e)
}

//**************************************************************************

// Devuelve una vector que representa la ronda.
vector<char> Ronda::rondaActual() {		//O(e)
	return explorers;						//O(e)
}

//**************************************************************************

// Cambia las posiciones de las exploradoras en la ronda.
bool Ronda::cambiarOrden() {														//O(e)
	return next_permutation(explorers.begin(), explorers.begin()+explorers.size()); 	//O(e)
}

//**************************************************************************

// Calcula la suma de las distancias entre las exploradoras que son amigas (primer componente) , y la mayor distancia entre dos amigas en la ronda(segunda componente).
tuple<int, int> Ronda::sumaDistancias() {									//O(e^3)
	int i = 0;																//O(1)
	int suma = 0;															//O(1)
	int maxLograda = 0;													//O(1)
	while ( i < explorers.size() ) {											//O(e)
		vector<char> amigas = friends[explorers[i]];						//O(e)
		int j = 0;															//O(1)         
		while ( j < amigas.size() ) {                    								//O(e)	(en total 2.a iteraciones)
			int pos;															//O(1)
			int distancia;													//O(1)
			perteneceConPos(explorers, amigas[j], pos);					//O(e)
			if (pos - i > 0) {													//O(1)
				if (pos - i > explorers.size() / 2) {							//O(1)
					distancia = explorers.size() - (pos - i); 					//O(1)
				}else{														//O(1)
					distancia = pos - i;										//O(1)
				}
				if (maxLograda < distancia) maxLograda = distancia;		//O(1)
				suma = suma + distancia;									//O(1)
			}
			j++;															//O(1)
		} 
		i++;																//O(1)
	}
	tuple<int, int> res;														//O(1)
	get<0>(res) = suma;													//O(1)
	get<1>(res) = maxLograda;											//O(1)				
	return res;																//O(1)
}

//**************************************************************************

// Ordena la ronda de manera tal que la suma de las distancias entre amigas se la menor posible, y devuelve la máxima distancia que hay entre dos amigas en la nueva ronda.
int Ronda::mejorOrden() {															
	ordenAlfabetico();																		
	tuple<int, int> minimaSuma = sumaDistancias();
	vector<char> mejorRonda = explorers;
	while ( cambiarOrden() ){							
		tuple<int, int> dist = sumaDistancias();			
		if ( get<0>(dist) < get<0>(minimaSuma) ) {													
			minimaSuma = dist;
			mejorRonda = explorers;																		
		}
	}
	explorers = mejorRonda;																			
	int res  = get<1>(minimaSuma);																	
	return res;																							
}

// e = cantidad de exploradoras

//**************************************************************************

// Ordena la ronda alfabeticamente.
void Ronda::ordenAlfabetico() {									//O(e log(e))
	sort( explorers.begin(), explorers.begin()+explorers.size() ); //O(e log(e))
}

//**************************************************************************

// Imprime la ronda.
void Ronda::imprimirRonda() {
		cout << "[";
	for(int j = 0; j < explorers.size() ; j++){
		if (j + 1 == explorers.size()) {
			cout << explorers[j];	
		}else{
			cout << explorers[j] << ",";
		}
	}
	cout << "]" << endl;
}

//**************************************************************************

// Imprime todas las exploradoras de la ronda, cada una con su conjunto de amigas.
void Ronda::imprimirAmistades() {
	cout << "[";
	for ( map<char, vector<char> >::iterator it = friends.begin(); it != friends.end(); ++it ) {
    		cout << it->first << "-->";
    		vector<char> aux = it->second;
    		cout << "{";
    		for (int i = 0; i < aux.size(); i++) {
    			if ( i == aux.size() - 1 ) {
    				cout << aux[i];
    			}else{
    				cout << aux[i] <<",";
    			}
    		}
    		cout << "}";
    		if (distance(it, friends.end()) != 1) cout << ";";
    	}
    	cout << "]" <<endl;
}

//**************************************************************************
// FUNCIONES AUXILIARES(PRIVADAS) DE LA CLASE RONDA
//**************************************************************************

// Funcion utilizada a la hora de crear una ronda no vacia. Como en el archivo de entrada las amistades pueden no estar escritas de manera simetrica, esta funcion verifica si falta escribir algo y lo agrega, para almacenarlo de esta forma.
void Ronda::completarAmigas (vector<char>& exploradoras, vector<vector<char> >& amigas) { //O(e³)
	int i = 0;																//O(1)
	while ( i < exploradoras.size() ) {										//O(e)
		int j = 0;															//O(1)	
		while ( j < amigas[i].size() ) {										//O(e)	(en total 2.a iteraciones)
			int pos;															//O(1)
			if ( perteneceConPos(exploradoras, amigas[i][j], pos) ) {		//O(e)
				if ( !(pertenece(amigas[pos], exploradoras[i])) ) {			//O(e)
					amigas[pos].push_back(exploradoras[i]);				//O(1)
				}
			}else{
				exploradoras.push_back(amigas[i][j]);						//O(1)
				vector<char> nueva = {exploradoras[i]};					//O(1)
				amigas.push_back(nueva);									//O(1)
			}
			j++;															//O(1)
		}
		i++;																//O(1)
	}
}

// e = cantidad de exploradoras

//**************************************************************************

// Devuelve true si e aparece al menos una vez en v.
bool Ronda::pertenece (vector<char> v , char e) {	//O(n)
	int i = 0;										//O(1)
	bool noEncontrado = true;						//O(1)
	while (noEncontrado && i < v.size() ){			//O(n)
		noEncontrado = !(v[i] == e);				//O(1)
		i++;										//O(1)
	}
	return !noEncontrado;							//O(1)
}

// n = longitud del vector v

//**************************************************************************

// Igual que pertenece, pero ademas modifica posicion asignandole el indice del caracter encontrado (si es false no se debe tener en cuenta).
bool Ronda::perteneceConPos (vector<char> v , char e, int& posicion) { //O(n)
	int i = 0;											//O(1)
	bool noEncontrado = true;							//O(1)
	while (noEncontrado && i < v.size() ){				//O(n)
		noEncontrado = !(v[i] == e);					//O(1)
		i++;
	}
	posicion = i - 1;									//O(1)
	return !noEncontrado;								//O(1)
}

// n = longitud del vector v

//**************************************************************************

int main() {

//ARCHIVOS DE SALIDA "resultados.out" Y "tiempos.out"

	ifstream in("Tp1Ej3.in");
 	ofstream out;
   	out.open("Tp1Ej3.out");
	double tiempo_promedio = 0;
	ofstream outtiempos;
	outtiempos.open("tiempos.out");
	

	while(in.good()) {
		vector<char> exploradoras;
		vector<vector<char> > amigas;
		string s,xs;	
		getline(in, s);

		for(int i = 0; i < s.size(); i++) {	 // Con esto reemplazo los ";" por " ".
			if (s[i] == ';') s[i] = ' ';
		}

		istringstream iss;
		iss.str(s);
		iss.clear();
		while(iss >> s >> xs) {
			exploradoras.push_back(s[0]);
			vector<char> v;
			for (int j = 0; j < xs.size(); j++) {
				v.push_back(xs[j]);
			}
			amigas.push_back(v);  
		}
		
		
		
		
		int iteraciones = 1;

		while (iteraciones <= 1) {
			clock_t startTime = clock();  //empezamos a medir el tiempo

			Ronda r(exploradoras, amigas);
			int res = r.mejorOrden();

			tiempo_promedio += ((double)clock() - startTime) / (CLOCKS_PER_SEC / 1000); //primero sumo los tiempos de las 10 iteraciones.
			if (iteraciones == 1) {
				out << res << " ";
				vector<char> aux = r.rondaActual();
				for (int i = 0; i < aux.size(); i++) {
					out << aux[i];
				}	
				out << endl;
			}
			iteraciones++;
	    	}

	    	//tiempo_promedio = tiempo_promedio/10.0; //calculo el promedio del tiempo de las 10 iteraciones.
        	//printf("%f \n", tiempo_promedio);  //se descomenta para saber los tiempos para el gráfico.
        	outtiempos << tiempo_promedio << endl;
       	tiempo_promedio = 0.0;

	  
	   

	    
	}
	out.close();
	outtiempos.close();

}


