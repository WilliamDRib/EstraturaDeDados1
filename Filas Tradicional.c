//Aluno: William Dutra Ribeiro

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LIM 10

typedef struct node{
	struct node *next;     //Item da lista
	struct node *back;
	int dado; 
} Node;

typedef struct {
	Node *head;
	Node *tail;						 //Lista
	int size;
} Lista;


bool empty(Lista *);
Lista* criaLista();
Node* criaElemento(int);
void insereElementoNaLista(Lista* , int);
void percorreLista(Lista* , int);						//Prototipação
void removeElementoDaLista(Lista*);
void limpaLista(Lista*);
	
	
bool empty(Lista * lista){
	if(lista -> size == 0){
		return true;
	} else {
		return false;
	}
}


Lista* criaLista(){
	Lista* lista;
	lista = (Lista*) malloc(sizeof(Lista));
	if (lista == NULL)
		return NULL;
	else {
		lista -> head = NULL;						//Alocar lista;
		lista -> tail = NULL;
		lista -> size = 0;
	}
	
	return lista;
}


Node* criaElemento(int dado){
	Node* nodo;
	nodo = (Node*) malloc(sizeof(Node));
	if (nodo == NULL)
		return NULL;								//Aloca elemento;
	else {
		nodo -> next = NULL;
		nodo -> back = NULL;
		nodo -> dado = dado;
	}
	
	return nodo;
}


void insereElementoNaLista(Lista* lista, int dado){
	Node* novo = criaElemento(dado);

	if (novo == NULL){
		printf("Erro ao alocar o elemento\n\n");
		return;
	}

	if(lista -> size == LIM){
		printf("Lista Cheia!\n");
		return;
	}
	
	if(empty(lista)){
		lista -> head = novo;					//Coloca elemento na primeira posicao(head);
		lista -> tail = novo;					
	} else {
		novo -> back = lista -> tail;
		lista -> tail -> next = novo;
		lista -> tail = novo;
	}

	printf("Valor %i inserido com sucesso\n", novo -> dado);
	lista -> size++;
	return;
}


void percorreLista(Lista* lista, int decisao){
	Node* aux;

	if(empty(lista)){
		printf("Lista vazia!\n\n");
		return;
	}

	if(decisao == 1){
		aux = lista->head;
		
		while(aux != NULL){									//Percore a lista comeco -> fim;
			printf("%i, ", aux->dado);
			aux = aux->next;
		}
	}	else if (decisao == -1){
		aux = lista->tail;
		
		while(aux != NULL){									//Percore a lista fim -> comeco;
			printf("%i, ", aux->dado);
			aux = aux->back;
		}
	}
	printf("\n\n");
}


void removeElementoDaLista(Lista* lista){
	Node * elem = lista -> head;

	if(!empty(lista)){
		lista -> head = elem -> next;
		if(lista -> head == NULL){
			lista -> tail = NULL;						//Remove ultimo elemento(tail);
		} else {
			elem -> next -> back = NULL;
		}
	} else {
		return;
	}

	printf("Elemento %i excluido da lista\n", elem -> dado);

	free (elem);
	lista -> size --;

	return;
}


void limpaLista(Lista* lista){
	while(lista -> head != NULL){
		removeElementoDaLista(lista);
	}
	
	free(lista);										//Lista e desaloca lista;
	printf("Lista desalocada\n");
}


int main(){
	int dado;
	Node* pivo;
	Lista* list = criaLista();

	if (list == NULL){
		printf("Impossivel alocar memoria para a lista.\n");
		return -1;
	}

	insereElementoNaLista(list, 1);
	percorreLista(list, 1);
	insereElementoNaLista(list, 2);
	percorreLista(list, 1);
	insereElementoNaLista(list, 3);
	percorreLista(list, 1);
	insereElementoNaLista(list, 4);
	percorreLista(list, 1);
	insereElementoNaLista(list, 5);
	percorreLista(list, 1);
	removeElementoDaLista(list);
	percorreLista(list, 1);
	removeElementoDaLista(list);
	percorreLista(list, 1);
	removeElementoDaLista(list);
	percorreLista(list, 1);
	removeElementoDaLista(list);
	percorreLista(list, 1);
	removeElementoDaLista(list);
	percorreLista(list, 1);


	limpaLista(list);
	return 0;
}