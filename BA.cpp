#include <iostream>
using namespace std;


int generar(int nivel, int * s, int n, int ** matriz, int &numPersonas, int &sumaActual){
	s[nivel-1] += 1;
		
	if(s[nivel-1] == 1){
		numPersonas++;
		// Añadimos las distancias de los elementos seleccionados
		for(int i = 0; i < n; i++){
			if(s[i] == 1 && i != nivel -1)	// 
				sumaActual += matriz[i][nivel-1] + matriz[nivel-1][i]; 
		}
	}
	return sumaActual;
}

int backtracking(int n, int m, int ** matriz){
	int * s = new int[n];
	for(int i = 0; i < n; i++)	s[i] = -1; // Inicializamos a -1;
	
	int nivel = 1;
	int maxSuma = 0;
	int sumaActual = 0;
	int numPersonas = 0;
	
	
	while(nivel != 0){
		// Genero un hermano
		generar(nivel, s, n, matriz, numPersonas, sumaActual);
		
		// Si he encontrado una solución que mejora a maxSuma, la guardo.
		if(numPersonas <= m && sumaActual > maxSuma){
				maxSuma = sumaActual;
		}		
		
		// Si podríamos llegar a la solución final, seguimos
		if(numPersonas <= m && nivel < n){ 
			nivel += 1;
		}else{
			// En caso contrario, retrocedemos hasta que se encuentre un nodo con más hermanos por explorar.
			while(nivel > 0 && !(s[nivel-1] <= 0)){
				if(s[nivel-1] == 1){
					numPersonas--;
					for(int i = 0; i < n; i++){
						if(s[i] == 1 && i != nivel -1)
							sumaActual -= matriz[i][nivel-1] + matriz[nivel-1][i]; 
					}
				}
				s[nivel-1] = -1;
				nivel -= 1;
			}
		
		}
		
	}	
	
	delete[] s;
	return maxSuma;
	
}

int main(){
	int numCasosPrueba,n,m;
	cin >> numCasosPrueba;
	for(int i = 0; i < numCasosPrueba; i++){
		cin >> n >> m;
		//Leemos la matriz de entrada
		int ** matriz = new int*[n];
		
		for(int j = 0; j < n; j++){
			matriz[j] = new int[n];
			for(int k = 0; k < n; k++){
				cin >> matriz[j][k];
			}
		}
		
		cout << backtracking(n,m,matriz) << endl;
		
		//Liberamos memoria
		for(int i = 0; i < n; i++){
			delete[] matriz[i];
		}
		delete[] matriz;
	}
}
