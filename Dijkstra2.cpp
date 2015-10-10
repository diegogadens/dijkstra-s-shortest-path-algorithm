#include "stdafx.h"
#include "conio.h"

typedef struct no{   
	int custo;
	int anterior;
	int visitado;
}No;
/*
* Estrutura de dados utilizada para representar o grafo, onde "custo" guardar� o valor
* do  menor  caminho encontrado at� o n� em  quest�o, "anterior" guardar� a refer�ncia
* (�ndice) do n� imediatamente anterior  a  cada um dos n�s do grafo,  ou -1 para o n� 
* inicial, e "visitado" far� o papel de "S barra". A  cada  itera��o  um  dos n�s ter� 
* o seu valor alterado de 0 (zero), que  indica  que  ele est� em S barra, para 1, que 
* indica que j� foi encontrado  o  menor  caminho  at�  este n�,  e  portanto ele pode 
* receber o valor 1 e passar para o conjunto S.
*/

No GRAFO[10];
int MATRIZ[10][10]; //Matriz utilizada para guardar as informa��es referentes ao grafo
					//onde a linha da matriz representa o n�  origem,  a  coluna  o n� 
					//destino e a intersec��o entre elas, o custo do arco.
int No_Selecionado;
int INFINITO = 32766;
int destino;
int qtd_nos;


//Prot�tipos das fun��es utilizadas neste algoritmo.
//Suas explica��es detalhadas encontram nas pr�prias fun��es, logo ap�s a fun��o main()
void inicializa_variaveis();
int visita();
void encontra_Menor(int x);
void gera_grafo(int a, int b, int c);
void imprime_Menor_Caminho();


void main()
{

/* Esta � a fun��o principal do algoritmo, sua fun��o � apenas controlar a chamada das
*  fun��es espec�ficas de sele��o e c�lculo para defini��o do menor caminho do grafo.
*  Al�m  deste  controle, �  aqui onde as informa��es, como quantidade e custo dos n�s
*  do grafo s�o inseridas.
*/ 

		//chamada � fun��o de inicializa��o de todas as vari�veis do grafo
		inicializa_variaveis(); 
		

	/*No trecho de c�digo abaixo, s�o solicitadas ao usu�rio as informa��es � respeito
	* do grafo, o  usu�rio deve inserir uma linha contendo tr�s inteiros separados por 
	* um  espa�o,  onde  o  primeiro  item  corresponde  ao  n� origem, o segundo item 
	* corresponde ao  n� destino, e o terceiro item corresponde a� custo do arco entre
	* estes dois n�s. Para terminar a inser��o deve-se inserir a linha 0 0 0.
	*/
	int k, l, m;
	printf("\n\nInsira os dados do grafo, no formato x y z onde: \n"); 
	printf("x= origem, y=destino, z=custo. Insira 0 0 0 para finalizar. \n\n");
	do
	{
		scanf("%d %d %d", &k, &l, &m);
			gera_grafo(k, l, m);
			// chama a  fun��o que insere os dados na matriz que representa o grafo, 
			// tantas vezes quantas forem o n�mero de arcos (este n�mero dobra se os
			// arcos forem n�o direcionados.)
	}while ((k + l) != 0);


	/*Terminada a inser��o dos dados na matriz, iniciam-se os c�lculos para encontrar 
	* o menor caminho,  �  realizado  um la�o, que se repete enquanto as condi��es de 
	* parada  n�o forem atendidas, a cada itera��o � encontrado o caminho m�nimo para
	* um  dos  n�s ainda n�o visitado, e este processo se repete at� que todos os n�s
	* sejam visitados e portanto o caminho m�nimo seja encontrado.
	*/
	do
	{
	encontra_Menor(No_Selecionado);
	}while (visita() != 0);

	
	/* Neste ponto do c�digo, o menor caminho j� foi encontrado e apenas � feita uma 
	* chamada � fun��o de impress�o, que ira mostrar os custos m�nimos e respectivos 
	* caminhos, para todos os n�s do grafo.
	*/
	imprime_Menor_Caminho();
getch();//A fun��o getch() serve apenas para pausar o programa, para que  o  usu�rio 
	    //possa ver os resultados, sem que ele se encerre automaticamente.
}

void inicializa_variaveis()
{
//EQUIVALENTE AO PASSO 1 - Inicializa��o das vari�veis.
	printf("Insira a quantidade de nos: \n");
		scanf("%d", &qtd_nos);
	int i, j;
	for (i=0; i<10; i++)
	  for(j=1; j<10; j++)
	    MATRIZ[i][j] = -1;
		//preenche a Matriz com -1, o que indica que nenhum dado � respeito dos n�s do
		//grafo foi inserida.
	for (i=0; i<10; i++)
	{	
		GRAFO[i].anterior = -1;
		//Atribuindo -1 para o antecessor de todos os n�s do grafo, indicamos que ainda
		//n�o foi encontrado o menor camiho para nenhum destes n�s.
		GRAFO[i].visitado = 0;
		//Como nenhum n� foi visitado, todos recebem o valor 0.
		GRAFO[i].custo = INFINITO;
		//todos os n�s recebem custo infinito.
	}
	//Selecionamos  o  n�  origem,  e  definimos  que o custo m�nimo para ele � 0(zero)
	//pois  ele  �  o  primeiro  n�  de  todos  os  caminhos. Como ele j� tem seu valor 
	//m�nimo  definido, o marcamos  como  visitado, ou  seja seria o mesmo que pass�-lo
	//para o conjunto S.
	GRAFO[0].custo = 0; 
	GRAFO[0].visitado = 1;
}


int visita()
{
//EQUIVALENTE AO PASSO 2 - Escolha do n�//
/*Esta  fun��o  tem  o  objetivo de encontrar o v�rtice com menor caminho para um 
* determinado  sucessor, dentre  os  v�rtices  que  ainda n�o foram visitados, ou 
* seja, seleciona-se o no com menor custo que esteja dentro do conjunto "S barra"
* feita  esta  escolha, atribui-se  o  valor 1 para o n� escolhido, o controle do 
* programa passa para a fun��o encontra_Menor(), que ir�  verificar  os  custos e 
* efetuar poss�veis atualiza��es de valores. Al�m disso esta fun��o  sinaliza  ao
* programa principal se existem ou n�o n�s a serem visitados,  ou seja,  se ainda
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
	* O trecho de c�digo abaixo serve para sinalizar � fun��o principal  se  ainda
	* existem n�s a serem visitados, ele funciona da seguinte maneira: percorre-se
	* o vetor que guarda os n�s, e multiplica-se todas as v�ri�veis "visitado", 
	* das estrutura, como � um valor bin�rio (0 ou 1), ele s� ser� 1, quando todos
	* os n�s possu�rem valor 1, do contr�rio uma multiplica��o por 0, indicar� que 
	* ainda existem n�s a serem visitados, portanto a fun��o principal continua no
	* la�o.
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
/* Ap�s um n� ter sido escolhido pela  fun��o  visita(),  ser�o  feitas  as  compara��es
* e poss�veis atualiza��es dos valores  dos  custos  deste  n�,  esta � a talvez a parte 
* mais importante do c�digo, pois � aqui  onde  s�o  realmente  armazenados  os  menores 
* custos para cada v�rtice, e por conseq��ncia para todos os n�s do grafo.
* Tomando por base o n�  que  foi  selecionado,  utiliza-se  a  matriz  para  determinar
* se o custo atual, (que � formado pelo custo de seu antecessor somado ao custo do arco)
* � menor que o custo que este n� possui, nas primeiras itera��es, estes valores ser�o o
* Infinito para v�rios n�s, ou seja, a substitui��o ir� com  certeza  ocorrer. Mas  esta 
* atualiza��o pode ocorrer novamente mais  �  frente, quando  um  novo (e menor) caminho
* possivelmente seja encontrado. Desta maneira ao fim das itera��es todos os n�s estar�o
* com seus custos m�nimos armazenados, e com isso temos o custo m�nimo para todos os n�s
* deste grafo.
* Resumindo: esta fun��o verifica todos os  n�s  adjacentes a um n� selecionado e guarda 
* o custo para este n� se ele for menor que o  custo que ele j� possu�a, al�m disso, ela
* guarda a refer�ncia para o n� antecessor de  cada  um  que  teve  seu  camihno  m�nimo 
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
/* Esta  fun��o  recebe  os  valores da entrada  do usu�rio e os  coloca  na  matriz  que 
* representa o grafo, sendo linha=origem, coluna=destino e intersec��o=custo.
* Se  as  informa��es  inseridas  forem  sobre  o  n�  inicial  0(zero),   j�  atribui-se 
* os custos para os n�s adjacentes a ele como sendo o valor do pr�rpio arco.
* Podemos   fazer   esta   atribui��o   pois   o   n�   incial   tem   custo  0, ou  seja 
* 0+arco = arco, e o antecessor dos adjacentes tamb�m j� � conhecido, e pode ser definido
* no caso, � tamb�m o n� inicial.O �nico caso em que n�o faremos esta atribui��o � quando 
* o n� inicial e final forem igual a 0 (zero),  pois do contr�rio o n� zero teria custo 0 
* e antecessor 0, mas o antecessor de 0 deve ser -1, mantendo-se o valor da inicializa��o
* geral  das  vari�veis, porque o n� inicial n�o deve ter antecessor, e sim ter  um valor 
* nulo, no caso o -1. Isto tamb�m ser� necess�rio no momento  a  impress�o  dos caminhos, 
* pois a condi��o de parada da impress�o � que o antecessor seja = -1.
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
/*Esta fun��o serve para imprimir o resultado encontrado para os menores caminhos do grafo
*ela imprime os custos m�nimos de cada n�, bem como o caminho que deve ser percorrido para
*alcan�ar estes n�s.  A fun��o imprime o caminho da seguinte maneira, para cada vertice, �
*� impresso seu antecessor e a vari�vel respons�vel por esta informa��o recebe o valor  do
*pr�ximo antecessor, fazendo isto dentro de uma  estrutura  de  repeti��o,  at�  que  seja
*encontrado  o  antecessor  -1,  o  que significa  que  o  n�  inicial  foi  alcan�ado,  e
*portanto  o  caminho  est�  completo. O caminho deve ser lido da direita para a esquerda.
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
