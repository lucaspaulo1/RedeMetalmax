#ifndef GRAFO_HPP
#define GRAFO_HPP


#include <iostream>
#include <vector>

using namespace std;


/*
 * Enum para representar o tipo do ponto da rede(gerador ou consumidor)
 */
enum TipoVertice
{
	FONTE = -1,
	VERTEDOURO = -2,
	GERADOR,
	CONSUMIDOR
};

/*
 * Enum para representar o tipo do ponto da aresta do grafo e do grafo residual
 */
enum TipoAresta
{
	FORWARD,
	BACKWARD
};


/*
 * Struct para representar um ponto na rede, ou seja, um vertice no grafo
 */
struct Vertice
{
	int indice; // Numero que representa o vertice
	TipoVertice tipo; // Tipo que o vertice representa na rede (grafo)
	int demanda; // Demanda de energia associada ao ponto da rede
};

/*
 * Struct para representar uma conexao na rede, ou seja, uma aresta no grafo
 */
struct Aresta
{
	int u; // Vertice de saida da aresta
	int v; // Vertice de entrada da aresta
	int capacidade; // Representa a capacidade(energia) da aresta
	int flow; // Representa o fluxo(energia) que sai do vertice 'u' e vai para o 'v'
	TipoAresta tipo; // Representa a aresta do grafo normal e do grafo residual
};

/*
 * Classe que representa a rede, mas modelada como um grafo
 */
class Grafo
{
	private:
		vector<Vertice> vertices; // Vetor de vertices para representar os pontos da rede
		int v_tam; // Tamanho do vetor de vertices
		vector<vector<Aresta>> grafo;

	public:
		Grafo(int n); // Metodo construtor
		void addVertice(int u, int t); // Adiciona ponto(vertice) na rede 
		void addAresta(int u, int v, int c); // Adiciona conexao(aresta) a rede(grafo)
		
		bool bfs(); // Verifica se ha um caminho aumentante
		int enviaFlow(int s, int t, int flow, int path[]); // Envia fluxo ao longo do caminho encontrado
		
};

#endif
