using namespace std;
#include <vector>
//#include <tuple>
#include <iostream>
#include <algorithm>
#include <sys/time.h>
#include <sstream>
#include <fstream>
#include <map>


void imprimir (vector<char> v) {
	cout << "[";
	for(int j = 0; j < v.size() ; j++){
		if (j + 1 == v.size()) {
			cout << v[j];	
		}else{
			cout << v[j] << ",";
		}
	}
	cout << "]" << endl;
}

void imprimir2 (vector< vector<char> > v ) {
	cout << "[";
	for ( int j = 0; j < v.size() ; j++ ) {
		cout << "{";
		for ( int i = 0; i < v[j].size() ; i++ ) {
			if ( i == v[j].size() - 1 ) {
				cout << v[j][i];
			}else{
				cout << v[j][i] << ",";
			}
		}
		cout << "}";
		if ( j != v.size() - 1 ) {
			cout << ";";
		}
	}
	cout << "]" <<endl;
}

void imprimirDicc (map<char, vector<char> > d ) {
	cout << "[";
	for ( map<char, vector<char> >::iterator it = d.begin(); it != d.end(); ++it ) {
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
    		if (distance(it, d.end()) != 1) cout << ";";
    	}
    	cout << "]" <<endl;
}

bool pertenece (vector<char> v , char e) {	//O(n)
	int i = 0;										//O(1)
	bool noEncontrado = true;						//O(1)
	while (noEncontrado && i < v.size() ){			//O(n)
		noEncontrado = !(v[i] == e);				//O(1)
		i++;										//O(1)
	}
	return !noEncontrado;							//O(1)
}

//GENERADOR DE k ENTRADAS DE HASTA  i EXPLORADORAS CADA UNA // ARCHIVO DE SALIDA "testsAleatorios.in"

int main(){
	
	ofstream out;
   	out.open("testsAleatorios.in");

	for (int k = 0; k < 14; k++){ //ACA SE CAMBIA EL K
		vector<char> v;
		int i = 0;
		while (i < 10) { //ACA SE CAMBIA EL i
			int n = rand() % 26 + 97;
			if ( pertenece(v, char(n)) ) {
				i++;
			}else{
				v.push_back(char(n));
				i++;
			}
		}
		vector<vector<char> > amigas;
		for (int j = 0; j < v.size(); j++) {
			vector <char> aux;
			for (int i = 0; i < v.size(); i++) {
				int n = rand() % 2 + 0;
				if ( bool(n) && i != j) aux.push_back(v[i]);
			}
			amigas.push_back(aux);
		}

		//imprimir(v);
		//imprimir2(amigas);

		i = 0;	
		while ( i < v.size() ) {
			if (amigas[i].size() == 0){
				i++;			
			}else{
				out << v[i] << " ";
				for (int j = 0; j < amigas[i].size(); j++) {
					out << amigas[i][j];
				}
				i++;
				if ( i != v.size() ) out << ";";
			}
		}
		out << endl;
	}
	out.close();

	
   	

   	

}