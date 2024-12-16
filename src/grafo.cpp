#include "../include/grafo.hpp"

#include <iostream>
#include <queue>
#include <stack>
#include <vector>

#define INFINITO 0x3f3f3f3f
#define ST 2

using namespace std;

Grafo::Grafo(int n) : vertices(n + ST), grafo(n + ST) {}

void Grafo::addVertice(int u, int t)
{
	TipoVertice tipo;
	Vertice v;

	// Verifica o tipo de aresta
	if(t == 0) tipo = GERADOR;
	else if(t > 0) tipo = CONSUMIDOR;

	v = {u, tipo, t};	
	vertices.push_back(v);
}

void Grafo::addAresta(int u, int v, int c)
{
	Aresta e = {u, v, c, 0, FORWARD};
	Aresta er = {v, u, 0, 0, BACKWARD};

	grafo.at(u).push_back(e);
	grafo.at(v).push_back(er);
}
