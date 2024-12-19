#ifndef FLUXOS_REDE_HPP
#define FLUXOS_REDE_HPP

#include "./grafo.hpp"


class FluxoRede : Grafo
{
	private:
				
	public:

		int energiaTotal(); // Capacidade maxima da rede (max flow)
		int energiaNaoAtendida(); // Energia que falta para os consumidores operarem efetivamente
		int energiaPerdida(); // Energia desperdicada ao longo da rede
		vector<Aresta> conexoesCriticas(); // Conexoes que demandam mais energia da rede	

};

#endif
