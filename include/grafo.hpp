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
	FONTE = -2,
	VERTEDOURO = -1,
	GERADOR = 0,
	CONSUMIDOR = 1
};

/*
 * Enum para representar o tipo do ponto da aresta do grafo e do grafo residual
 */
enum TipoAresta
{
	NORMAL, // Arestas do grafo normal (nao eh o grafo residual)
	FORWARD, // Arestas na direcao da fonte ao vertedouro no grafo residual
	BACKWARD, // Arestas na direcao contraria da fonte ao vertedouro no grafo residual
	ARTF // Arestas 'artificiais' da fonte aos geradores ou dos consumidores ao vertedouro
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
		vector<vector<Aresta>> grafo; // Vetor de conexoes(arestas) para reprentar a rede
		vector<vector<Aresta>> grafoResidual; // Vetor de conexoes(arestas) para representar o grafo residual

		int v_tam; // Tamanho do vetor de vertices
		int fonte; // Representa o indice do vertice fonte (vertice por onde sai o fluxo) 
		int vertedouro; // Representa o indice do vertice vertedouro(vertice para onde o fluxo vai)
		
		int garg; // Representa o fluxo atual da rede
		int energiaRequerida;

	public:
		Grafo(int n); // Metodo construtor
		void addVertice(int u, int t); // Adiciona ponto(vertice) na rede 
		void addAresta(int u, int v, int c); // Adiciona conexao(aresta) a rede(grafo)
		int verificaAresta(int u, int v); // Verifica se a aresta 'u' existe em 'v'		
		
		void consomeEnergia(int u, int e); // Consome a energia 'e' que entra no vertice 'u'
		bool bfs(vector<int>& pais); // Verifica se ha um caminho aumentante
		int fluxoMaximo(); // Calcula o fluxo maximo da rede

		void imprime(); // Imprime os grafos		
};

#endif
