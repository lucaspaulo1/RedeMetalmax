#ifndef FLUXO_REDE_HPP
#define FLUXO_REDE_HPP

#include "./grafo.hpp"

using namespace std;

class FluxoRede 
{
	private:
		Grafo g; // Representa a rede modelada como um grafo
		int fluxoEnergia; // Representa o fluxo de energia que pode passar pela rede 
		int demandaTotal; // Representa a demanda total dos consumidores
	public:
		FluxoRede(int n, int m);	
		int energiaTotal(); // Capacidade maxima da rede (max flow)
		int energiaNaoAtendida(); // Energia que falta para os consumidores operarem efetivamente
		int energiaPerdida(); // Energia desperdicada ao longo da rede
		vector<tuple<int, int, int>> conexoesCriticas(); // Conexoes que demandam mais energia da rede	

};

#endif
