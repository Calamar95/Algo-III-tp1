using namespace std;
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

bool pertenece (vector<char> v , char e) {	//O(n)
	int i = 0;										//O(1)
	bool noEncontrado = true;						//O(1)
	while (noEncontrado && i < v.size() ){			//O(n)
		noEncontrado = !(v[i] == e);				//O(1)
		i++;										//O(1)
	}
	return !noEncontrado;							//O(1)
}


//GENERADOR DE ENTRADAS DE i EXPLORADORAS (K ENTRADAS) // ARCHIVO DE SALIDA "testsDeiExploradoras.in"

int main(){
	
	ofstream out;
   	out.open("testsDeiExploradoras.in");

   	srand (time(NULL));
	for (int k = 0; k < 5; k++){ //ACA SE MODIFICA EL K
		vector<char> v;
		int i = 0;
		while (i < 10) { //ACA SE MODIFICA EL I
			int n = rand() % 26 + 97;
			if ( !pertenece(v, char(n)) ) {
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