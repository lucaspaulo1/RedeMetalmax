#include "../include/grafo.hpp"

#include <iostream>
#include <queue>
#include <stack>
#include <vector>

#define INFINITO 0x3f3f3f3f
#define ST 2
#define INVALIDO -1

using namespace std;

Grafo::Grafo(int n)
{
	vertices(n + ST);
	v_tam(n);
	grafo(n + ST);

	int indice_f = 0;
	int indice_v = n + 1;
	Vertice fonte, vertedouro;

	// Criacao de dois vertices artificiais para representar a fonte e o vertedouro em um fluxo
	fonte = {indice_f, FONTE, INVALIDO}; 
	vertedouro = {indice_v, VERTEDOURO, INVALIDO};
	vertices[indive_f] = fonte;
	vertices[indice_v] = vertedouro;
}

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

	grafo.at(u).push_back(e); // Cria uma aresta para o grafo
	grafo.at(v).push_back(er); // Cria uma aresta para o grafo residual
}

bool Grafo::bfs()
{
	vector<int> visitados(v_tam, -1);
	return false;	
}


