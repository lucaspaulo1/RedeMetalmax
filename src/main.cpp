#include "../include/grafo.hpp"
#include "../include/fluxoRede.hpp"

#include <iostream>
#include <tuple>
#include <vector>

int main()
{
	int n, m; // Representam o numero de vertices e de arestas, respectivamente
	cin >> n >> m;

	FluxoRede MetalMax = FluxoRede(n, m); // Cria a representacao da Rede de Energia 

	// Energia é desperdiçada ao longo da rede	
	int energiaTotal = MetalMax.energiaTotal();
	cout << energiaTotal << endl;

	// Quantidae de energia que falta para os consumidores operarem efetivamente
	int energiaNaoAtendida = MetalMax.energiaNaoAtendida();
	cout << energiaNaoAtendida << endl;

	// Quantidade de energia que é desperdiçada ao longo da rede
	int energiaPerdida = MetalMax.energiaPerdida();
	cout << energiaPerdida << endl;

	// Conexoes que demandam mais energia da rede 
	vector<tuple<int, int, int>> conexoesCriticas = MetalMax.conexoesCriticas();
	long unsigned int tam = conexoesCriticas.size();
	cout << tam << endl;
	for(auto& t : conexoesCriticas)
	{
		int u = get<0>(t);
		int v = get<1>(t);
		int c = get<2>(t);
		cout << u << " " << v << " " << c << endl;
	}


	return 0;
}


