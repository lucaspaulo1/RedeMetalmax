#include "../include/grafo.hpp"

#include <iostream>
#include <queue>
#include <stack>
#include <tuple>
#include <vector>

#define INFINITO 0x3f3f3f3f
#define ST 2
#define INVALIDO -1

using namespace std;

Grafo::Grafo(int n) : vertices(n + ST), grafo(n + ST), grafoResidual(n + ST), v_tam(n), fonte(0), vertedouro(n + 1)
{ 
	// Criação de dois vértices artificiais para representar a fonte e o vertedouro em um fluxo 
	Vertice fonteVertice = {fonte, FONTE, INVALIDO}; 
	Vertice vertedouroVertice = {vertedouro, VERTEDOURO, INVALIDO}; // Inserir a fonte e o vertedouro nas posições corretas 
	vertices[fonte] = fonteVertice; 
	vertices[vertedouro] = vertedouroVertice; 
}

void Grafo::addVertice(int u, int t)
{
	TipoVertice tipo;
	Vertice v;
	Aresta e, er; // Aresta que conectara a fonte ao gerador ou o consumidor ao vertedouro e a inversa desta aresta no grafo residual 

	// Verifica o tipo de vertice
	if(t == 0) 
	{
		tipo = GERADOR;
		// Cria uma aresta de capacidade infinita que vai da fonte ao gerador
		e = {fonte, u, INFINITO, 0, ARTF};
		er = {u, fonte, 0, 0, BACKWARD};
		
		grafo.at(fonte).push_back(e);
		grafoResidual.at(fonte).push_back(e);
		grafoResidual.at(u).push_back(er);
	}
	else if(t > 0) 
	{
		tipo = CONSUMIDOR;
		// Cria uma aresta de capacidade 't' que sai do consumidor vai para o vertedouro
		e = {u, vertedouro, t, 0, ARTF}; 
		er = {vertedouro, u, 0, 0, BACKWARD};

		grafo.at(u).push_back(e);
		grafoResidual.at(u).push_back(e);
		grafoResidual.at(vertedouro).push_back(er);
	}

	// Cria e adiciona o vertice
	v = {u, tipo, t};	
	vertices.at(u) = v;
}

void Grafo::addAresta(int u, int v, int c)
{

	// Caso os vertices especificados nao existam
	if(u > v_tam || v > v_tam)
	{
		cout << "Os vertices especificados nao existem!" << endl;
	}

	Aresta e = {u, v, c, 0,  NORMAL};
	Aresta erf = {u, v, c, 0, FORWARD};
	Aresta erb = {v, u, 0, 0, BACKWARD};

	grafo.at(u).push_back(e); // Cria uma aresta para o grafo
	grafoResidual.at(u).push_back(erf); // Cria uma aresta do tipo FORWARD para o grafo residual
	grafoResidual.at(v).push_back(erb); // Cria uma aresta do tipo BACKWARD para o grafo residual

}

void Grafo::consomeEnergia(int u, int e)
{
	vertices.at(u).demanda -= e;
}

bool Grafo::bfs(vector<int> &pais)
{
	queue<pair<int, int>> fila;
	int a;

	fill(pais.begin(), pais.end(), -1); // Limpa o vetor de antecessores
	fila.push({fonte, INFINITO}); 
	pais.at(fonte) = fonte;

	while(!fila.empty())
	{
		int u = fila.front().first;
		int c = fila.front().second;
		fila.pop();


		for(auto& v : grafoResidual.at(u))
		{
			a = verificaAresta(grafoResidual, u, v.v);
			
			if(pais.at(v.v) == -1 && (grafoResidual.at(u).at(a).capacidade - grafoResidual.at(u).at(a).flow > 0))
			{
				pais.at(v.v) = u;
				int novaCap = min(c, grafoResidual.at(u).at(a).capacidade - grafoResidual.at(u).at(a).flow);		
			
				if(v.v == vertedouro) return true;

				fila.push({v.v, novaCap});
			}
		}
	}

	return false;
}


int Grafo::verificaAresta(vector<vector<Aresta>>& g, int u, int v)
{
	int i = 0;
	for(auto& w : g.at(u))
	{
		if(w.v == v) return i;
		i++;
	}

	return INVALIDO;
}

void Grafo::atualizaGrafoResidual()
{
	for(int i = 0; i < v_tam + ST; i++)
	{
		for(auto& v : grafoResidual.at(i))
		{
			//int a = verificaAresta(grafoResidual, i, v.v);
			int b = verificaAresta(grafoResidual, v.v, i);
		
			if(v.flow < 0) 
			{
				v.flow = -v.flow;	
				grafoResidual.at(v.v).at(b).flow = grafoResidual.at(v.v).at(b).capacidade - v.flow;
			}
		}
	}
}

int Grafo::fluxoMaximo()
{
	vector<int> pais(v_tam + ST, -1);
	int maxFlow = 0;
	int u,v;

	int i = 0;
	while(bfs(pais)) // Enquanto existir caminho entre a fonte e o vertedouro
	{
		i++;
		int gargalo = INFINITO;
		
		int a, b, c, d; // Variaveis auxiliares 
		v = vertedouro;

		// Calcula gargalo
		while(v != fonte)
		{
			u = pais.at(v);
			a = verificaAresta(grafoResidual, u, v);
			gargalo = min(gargalo, grafoResidual.at(u).at(a).capacidade - grafoResidual.at(u).at(a).flow);

			v = u;
		}	

		// Atualiza fluxos
		v = vertedouro;
		while(v != fonte)
		{
			u = pais.at(v);
			a = verificaAresta(grafoResidual, u, v);
			b = verificaAresta(grafoResidual, v, u);
			
			consomeEnergia(u, gargalo);

			// Atualiza fluxo
			grafoResidual.at(u).at(a).flow += gargalo;
			grafoResidual.at(v).at(b).flow -= gargalo;

			// Atualiza fluxo do grafo
			c = verificaAresta(grafo, u, v);
			d = verificaAresta(grafo, v, u);
			if(c == INVALIDO && d != INVALIDO) grafo.at(v).at(d).flow -= gargalo;
			else grafo.at(u).at(c).flow += gargalo;

			v = u;
		}
		
		maxFlow += gargalo;
	}

	atualizaGrafoResidual();
	
	return maxFlow;
}

int Grafo::demandaUsada()
{
	int total = 0;

	for(auto& u : vertices) // Para cada vertice
	{
		int i = u.indice;
		
		if(u.tipo != GERADOR) continue; // Caso o vertice nao seja um gerador, parta para o proximo vertice

		// Para cada vizinho do vertice 'i' 
		for(auto& e : grafoResidual.at(i))
		{
			if(vertices.at(e.v).tipo != CONSUMIDOR) continue;
			total += vertices.at(e.v).demanda;		
		}
	}

	return total;
}

int Grafo::capGeradores()
{
	int total = 0;

	for(auto& u : vertices)
	{
		int i = u.indice;
		if(u.tipo != GERADOR) continue;

		for(auto& e : grafoResidual.at(i))
		{
			total += e.capacidade;		
		}
	}

	return total;
}


vector<tuple<int, int, int>> Grafo::arestasCheias()
{
	vector<tuple<int, int, int>> arestas;
	
	for(auto& u : grafo)
	{
		for(auto& v : u)
		{
			tuple<int, int, int> t = make_tuple(v.u, v.v, v.capacidade);

			// Verifica se a aresta nao pertence a fonte ou ao vertedouro , e se ela operando em capacidade maxima
			if(v.capacidade - v.flow == 0 && vertices.at(v.v).tipo == CONSUMIDOR) 
			{
				arestas.push_back(t);
			}
		}
	}

	return arestas;
}

void Grafo::imprime()
{
	int i;
	cout << endl;
	cout << "Grafo: " << endl;
	// Imprime grafo normal
	for(i = 0; i < v_tam + ST; i++)
	{
		cout << "Vertice " << i << " : ";
		for(auto& v : grafo.at(i))
		{
			cout << "[" << v.v << "]" << v.flow << "/" << v.capacidade << "  " ;
		}
		cout << endl;
	}

	cout << endl << "Grafo Residual: " << endl;
	// Imprime grafo residual
	for(int i = 0; i < v_tam + ST; i++)
	{
		cout << "Vertice " << i << " : ";
		for(auto& v : grafoResidual.at(i))
		{
			cout << "[" << v.v << "]" << v.flow << "/" << v.capacidade << "  " ;
		}
		cout << endl;
	}


}

