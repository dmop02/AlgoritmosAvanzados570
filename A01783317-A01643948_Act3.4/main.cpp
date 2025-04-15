/**
 * Autor: Domingo Mora | A01783317 / Alvaro Solano | A01643948
 * Fecha: 11 de abril de 2025
 * Referencias: https://brilliant.org/wiki/hopcroft-karp/
 * https://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-1-introduction/
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class BipartiteMatching {
private:
    int numConductores;        
    int numRutas;               
    vector<vector<int>> grafoAdyacencia;   
    vector<int> asignacionRutas;           
    vector<bool> nodosVisitados;          

public:
     // Complejidad: O(conductores + rutas)
    BipartiteMatching(int conductores, int rutas, int relaciones) {
        numConductores = conductores;
        numRutas = rutas;
        grafoAdyacencia.resize(numConductores + numRutas);
    }

    //Complejidad: O(1)
    void agregarArista(int conductor, int ruta) {
        grafoAdyacencia[conductor].push_back(numConductores + ruta - 1);
        grafoAdyacencia[numConductores + ruta - 1].push_back(conductor);
    }

    
     // Complejidad: O(V*E) donde V es número de vértices y E número de aristas
     
    bool buscarCaminoAumentante() {
        queue<int> colaNodos;
        vector<int> nodoPadre(numConductores + numRutas, -1);
        
        for (int nodoActual = 0; nodoActual < numConductores; nodoActual++) {
            if (find(asignacionRutas.begin(), asignacionRutas.end(), nodoActual) == asignacionRutas.end()) {
                colaNodos.push(nodoActual);
                nodoPadre[nodoActual] = -2;
            }
        }
        
        int nodoDestino = -1;
        
        while (!colaNodos.empty() && nodoDestino == -1) {
            int nodoActual = colaNodos.front();
            colaNodos.pop();
            
            for (int nodoAdyacente : grafoAdyacencia[nodoActual]) {

                if (nodoPadre[nodoAdyacente] == -1) {

                    if (nodoActual < numConductores && asignacionRutas[nodoAdyacente - numConductores] == nodoActual) {
                        continue;
                    }

                    else if (nodoActual >= numConductores && asignacionRutas[nodoActual - numConductores] != nodoAdyacente) {
                        continue; 
                    }
                    
                    nodoPadre[nodoAdyacente] = nodoActual;
                    
                    if (nodoAdyacente >= numConductores && asignacionRutas[nodoAdyacente - numConductores] == -1) {
                        nodoDestino = nodoAdyacente;
                        break;
                    }
                    
                    colaNodos.push(nodoAdyacente);
                }
            }
        }
        

        if (nodoDestino == -1) {
            return false;
        }
        

        while (nodoDestino != -2) {
            int nodoActual = nodoPadre[nodoDestino];
            if (nodoActual == -2) {
                break;
            }
            
            if (nodoDestino >= numConductores) { 
                asignacionRutas[nodoDestino - numConductores] = nodoActual;
            }
            
            nodoDestino = nodoActual;
        }
        
        return true;
    }

    
     // Complejidad: O(E*sqrt(V)) donde E es número de aristas y V número de vértices
    vector<pair<int, int>> obtenerAsignacionMaxima() {
        asignacionRutas.resize(numRutas, -1); 
        vector<int> asignacionConductores(numConductores, -1);
 
        nodosVisitados.resize(numConductores, false);
        

        function<bool(int)> buscarDFS = [&](int nodoActual) -> bool {
            if (nodosVisitados[nodoActual]) {
                return false;
            }
            nodosVisitados[nodoActual] = true;
            
            for (int nodoAdyacente : grafoAdyacencia[nodoActual]) {
                if (nodoAdyacente < numConductores) {
                    continue; 
                }
                
                int indiceRuta = nodoAdyacente - numConductores;
                if (asignacionRutas[indiceRuta] == -1 || buscarDFS(asignacionRutas[indiceRuta])) {
                    asignacionRutas[indiceRuta] = nodoActual;
                    asignacionConductores[nodoActual] = indiceRuta;
                    return true;
                }
            }
            return false;
        };
        

        bool seEncontroNuevoCamino = false;
        do {
            seEncontroNuevoCamino = false;
            fill(nodosVisitados.begin(), nodosVisitados.end(), false);
            
            for (int indiceConductor = 0; indiceConductor < numConductores; indiceConductor++) {
                if (asignacionConductores[indiceConductor] == -1 && buscarDFS(indiceConductor)) {
                    seEncontroNuevoCamino = true;
                }
            }
        } while (seEncontroNuevoCamino);
        

        vector<pair<int, int>> asignacionFinal;
        for (int indiceRuta = 0; indiceRuta < numRutas; indiceRuta++) {
            if (asignacionRutas[indiceRuta] != -1) {

                asignacionFinal.push_back({asignacionRutas[indiceRuta] + 1, indiceRuta + 1});
            }
        }
        
        return asignacionFinal;
    }
};


int main() {
    int numConductores = 0;
    int numRutas = 0;
    int numRelaciones = 0;
    cin >> numConductores >> numRutas >> numRelaciones;
    
    BipartiteMatching solucionador(numConductores, numRutas, numRelaciones);
    
    for (int indice = 0; indice < numRelaciones; indice++) {
        int conductor = 0;
        int ruta = 0;
        cin >> conductor >> ruta;
        solucionador.agregarArista(conductor - 1, ruta); 
    }
    
    vector<pair<int, int>> asignacionOptima = solucionador.obtenerAsignacionMaxima();
    
    cout << "Rutas asignadas: " << asignacionOptima.size() << endl;
    
    for (auto& par : asignacionOptima) {
        cout << par.first << " " << par.second << endl;
    }
    
    return 0;
}