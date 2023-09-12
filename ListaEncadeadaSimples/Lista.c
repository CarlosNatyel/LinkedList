/*
Listas encadeadas são estruturas de dados que permitem armazenar uma coleção
 de elementos de um mesmo tipo.

Neste arquivo, temos a implementação de uma lista encadeada simples de inteiros.
*/

#include "lista.h"

struct lista //definição da estrutura da lista
{
	int info; //armazena um valor inteiro
	struct lista *prox; //ponteiro para o proximo elemento da lista
};

Lista *lst_cria(void)//função para criar uma lista vazia
{
	return NULL;//retorna um ponteiro nulu indicando que a lista esta vazia
}

Lista *lst_insere(Lista *l, int v)//função para inserir um elemento no inicio da lista 
{
	Lista *novo = (Lista *)malloc(sizeof(Lista));//aloca memoria para um novo valor da lista
	if (novo == NULL)//caso o novo valor seja nulo
	{
		printf("[ERRO] memoria insuficiente!");//informa ao usuario que tenha erro
		exit(1);//aborta a execução
	}
	novo->info = v;//define o valor do novo elemento
	novo->prox = l;//o novo elemento aponta para o antigo inicio da lista
	return novo;//retorna o novo inicio da lista

	/* Ou para alterar diretamente

	void lst_insere(Lista** t, int v){
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->info = v;
	novo->prox = *t;
	*t = novo; */
}

int lst_vazia(Lista *l)//função para verificar se a lista ta vazia 
{
	return (l == NULL);
}

void lst_imprime(Lista *l)//função para imprimir os elementos da lista
{
	Lista *p;
	for (p = l; p != NULL; p = p->prox)//loop percorre a lista a partir do inicio p=l até o final P!=NULL
	{
		printf("\tInfo = %d \n", p->info);
	}
}

Lista *lst_busca(int elemento, Lista *l)//Função para buscar um elemento na lista
{
	Lista *p;
	for (p = l; p != NULL; p = p->prox)//loop percorre a lista a partir do inicio p=l até o final P!=NULL
	{
		if (p->info == elemento)// se o elemento armazenado no nó atual for igual ao (elemento) desejado,retorna o ponteiro para esse nó
			return p;//retorna o ponteiro para o elemento encontrado
	}

	return NULL;
}

Lista *lst_retira(Lista *l, int v)//função para tirar um elemento da lista
{
	Lista *ant = NULL; /* ponteiro para elemento anterior */
	Lista *p = l;	   /* ponteiro para percorrer a lista*/
	/* procura elemento na lista, guardando anterior */
	while (p->info != v)
	{
		if (p == NULL)
			return l; /* nao achou: retorna lista original */
		ant = p;
		p = p->prox;
		/* verifica se achou elemento */
	}
	/* retira elemento */
	if (ant == NULL)
		/* retira elemento do inicio */
		l = p->prox;
	else
		/* retira elemento do meio da lista */
		ant->prox = p->prox;
	free(p);//função para tirar um elemento da lista
	return l;
}

void lst_libera(Lista *l)//função para liberar a memoria alocada pela lista
{
	Lista *p = l;
	Lista *t;
	while (p != NULL)
	{
		t = p->prox;
		free(p);//libera a memoria do elemento atual
		p = t;
	}
}

Lista *lst_insere_ordenada(Lista *l, int v)
{
	Lista *novo;
	Lista *ant = NULL;
	Lista *p = l;
	while (p != NULL && p->info < v)
	{
		ant = p;
		p = p->prox;
	}
	novo = (Lista *)malloc(sizeof(Lista));
	novo->info = v;
	if (ant == NULL)
	{
		novo->prox = l;
		l = novo;
	}
	else
	{
		novo->prox = ant->prox;
		ant->prox = novo;
	}
	return l;
}

Lista *lst_ler_arquivo(char *nome_arquivo)
{
	FILE *arquivo;
	int valor;
	Lista *l = lst_cria();
	arquivo = fopen(nome_arquivo, "r");
	if (arquivo == NULL)
	{
		printf("Erro ao abrir o arquivo!\n");
		exit(1);
	}
	while (fscanf(arquivo, "%d", &valor) != EOF)
	{
		l = lst_insere(l, valor);
	}
	fclose(arquivo);
	return l;
}
