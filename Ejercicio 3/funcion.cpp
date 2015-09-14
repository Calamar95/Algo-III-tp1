#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <math.h>
using namespace std;

int main(){

	ofstream out;
   	out.open("valores.out");

	int i = 2;
	while (i < 11) {
		float a = pow (i, i) / 35000;
		cout << a << endl;
		out << a <<endl;
		i++;
	}

	out.close();


}
