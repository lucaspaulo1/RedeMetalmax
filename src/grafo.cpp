#include "../include/grafo.hpp"

#include <iostream>
#include <queue>
#include <stack>
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
		// Cria uma aresta de capacidade infinita que sai do consumidor vai para o vertedouro
		e = {u, vertedouro, INFINITO, 0, ARTF}; 
		er = {vertedouro, u, 0, 0, BACKWARD};

		grafo.at(u).push_back(e);
		grafoResidual.at(u).push_back(e);
		grafoResidual.at(vertedouro).push_back(er);
	}

	cout << "tipo: " << tipo << endl;
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
	cout << "antiga demaanda: " << vertices.at(u).demanda << endl;
	vertices.at(u).demanda -= e;
	cout << "nova demaanda: " << vertices.at(u).demanda << endl;
	
}

bool Grafo::bfs(vector<int>& pais)
{
	vector<bool> visitados(v_tam + ST, false);
	queue<int> fila;
	
	fila.push(fonte); 
	visitados.at(fonte) = true;
	pais.at(fonte) = INVALIDO;
	

	while(!fila.empty())
	{
		int u = fila.front();
		fila.pop();


		for(auto& v : grafoResidual.at(u))
		{
			// Verifica se o vertice foi visitado, se ele tem demanda e se existe uma aresta com capacidade sufiente  
			if(!visitados.at(v.v) && v.capacidade > 0 && (vertices.at(v.v).demanda > 0 || vertices.at(v.v).tipo == GERADOR || vertices.at(v.v).tipo == VERTEDOURO) )
			{
				
				if(v.v == vertedouro) 
				{
					pais.at(v.v) = u;
					return true;
				}

				fila.push(v.v);
				pais.at(v.v) = u;
				visitados.at(v.v) = true;
			}
		}
	}
	
	return false;
}

int Grafo::verificaAresta(int u, int v)
{
	int i = 0;
	for(auto& w : grafoResidual.at(u))
	{
		if(w.v == v) return i;
		i++;
	}

	return INVALIDO;
}

int Grafo::fluxoMaximo()
{
	int u, v;
	vector<int> pais(v_tam + ST);
	int maxFlow = 0;

	while(bfs(pais)) // Enquanto existir caminho entre a fonte e o vertedouro
	{
		int gargalo = INFINITO;
		int a, b, energia;

		cout << "KKKKKKKKKKKK" << endl;

		// Econtrar o gargalo da caminho minimo aumentatnte
		for(v = vertedouro; v != fonte; v = pais.at(v))
		{
			u = pais.at(v);
			cout << "\n\nu: " << u << "\nv: " << v << endl;
		
			// Procura o vertice 'v' na lista de adjcancia de 'u'
			a = verificaAresta(u, v);
			if(a == INVALIDO) cout << "Aresta de [" << u << "] para [" << v << "] nao existe!" << endl;
			
			// Calcula o gargalo da caminho aumentante
			//if(u == vertedouro) continue;
			energia = vertices.at(v).demanda; // calcula a demanda de energia do vertice 'v'
			gargalo = min(energia, grafoResidual.at(u).at(a).capacidade); // Calcula o minimo entre a capacidade da aresta e do vertice
			consomeEnergia(u, gargalo); // Consome a energia que chega no vertice
			cout << "Gargalo: " << garg << endl;
		}

		// Atualizar grafo residual
		for(v = vertedouro; v != fonte; v = pais.at(v))
		{
			u = pais.at(v);
		
			// Procura o vertice 'v' na lista de adjacencia de 'u'	
			a = verificaAresta(u, v);
			b = verificaAresta(v, u);
			if(a == INVALIDO) cout << "Aresta de [" << u << "] para [" << v << "] nao existe!" << endl;
			if(b == INVALIDO) cout << "Aresta de [" << v << "] para [" << u << "] nao existe!" << endl;


			// Atualiza o fluxo no caminho aumentante
			grafoResidual.at(u).at(a).flow += gargalo;
			grafoResidual.at(u).at(a).capacidade -= gargalo;
			
			grafoResidual.at(v).at(b).capacidade += gargalo;
		}

		maxFlow += gargalo; // Atualiza fluxo maximo
	}

	return maxFlow;
}

void Grafo::imprime()
{
	int i;
	cout << endl;
	cout << "Grafo: " << endl;
	for(i = 0; i < v_tam + ST; i++)
	{
		cout << "Vertice " << i << " : ";
		for(auto& v : grafo.at(i))
		{
			if(v.tipo == NORMAL || v.tipo == ARTF) cout << "(" << v.v << " - " << v.flow << "|" << v.capacidade << ")" << " ";
		}
		cout << endl;
		//i++;
	}

	cout << endl << "Grafo Residual: " << endl;
	for(int i = 0; i < v_tam + ST; i++)
	{
		cout << "Vertice " << i << " : ";
		for(auto& v : grafoResidual.at(i))
		{
			if((v.tipo == FORWARD && v.capacidade > 0) || v.tipo == ARTF) cout << "(" << v.v << "F" << " - " << v.flow << "|" << v.capacidade << ")" << " ";
			if((v.tipo == BACKWARD && v.capacidade > 0) || v.tipo == ARTF) cout << "(" << v.v << "C" << " - " << v.flow << "|" << v.capacidade << ")" << " ";
		}
		cout << endl;
	}


}

