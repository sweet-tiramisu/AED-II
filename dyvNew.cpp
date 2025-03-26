#include <iostream>
using namespace std;

struct solucion {
	int indice;
	int suma;
};

// Función generadora de caracteres
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

    // Primera ventana
    int fin1 = inicio + m < fin ? inicio + m : fin; // Evitar que salga del rango
    for (int i = inicio; i < fin1; i++) {
        aux.suma += abs(A[i] - B[i]);
    }
    
    solucion s = aux; 
    for (int i = inicio + m; i < fin; i++) {
        aux.suma = aux.suma - abs(A[i-m] - B[i-m]) + abs(A[i] - B[i]);	// Quitamos el primer elemento y añadimos el siguiente.
        aux.indice = i - m + 1;
        // Si la nueva suma es mayor, actualizar la mejor solución.
        if (aux.suma > s.suma) {
            s.suma = aux.suma;
            s.indice = aux.indice;
        }
    }

    return s;
}


solucion dyv(char A[], char B[], int inicio, int fin, int m) {
	int nuevaN = (fin-inicio);
	//cout << nuevaN << " ";
	if(nuevaN==m){
		return resolucionDirecta(A,B,inicio,fin,m);
	}
	
	int finIzquierdo = inicio +(nuevaN+(m-1))/2;
	//if(finIzquierdo > fin) finIzquierdo = fin;
	solucion p1 = dyv(A,B,inicio, finIzquierdo,m);
	solucion p2 = dyv(A,B,finIzquierdo-(m-1), fin, m);
	
	if(p1.suma >= p2.suma){
		return p1;
	}else{
		return p2;
	}
		
}

int main() {
	srand(time(NULL));
	// Establecemos el tamaño de la n y m de forma temporal a través de la terminal.
	int n, m;
	cin >> n >> m;
	
	//n = rand()%(1000000-100)+100; //-> Rango entre 10⁶ - 10² -> tamaño de la n
	//m = rand()%(n) + 1;	// Genera un valor de m entre 1 y n.
	
	// Casos de prueba
	//char A[n] = { 'c', 'd', 'd', 'a', 'b', 'c', 'd', 'a', 'c', 'c' };
	//char B[n] = { 'c', 'a', 'c', 'd', 'd', 'b', 'c', 'a', 'd', 'c' };
	//char A[n] = {'x','u','n','p','h','o','d','s','i','o','o','e','n','e','d','i','d','r','n','u','s','z','c','x', 'e','f','l','i','i','r'};
	//char B[n] = {'q','n','g','b','l','f','s','z','l','s','x','n','z','t','n','c','f','s','h','u','i','y','t','k', 'n','s','j','y','m','n'};
	
	char A[n], B[n];
	generadorCasos(A,B,n);
	
	
	cout << "n = " << n << " " << "m = " << m << endl;
/*	cout << "A : ";
	for(int i = 0; i < n; i++) cout << A[i] << " ";
	cout << endl << "--------------------------------" << endl;
	
	cout << "B : ";
	for(int i = 0; i < n; i++) cout << B[i] << " ";
	cout << endl << "--------------------------------" << endl;
	
	cout << "dif: ";
	for(int i = 0; i < n; i++) cout << abs(A[i]-B[i]) << " ";
	cout << endl;
*/	
	if(m>0) {
		solucion s1 = dyv(A,B,0, n, m);
		solucion s2 = resolucionDirecta(A,B,0,n,m);
		cout << "resolucionDirecta : " << s2.suma << " " << s2.indice+1 << endl;
		cout << "dyv : " << s1.suma << " " << s1.indice+1 << endl;
		//cout << "indice: " << s.indice + 1 << " suma: " << s.suma << "\n";
	} else {
		cout << "indice: 0 suma: 0\n";
	}
	
}




