#include <iostream>
using namespace std;

struct solucion {
	int indice;
	int suma;
};

void generadorCasos(char A[], char B[], int n){
	for(int i = 0; i < n; i++){
		A[i] = rand()%(26) + 'a';
		B[i] = rand()%(26) + 'a';
	}
}

solucion resolucionDirecta(char A[], char B[], int inicio, int fin, int m) {
	solucion aux;
	aux.indice = inicio;
	aux.suma = 0;
	
	int fin1 = inicio + m <= fin ? inicio + m : fin; // Evitar que salga del rango
	for(int i = inicio; i < fin1; i++)	
		aux.suma += abs(A[i]-B[i]);
			 
	solucion s = aux;
	for(int i = inicio + m; i <= fin; i++){
		aux.suma = aux.suma-(abs(A[aux.indice]-B[aux.indice]))+ abs(A[i]-B[i]);
		aux.indice++;
		if(aux.suma > s.suma){
			s.suma = aux.suma;
			s.indice = aux.indice;
		}
		
	}
	return s;
}

solucion combinar(char A[], char B[], solucion p1, solucion p2, int inicio, int fin, int medio, int m){
	
	if(m == 1){
		if(p1.suma > p2.suma) return p1;
		else return p2;
	}
	
	solucion s;
	if(fin - inicio + 1 <= m){
		s.indice = p1.indice;
		s.suma = p1.suma + p2.suma;		
	}
	
	int inicioMedio = medio-(m-2) < inicio ? inicio : medio-(m-2); // para evitar números negativos
	int finMedio = medio+m > fin ? fin : medio+m;		           // para evitar números negativos
	s = resolucionDirecta(A,B,inicioMedio, finMedio, m);	
	
	if(p1.suma >= p2.suma && p1.suma >= s.suma){
		return p1;
	}else if(p2.suma >= p1.suma && p2.suma >= s.suma){
		return p2;
	}else{
		return s;
	}		
}


solucion dyv(char A[], char B[], int inicio, int fin, int m) {
	// Comprobar si el tamaño del problema es suficientemente pequeño.
	if (fin - inicio <= m) { 
		return resolucionDirecta(A,B,inicio,fin,m);
	}
	
	int medio = (inicio + fin) / 2;
	solucion p1 = dyv(A,B,inicio, medio, m);
	solucion p2 = dyv(A,B,medio+1, fin, m);	
	
	return combinar(A,B,p1,p2,inicio,fin,medio,m);
}

int main() {
	srand(time(NULL));
	// Establecemos el tamaño de la n y m de forma temporal a través de la terminal.
	int n, m;
	cin >> n >> m;
	
	//n = rand()%(1000000-100)+100; //-> Rango entre 10⁶ - 10² -> tamaño de la n
	//m = rand()%(n) + 1;	// Genera un valor de m entre 1 y n.
	
	char A[n], B[n];
	generadorCasos(A,B,n);
	
	cout << "n = " << n << " " << "m = " << m << endl;
	cout << "A : ";
	for(int i = 0; i < n; i++) cout << A[i] << " ";
	cout << endl << "--------------------------------" << endl;
	
	cout << "B : ";
	for(int i = 0; i < n; i++) cout << B[i] << " ";
	cout << endl << "--------------------------------" << endl;
	
	cout << "dif: ";
	for(int i = 0; i < n; i++) cout << abs(A[i]-B[i]) << " ";
	cout << endl;
	
	//solucion s = resolucionDirecta(0,n-1,m);
	//cout << s.indice << " " << s.suma << endl;
	solucion s = dyv(A,B,0, n-1, m);
	cout << "indice: " << s.indice << " suma: " << s.suma << "\n";
	
	
}
//	char A[n] = { 'c', 'd', 'd', 'a', 'b', 'c', 'd', 'a', 'c', 'c' };
//	char B[n] = { 'c', 'a', 'c', 'd', 'd', 'b', 'c', 'a', 'd', 'c' };



