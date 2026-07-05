#pragma once
#include <vector>
#include <limits>
#include <iostream>
#include "Lista.h"

using namespace std;

// Removed the default 'vacio = -1' from the template definition
template<class T>
class CGrafo {
private:
    class CArco {
    public:
        T info;
        int v;
        float peso;

        CArco(int vLlegada, float p, T vacioInfo) {
            info = vacioInfo;
            v = vLlegada;
            peso = p;
        }
    };

    class CVertice {
    public:
        T info;
        vector<CArco*>* ady; 
        CVertice(T vacioInfo) {
            info = vacioInfo;
            ady = new vector<CArco*>();
        }
    };

    vector<CVertice*>* vertices;
    T valorVacio; 

public:

    CGrafo(T vacio) {
        vertices = new vector<CVertice*>();
        valorVacio = vacio;
    }

    ~CGrafo() {
        for (auto v : *vertices) {
            for (auto a : *(v->ady)) delete a;
            delete v->ady;
            delete v;
        }
        delete vertices;
    }

    CGrafo(const CGrafo&) = delete;
    CGrafo& operator=(const CGrafo&) = delete;

    int adicionarVertice(T info) {
        CVertice* vert = new CVertice(valorVacio);
        vert->info = info;
        vertices->push_back(vert);
        return vertices->size() - 1;
    }

    T obtenerVertice(int v) {
        return (vertices->at(v))->info;
    }

    int adicionarArco(int vOrigen, int vLlegada, float peso) {
        CVertice* vert = vertices->at(vOrigen);
        CArco* arc = new CArco(vLlegada, peso, valorVacio);
        vert->ady->push_back(arc);
        return vert->ady->size() - 1;
    }

    Lista<int>* Dijkstra(int vOrigen, int vDestino, float& costoTotal) {
        int n = vertices->size();
        vector<float> distancias(n, numeric_limits<float>::infinity());
        vector<int> previos(n, -1);
        vector<bool> visitados(n, false);

        distancias[vOrigen] = 0;

        for (int i = 0; i < n - 1; i++) {
            float min = numeric_limits<float>::infinity();
            int u = -1;
            for (int v = 0; v < n; v++) {
                if (!visitados[v] && distancias[v] <= min) {
                    min = distancias[v];
                    u = v;
                }
            }

            if (u == -1) break; 
            visitados[u] = true;

            for (CArco* arco : *(vertices->at(u)->ady)) {
                int v = arco->v;
                float peso = arco->peso;
                if (!visitados[v] && distancias[u] != numeric_limits<float>::infinity() && distancias[u] + peso < distancias[v]) {
                    distancias[v] = distancias[u] + peso;
                    previos[v] = u;
                }
            }
        }

        costoTotal = distancias[vDestino];

        Lista<int>* camino = new Lista<int>();
        if (costoTotal != numeric_limits<float>::infinity()) {
            for (int at = vDestino; at != -1; at = previos[at]) {
                camino->agregaInicial(at);
            }
        }
        return camino;
    }
};