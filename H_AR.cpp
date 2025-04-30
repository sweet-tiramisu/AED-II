#include <iostream>
#include <vector>
#include <list>
using namespace std;
#define INF 999999999

struct Maquina {
	int tarea, tiempo;
};

struct Solucion {
	int tarea, tiempo, maquina;
};

void insertarOrden(list<Maquina>* t, int tarea, int maquina) {
	Maquina nuevo;
	nuevo.tarea = tarea;
	cin >> nuevo.tiempo;

	list<Maquina>::iterator it = t[maquina].begin();
	while (it != t[maquina].end() && nuevo.tiempo > (*it).tiempo)
		++it;

	t[maquina].insert(it, nuevo);
}

void avanceRapido(Solucion* sol, int* acum, list<Maquina>* t, int n, int m) {
	bool* completada = new bool[n];
	for (int i = 0; i < n; ++i)
		completada[i] = false;

	int tareas = 0;

	while (tareas < n) {
		Solucion minimo;
		minimo.tiempo = INF;
		for (int i = 0; i < m; ++i) {
			list<Maquina>::iterator it = t[i].begin();
			while (it != t[i].end() && completada[(*it).tarea])
				++it;
			if (it != t[i].end() && (*it).tiempo + acum[i] < minimo.tiempo) {
				minimo.tarea = (*it).tarea;
				minimo.tiempo = (*it).tiempo + acum[i];
				minimo.maquina = i;
			}
		}
		acum[minimo.maquina] += (minimo.tiempo - acum[minimo.maquina]);
		completada[minimo.tarea] = true;
		sol[tareas] = minimo;

		++tareas;
	}
	delete[] completada;
}

int main() {
	int p, n, m;
	cin >> p;
	for (int caso = 0; caso < p; ++caso) {
		cin >> n >> m;
		list<Maquina>* t = new list<Maquina>[m];
		for (int tarea = 0; tarea < n; ++tarea)
			for (int maquina = 0; maquina < m; ++maquina)
				insertarOrden(t, tarea, maquina);

		Solucion* sol = new Solucion[n];
		int* acum = new int[m];
		for (int i = 0; i < m; ++i)
			acum[i] = 0;

		avanceRapido(sol, acum, t, n, m);
		
		cout << acum[sol[n - 1].maquina] << endl;

		for (int i = 0; i < n; ++i)
			cout << sol[i].tarea + 1 << " ";
		cout << endl;
		for (int i = 0; i < n; ++i)
			cout << sol[i].maquina + 1 << " ";
		cout << endl;
		delete[] acum;
		delete[] sol;
	}
}