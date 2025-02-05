# Introdução
Este repositório contém os algoritmos que resolve o problema de fluxo de rede elétrica interna da empresa Metalmax, uma siderúrgica especializada na produção de aço. A rede elétrica interna, composta por
geradores, consumidores e conexões, precisa ser analisada para identificar gargalos e falhas.
Os geradores produzem energia sem restrições, enquanto os consumidores têm demandas específicas e as conexões possuem capacidade limitada.

A análise da rede elétrica da Metalmax abordou quatro questões principais: a capacidade máxima que a rede pode operar, identificando o limite de transmissão de energia
considerando todos os geradores e conexões; a energia não-atendida, calculando a quantidade de energia que falta para que os consumidores operem efetivamente; a energia perdida, determinando quanto de energia não chega aos consumidores devido às limitações das conexões; e as conexões críticas, identificando as conexões que consomem mais energia e que podem ser potenciais pontos de falha na rede elétrica.

O problema foi modelado usando grafos, e resolvido usando algoritmos de fluxo máximo.

# Estrutura do projeto
```
├── include/
│   ├── fluxoRede.hpp
│   ├── grafo.hpp
├── src/
│   ├── fluxoRede.cpp
│   ├── grafo.cpp
│   ├── main.cpp
├── obj/
├── bin/
├── tests/
│   ├── 'Casos de Teste-20241223'/
├── Makefile 
```

Obs: As pastas bin e obj permanecem vazias até que o programa seja compilado.

# Requisitos
Para executar o projeto, é necessário ter:
- Compilador g++ (gcc version 11.4.0)

# Entradas e Saídas
As entradas do programa são feitas via linha de comando.
## Exemplo
Considere a entrada do exemplo a seguir:
```
6 7
1 0
2 20
3 30
4 40
5 50
6 50
1 2 50
1 3 60
1 4 70
1 5 80
1 6 30
2 4 10
5 6 15
```
A primeira linha contém dois números inteiros V e E, onde V é o número de
pontos na rede e E o número de conexões.
Nas próximas V linhas, temos 2 números Vi e T , onde Vi é o identificador do ponto
na rede e T indicando qual o tipo. Se for o caso onde T = 0, então é um gerador.
Mas se T > 0, então é um consumidor e o número indica sua demanda.
Em seguida, temos E linhas contendo 3 números Vi , Vj e C, onde Vi e Vj são dois
identificadores de pontos na rede representando que entre eles existe uma conexão
indo de Vi até Vj que possui capacidade máxima C > 0.

Para essa entrada temos a saı́da:
```
185
5
105
2
1 6 30
5 6 15
```
Temos 3 linhas, cada uma contendo um número referente aos diagnósticos descritos anteriormente.
A primeira, temos ETotal > 0 que é a energia total que a rede comporta.
A segunda, temos EMissing ≥ 0 que é a energia não-atendida.
A terceira, temos ELoss ≥ 0 indicando a energia perdida ao longo da rede.
Na quarta linha, temos um número PCritical indicando quantas conexões crı́ticas
temos na rede. Nas próximas PCritical linhas, temos 3 números Vi , Vj e Eij indicando uma conexão que vai de Vi para Vj 
e está operando em sua capacidade máxima Eij.

# Uso
Dentro do projeto, execute os seguintes comandos para compilar o projeto:
```make clean```
```make all```
O programa será lido pela entrada padrão através de linha de comando, como por exemplo:
```./bin/tp2 < input.txt```
Onde `input.txt` é um arquivo com uma entrada válida dentro.




