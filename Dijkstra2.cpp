#include "stdafx.h"
#include "conio.h"

typedef struct no{   
	int custo;
	int anterior;
	int visitado;
}No;
/*
* Estrutura de dados utilizada para representar o grafo, onde "custo" guardará o valor
* do  menor  caminho encontrado até o nó em  questão, "anterior" guardará a referência
* (índice) do nó imediatamente anterior  a  cada um dos nós do grafo,  ou -1 para o nó 
* inicial, e "visitado" fará o papel de "S barra". A  cada  iteração  um  dos nós terá 
* o seu valor alterado de 0 (zero), que  indica  que  ele está em S barra, para 1, que 
* indica que já foi encontrado  o  menor  caminho  até  este nó,  e  portanto ele pode 
* receber o valor 1 e passar para o conjunto S.
*/

No GRAFO[10];
int MATRIZ[10][10]; //Matriz utilizada para guardar as informações referentes ao grafo
					//onde a linha da matriz representa o nó  origem,  a  coluna  o nó 
					//destino e a intersecção entre elas, o custo do arco.
int No_Selecionado;
int INFINITO = 32766;
int destino;
int qtd_nos;


//Protótipos das funções utilizadas neste algoritmo.
//Suas explicações detalhadas encontram nas próprias funções, logo após a função main()
void inicializa_variaveis();
int visita();
void encontra_Menor(int x);
void gera_grafo(int a, int b, int c);
void imprime_Menor_Caminho();


void main()
{

/* Esta é a função principal do algoritmo, sua função é apenas controlar a chamada das
*  funções específicas de seleção e cálculo para definição do menor caminho do grafo.
*  Além  deste  controle, é  aqui onde as informações, como quantidade e custo dos nós
*  do grafo são inseridas.
*/ 

		//chamada à função de inicialização de todas as variáveis do grafo
		inicializa_variaveis(); 
		

	/*No trecho de código abaixo, são solicitadas ao usuário as informações à respeito
	* do grafo, o  usuário deve inserir uma linha contendo três inteiros separados por 
	* um  espaço,  onde  o  primeiro  item  corresponde  ao  nó origem, o segundo item 
	* corresponde ao  nó destino, e o terceiro item corresponde aó custo do arco entre
	* estes dois nós. Para terminar a inserção deve-se inserir a linha 0 0 0.
	*/
	int k, l, m;
	printf("\n\nInsira os dados do grafo, no formato x y z onde: \n"); 
	printf("x= origem, y=destino, z=custo. Insira 0 0 0 para finalizar. \n\n");
	do
	{
		scanf("%d %d %d", &k, &l, &m);
			gera_grafo(k, l, m);
			// chama a  função que insere os dados na matriz que representa o grafo, 
			// tantas vezes quantas forem o número de arcos (este número dobra se os
			// arcos forem não direcionados.)
	}while ((k + l) != 0);


	/*Terminada a inserção dos dados na matriz, iniciam-se os cálculos para encontrar 
	* o menor caminho,  é  realizado  um laço, que se repete enquanto as condições de 
	* parada  não forem atendidas, a cada iteração é encontrado o caminho mínimo para
	* um  dos  nós ainda não visitado, e este processo se repete até que todos os nós
	* sejam visitados e portanto o caminho mínimo seja encontrado.
	*/
	do
	{
	encontra_Menor(No_Selecionado);
	}while (visita() != 0);

	
	/* Neste ponto do código, o menor caminho já foi encontrado e apenas é feita uma 
	* chamada à função de impressão, que ira mostrar os custos mínimos e respectivos 
	* caminhos, para todos os nós do grafo.
	*/
	imprime_Menor_Caminho();
getch();//A função getch() serve apenas para pausar o programa, para que  o  usuário 
	    //possa ver os resultados, sem que ele se encerre automaticamente.
}

void inicializa_variaveis()
{
//EQUIVALENTE AO PASSO 1 - Inicialização das variáveis.
	printf("Insira a quantidade de nos: \n");
		scanf("%d", &qtd_nos);
	int i, j;
	for (i=0; i<10; i++)
	  for(j=1; j<10; j++)
	    MATRIZ[i][j] = -1;
		//preenche a Matriz com -1, o que indica que nenhum dado à respeito dos nós do
		//grafo foi inserida.
	for (i=0; i<10; i++)
	{	
		GRAFO[i].anterior = -1;
		//Atribuindo -1 para o antecessor de todos os nós do grafo, indicamos que ainda
		//não foi encontrado o menor camiho para nenhum destes nós.
		GRAFO[i].visitado = 0;
		//Como nenhum nó foi visitado, todos recebem o valor 0.
		GRAFO[i].custo = INFINITO;
		//todos os nós recebem custo infinito.
	}
	//Selecionamos  o  nó  origem,  e  definimos  que o custo mínimo para ele é 0(zero)
	//pois  ele  é  o  primeiro  nó  de  todos  os  caminhos. Como ele já tem seu valor 
	//mínimo  definido, o marcamos  como  visitado, ou  seja seria o mesmo que passá-lo
	//para o conjunto S.
	GRAFO[0].custo = 0; 
	GRAFO[0].visitado = 1;
}


int visita()
{
//EQUIVALENTE AO PASSO 2 - Escolha do nó//
/*Esta  função  tem  o  objetivo de encontrar o vértice com menor caminho para um 
* determinado  sucessor, dentre  os  vértices  que  ainda não foram visitados, ou 
* seja, seleciona-se o no com menor custo que esteja dentro do conjunto "S barra"
* feita  esta  escolha, atribui-se  o  valor 1 para o nó escolhido, o controle do 
* programa passa para a função encontra_Menor(), que irá  verificar  os  custos e 
* efetuar possíveis atualizações de valores. Além disso esta função  sinaliza  ao
* programa principal se existem ou não nós a serem visitados,  ou seja,  se ainda
* existem elementos em "S barra".
*/
int j, min, vazio;
j=0;
min = INFINITO;
vazio = 1;	

	for(int i=1; i<10; i++)
	{
		if (GRAFO[i].visitado == 0)
		{
			if (min > GRAFO[i].custo)
			{
				min = GRAFO[i].custo;
				No_Selecionado = i;
			}
		}
	}
	
	GRAFO[No_Selecionado].visitado = 1;

	
	/* 
	* O trecho de código abaixo serve para sinalizar à função principal  se  ainda
	* existem nós a serem visitados, ele funciona da seguinte maneira: percorre-se
	* o vetor que guarda os nós, e multiplica-se todas as váriáveis "visitado", 
	* das estrutura, como é um valor binário (0 ou 1), ele só será 1, quando todos
	* os nós possuírem valor 1, do contrário uma multiplicação por 0, indicará que 
	* ainda existem nós a serem visitados, portanto a função principal continua no
	* laço.
	*/
	for(int i=0; i<qtd_nos; i++)
	{
		vazio = (vazio * GRAFO[i].visitado);
	}

	if (vazio == 0)
		return 1;
	else 
		return 0;
}


void encontra_Menor(int x)
{
//EQUIVALENTE AO PASSO 3 - Calculo do custo do caminho//
/* Após um nó ter sido escolhido pela  função  visita(),  serão  feitas  as  comparações
* e possíveis atualizações dos valores  dos  custos  deste  nó,  esta é a talvez a parte 
* mais importante do código, pois é aqui  onde  são  realmente  armazenados  os  menores 
* custos para cada vértice, e por conseqüência para todos os nós do grafo.
* Tomando por base o nó  que  foi  selecionado,  utiliza-se  a  matriz  para  determinar
* se o custo atual, (que é formado pelo custo de seu antecessor somado ao custo do arco)
* é menor que o custo que este nó possui, nas primeiras iterações, estes valores serão o
* Infinito para vários nós, ou seja, a substituição irá com  certeza  ocorrer. Mas  esta 
* atualização pode ocorrer novamente mais  à  frente, quando  um  novo (e menor) caminho
* possivelmente seja encontrado. Desta maneira ao fim das iterações todos os nós estarão
* com seus custos mínimos armazenados, e com isso temos o custo mínimo para todos os nós
* deste grafo.
* Resumindo: esta função verifica todos os  nós  adjacentes a um nó selecionado e guarda 
* o custo para este nó se ele for menor que o  custo que ele já possuía, além disso, ela
* guarda a referência para o nó antecessor de  cada  um  que  teve  seu  camihno  mínimo 
* encontrado.
*/

	for(int y=0; y<10; y++)
	{
		if (MATRIZ[x][y] > -1)
		  if ((GRAFO[y].custo) > (GRAFO[x].custo + MATRIZ[x][y]))
			{
				GRAFO[y].custo = (GRAFO[x].custo + MATRIZ[x][y]);
				GRAFO[y].anterior = x;
			}
	}
}

void gera_grafo(int a, int b, int c)
{
/* Esta  função  recebe  os  valores da entrada  do usuário e os  coloca  na  matriz  que 
* representa o grafo, sendo linha=origem, coluna=destino e intersecção=custo.
* Se  as  informações  inseridas  forem  sobre  o  nó  inicial  0(zero),   já  atribui-se 
* os custos para os nós adjacentes a ele como sendo o valor do prórpio arco.
* Podemos   fazer   esta   atribuição   pois   o   nó   incial   tem   custo  0, ou  seja 
* 0+arco = arco, e o antecessor dos adjacentes também já é conhecido, e pode ser definido
* no caso, é também o nó inicial.O único caso em que não faremos esta atribuição é quando 
* o nó inicial e final forem igual a 0 (zero),  pois do contrário o nó zero teria custo 0 
* e antecessor 0, mas o antecessor de 0 deve ser -1, mantendo-se o valor da inicialização
* geral  das  variáveis, porque o nó inicial não deve ter antecessor, e sim ter  um valor 
* nulo, no caso o -1. Isto também será necessário no momento  a  impressão  dos caminhos, 
* pois a condição de parada da impressão é que o antecessor seja = -1.
*/

	MATRIZ[a][b] = c;
	if ((a==0) && (b != 0))
	{
		GRAFO[b].custo = c; 
		GRAFO[b].anterior = a;
	}
}


void imprime_Menor_Caminho()
{ 
/*Esta função serve para imprimir o resultado encontrado para os menores caminhos do grafo
*ela imprime os custos mínimos de cada nó, bem como o caminho que deve ser percorrido para
*alcançar estes nós.  A função imprime o caminho da seguinte maneira, para cada vertice, é
*é impresso seu antecessor e a variável responsável por esta informação recebe o valor  do
*próximo antecessor, fazendo isto dentro de uma  estrutura  de  repetição,  até  que  seja
*encontrado  o  antecessor  -1,  o  que significa  que  o  nó  inicial  foi  alcançado,  e
*portanto  o  caminho  está  completo. O caminho deve ser lido da direita para a esquerda.
*/
	printf("\n\n");
	int i;
	for (i =0; i<qtd_nos; i++)
	{
		int dest = i;
		printf("Custo minimo ate o no %d: %d    Caminho: ", dest, GRAFO[dest].custo);
		do	
		{
			printf("%d ", dest);
			dest = GRAFO[dest].anterior;
		}while (dest != -1);
		printf("\n");
	}


}
