#include "../include/grafo.hpp"
#include "../include/fluxoRede.hpp"

#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

FluxoRede::FluxoRede(int n, int m) : g(n) 
{
	int u, v, t, c;
	demandaTotal = 0;

	// Leitura das entradas
	for(int i = 0; i < n; i++)
	{
		cin >> u >> t; // Le o identificador do ponto na rede e o tipo do ponto
		g.addVertice(u, t); // Adiciona o novo ponto na rede
		demandaTotal += t; // Soma as demandas dos consumidores
	}

	for(int i = 0; i < m; i++)
	{
		cin >> u >> v >> c; // Le os pontos e a capacidade da aresta na rede
		g.addAresta(u, v, c); // Adiciona a conexao na rede
	}

	fluxoEnergia = g.fluxoMaximo(); // Calcula os fluxos no grafo
}

int FluxoRede::energiaTotal()
{
	return fluxoEnergia;
}

int FluxoRede::energiaNaoAtendida()
{
	return demandaTotal - fluxoEnergia; 
}

int FluxoRede::energiaPerdida()
{
	return g.capGeradores() - fluxoEnergia;
}

// Funcao para inverter um vector
void inverterVector(vector<tuple<int, int, int>>& vec) 
{
	int n = (int) vec.size();
	for (int i = 0; i < n / 2; ++i) 
	{
		// Troca os elementos simétricos
		swap(vec[i], vec[n - 1 - i]);
	}
}


// Funcao para mesclar dois subvetores ordenados pelo terceiro elemento em ordem decrescente
void merge(vector<tuple<int, int, int>>& vec, int esquerda, int meio, int direita) 
{
	int n1 = meio - esquerda + 1;
	int n2 = direita - meio;

	vector<tuple<int, int, int>> L(n1);
	vector<tuple<int, int, int>> R(n2);

	for (int i = 0; i < n1; ++i)
		L[i] = vec[esquerda + i];
	for (int j = 0; j < n2; ++j)
		R[j] = vec[meio + 1 + j];

	int i = 0, j = 0, k = esquerda;
	while (i < n1 && j < n2) {
		if (get<2>(L[i]) >= get<2>(R[j])) {
			vec[k] = L[i];
			++i;
		} else {
			vec[k] = R[j];
			++j;
		}
		++k;
	}

	while (i < n1) {
		vec[k] = L[i];
		++i;
		++k;
	}

	while (j < n2) {
		vec[k] = R[j];
		++j;
		++k;
	}
}

// Função recursiva do Merge Sort
void mergeSort(vector<tuple<int, int, int>>& vec, int esquerda, int direita) 
{
	if (esquerda < direita) {
		int meio = esquerda + (direita - esquerda) / 2;

		mergeSort(vec, esquerda, meio);
		mergeSort(vec, meio + 1, direita);

		merge(vec, esquerda, meio, direita);
	}

}



vector<tuple<int, int, int>> FluxoRede::conexoesCriticas()
{
	vector<tuple<int, int, int>> arestas = g.arestasCheias();
	int tam = (int) arestas.size() - 1;

	// Ordena o vetor em ordem decescente
	mergeSort(arestas, 0, tam);
	
	// Inverte o vetor para ordem decrescente
	// inverterVector(arestas); 

	return arestas;
}


