#include "../include/grafo.hpp"
#include "../include/fluxosRede.hpp"

#include <iostream>
#include <vector>


int main()
{
	int n, m; // Representam o numero de vertices e de arestas, respectivamente
	int u, v, t, c;

	// Leitura das entradas
	cin >> n >> m;
	
	Grafo g = Grafo(n);

	for(int i = 0; i < n; i++)
	{
		cin >> u >> t; // Le o identificador do ponto na rede e o tipo do ponto
		g.addVertice(u, t); // Adiciona o novo ponto na rede
	}

	for(int i = 0; i < m; i++)
	{
		cin >> u >> v >> c; // Le os pontos e a capacidade da aresta na rede
		g.addAresta(u, v, c); // Adiciona a conexao na rede
	}

	return 0;
}


