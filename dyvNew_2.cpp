#include <iostream>
#include <time.h>
using namespace std;

struct Solucion {
	int indice;
	int suma;
};

Solucion resolucionDirecta(int * dif, int inicio, int fin, int m) {
    Solucion aux;
    aux.indice = inicio;
    aux.suma = 0;

    // Primera ventana
   // int fin1 = inicio + m < fin ? inicio + m : fin; // Evitar que salga del rango
    for (int i = inicio; i < min(inicio+m,fin); i++) {
        aux.suma += dif[i];
    }
    
    Solucion s = aux; 
    for (int i = inicio + m; i < fin; i++) {
        aux.suma = aux.suma - dif[i-m] + dif[i];	// Quitamos el primer elemento y añadimos el siguiente.
        aux.indice = i - m + 1;
        //cout << "dif[i+m] " << dif[i-m] << endl;
        //cout << "dif[i] " << dif[i] << endl;
        
        // Si la nueva suma es mayor, actualizar la mejor solución.
        if (aux.suma > s.suma) {
            s.suma = aux.suma;
            s.indice = aux.indice;
        }
    }

    return s;
}


void generadorCasos(char A[], char B[], int n) {
	for (int i = 0; i < n; i++) {
		A[i] = rand() % (26) + 'a';
		B[i] = rand() % (26) + 'a';
	}
}

Solucion combinar(int* dif, Solucion p1, Solucion p2, int inicio, int fin, int medio, int m) {
	
	int aux = 0;
	for (int i = p1.indice; i <  min(p1.indice + m, fin); i++)
		aux += dif[i];

	Solucion s;
	s.suma = aux;
	s.indice = p1.indice;
	int i = p1.indice;
	while (i < fin-m) {
		aux += dif[i + m] - dif[i];
		//cout << "i + m  : " << i + m  << endl;
		//cout << "i  : " << i  << endl;
		if (aux > s.suma) {
			s.suma = aux;
			s.indice = i + 1;
		}
		i++;
	}
		
	return s;
}	


Solucion dyv(int* dif, int inicio, int fin, int m) {
	// Comprobar si el tamaño del problema es suficientemente pequeño.
	Solucion s;
	s.suma = 0;
	s.indice = inicio;
	int medio = (inicio + fin) / 2;
		Solucion p1, p2;
		p1.suma = 0;
		p2.suma = 0;
		p1.indice = inicio;
		p2.indice = medio;

	if (medio - inicio >= m) {
		if (fin - inicio > m) {
			p1 = dyv(dif, inicio, medio, m);
			p2 = dyv(dif, medio, fin, m);
		}
		s = combinar(dif, p1, p2, inicio, fin, medio, m);
	} else {//if (fin - inicio == m) {
		s = combinar(dif, p1, p2, inicio, fin, medio, m);
	} 
	return s;
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		srand(time(NULL));
		clock_t t;
		t = clock();
		// Declaramos las variables 'n' y 'm', y las introducimos por la consola.

		// Declaramos las cadenas 'A' y 'B', y las introducimos por la consola.
		char A[n], B[n];
		generadorCasos(A, B, n);

/*		for (int i = 0; i < n; i++)
			cout << A[i] << " ";
		cout << endl;

		for (int i = 0; i < n; i++)
			cout << B[i] << " ";
		cout << endl;
*/
		// Declaramos el array de enteros 'dif' y alcenamos en él la diferencia 
		// entre las cadenas 'A' y 'B'.
		int dif[n];
		for (int i = 0; i < n; i++)
			dif[i] = abs(A[i] - B[i]);
/*		for (int i = 0; i < n; i++)
			cout << dif[i] << " ";
		cout << endl;
*/
		// Llamamos a la función que aplica divide y vencerás, e imprimimos el 
		// resultado por la terminal.
		
		if(m>0) {
			Solucion s = dyv(dif, 0, n, m);
			Solucion s2 = resolucionDirecta(dif, 0, n, m);
			cout << "indice : " << s.indice + 1 << " " << s.suma << endl;
			cout << "resolucionDirecta : " << s2.indice + 1 << " " << s2.suma << endl;
			t = clock() - t;
			21cout << n << ";" << (((float)t) / CLOCKS_PER_SEC) * 1000 << endl;
		} else {
			cout << "indice: 0 suma: 0\n";
		}
		
	}
}
//	char A[n] = { 'c', 'd', 'd', 'a', 'b', 'c', 'd', 'a', 'c', 'c' };
//	char B[n] = { 'c', 'a', 'c', 'd', 'd', 'b', 'c', 'a', 'd', 'c' };


