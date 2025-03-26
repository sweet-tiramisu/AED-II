#include <iostream>
using namespace std;

// Estructura de datos donde almacenaremos la suma total y el índice donde 
// comienza la subcadena solución.
struct Solucion {
	int indice;
	int suma;
};

Solucion resolucionDirecta(int* dif, int inicio, int fin, int m) {
	// La resolución directa del problema se basa en aplicar el algoritmo 
	// de ventana deslizante de tamaño 'm' entre las posiciones 'inicio' 
	// y 'fin' del array de enteros 'dif'.

	// Declaramos e inicalizamos la variable 'aux' de tipo Solucion, donde 
	// guardaremos el resultado de los pasos intermedios.
    Solucion aux;
    aux.indice = inicio;
    aux.suma = 0;

    // Declaramos el entero 'fin1', correspondiente al límite izquierdo de 
	// la ventana deslizante, y calculamos la ventana inicial.
    int fin1 = inicio + m < fin ? inicio + m : fin; // Evitar que salga del rango
    for (int i = inicio; i < fin1; i++) 
        aux.suma += dif[i];
    
	// Declaramos la variable 's' de tipo Solucion (tomando el valor de 
	// 'aux') y vamos desplazando la ventana deslizante, guardando el máximo 
	// en 's'.
    Solucion s = aux; 
    for (int i = inicio; i < fin - m; i++) {
		// Restamos el elemento de la izquierda y le sumamos el nuevo.
		aux.suma = aux.suma - dif[i] + dif[i + m];
        aux.indice = i - m + 1;
        if (aux.suma > s.suma) {
            s.suma = aux.suma;
            s.indice = aux.indice;
        }
    }
    return s;
}


Solucion dyv(int* dif, int inicio, int fin, int m) {
	// Declaramos el entero 'nuevaN', que representa el tamaño 'n' de 
	// la subproblema actual
	int nuevaN = fin - inicio;

	// Comprueba si 'nuevaN' es igual al tamaño de la subcadena que se 
	// busca y, si es así, se llama a la función 'resolucionDirecta'.
	if(nuevaN == m) 
		return resolucionDirecta(dif, inicio, fin, m);
	
	// Declaramos el entero 'finIzquierdo', que representa el límite 
	// izquierdo de la primera mitad, y llamamos recursivamente a la 
	// función 'dyv' a cada una de las mitades.
	int finIzquierdo = inicio + (nuevaN + (m - 1)) / 2;
	Solucion p1 = dyv(dif, inicio, finIzquierdo, m);
	Solucion p2 = dyv(dif, finIzquierdo - (m - 1), fin, m);
	
	// Devolvemos la solución cuya suma sea máxima.
	if(p1.suma >= p2.suma)
		return p1;
	else
		return p2;
}

int main() {
	// Declaramos las variables 'n' y 'm', y las introducimos por la consola.
	int n, m;
	cin >> n >> m;
	
	// Declaramos las cadenas 'A' y 'B', y las introducimos por la consola.
	char A[n], B[n];
	for (int i = 0; i < n; i++)
		cin >> A[i];
	for (int i = 0; i < n; i++)
		cin >> B[i];

	// Declaramos el array de enteros 'dif' y alcenamos en él la diferencia 
	// entre las cadenas 'A' y 'B'.
	int dif[n];
	for (int i = 0; i < n; i++) 
		dif[i] = abs(A[i] - B[i]);
	
	// Llamamos a la función que aplica divide y vencerás, e imprimimos el 
	// resultado por la terminal.
	Solucion s = dyv(dif, 0, n, m);
	cout << s.indice + 1 << " " << s.suma << endl;
}




