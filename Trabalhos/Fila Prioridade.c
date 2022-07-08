//Aluno: William Dutra Ribeiro

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LIM 10

typedef struct node{
	struct node *next;     //Item da lista
	struct node *back;
	int prioridade;
	int dado; 
} Node;

typedef struct {
	Node *head;
	Node *tail;						 //Lista
	int size;
	int limite;
} Lista;


Lista * criaLista(int);
Node* criaElemento(int , int);
void insereElementoNaLista(Lista* , int , int);
void percorreLista(Lista* , int);								//Prototipação
void removeElementoDaLista(Lista* , int);
void limpaLista(Lista*);
bool empty(Lista *);


bool empty(Lista * lista){
	if(lista -> size == 0){
		return true;
	} else {
		return false;
	}
}

Lista* criaLista(int lim){
	Lista* lista;
	lista = (Lista*) malloc(sizeof(Lista));
	
	if (lista == NULL){
		return NULL;
	} else {
		lista -> head = NULL;						//Alocar lista
		lista -> tail = NULL;
		lista -> size = 0;
		lista -> limite = lim;
	}
	
	return lista;
}


Node* criaElemento(int dado, int prioridade){
	Node* nodo;
	nodo = (Node*) malloc(sizeof(Node));
	
	if (nodo == NULL){
		return NULL;								//Aloca elemento
	} else {
		nodo -> next = NULL;
		nodo -> back = NULL;
		nodo -> dado = dado;
		nodo -> prioridade = prioridade;
	}
	
	return nodo;
}


void insereElementoNaLista(Lista* lista, int dado, int prioridade){
	Node* novo = criaElemento(dado, prioridade);

	if (novo == NULL){
		printf("Erro ao alocar o elemento\n\n");
		return;
	}

	if(lista -> size == LIM){
		printf("Lista Cheia!\n");
		return;
	}
	
	if(empty(lista)){
		lista -> head = novo;
		lista -> tail = novo;					//Adiciona o elem sempre ao final;
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
		
		while(aux != NULL){									//Percore a lista comeco -> fim
			printf("%i, ", aux->dado);
			aux = aux->next;
		}
	}	else if (decisao == -1){
		aux = lista->tail;
		
		while(aux != NULL){									//Percore a lista fim -> comeco
			printf("%i, ", aux->dado);
			aux = aux->back;
		}
	}
	printf("\n\n");
}


void removeElementoDaLista(Lista* lista, int decisao){
	
	if(empty(lista)){
		printf("Lista vazia\n\n");
		return;
	}	
	
	Node * elem = lista -> head;
	int auxPrio = elem -> prioridade;
	Node * bkpNode = elem;
	
	if(decisao == 1){
		for(int i = 0; i < lista -> size ; i++) {
			if(elem -> prioridade < auxPrio){
				auxPrio = elem -> prioridade;
				bkpNode = elem;								//Acha o elem com maior prioridade;
			}
			elem = elem -> next;
		}
	}if(decisao == -1){
		for(int i = 0; i < lista -> size ; i++) {
			if(elem -> prioridade > auxPrio){
				auxPrio = elem -> prioridade;
				bkpNode = elem;							 //Acha o elem com menor prioridade;
			}
			elem = elem -> next;
		}
	}
	
	elem = bkpNode;

	if(elem == lista -> head){
		lista -> head = elem -> next;
		if(lista -> head == NULL){
			lista -> tail = NULL;
		}
		else {												//removendo elemento;
			elem -> next -> back = NULL;
		}
	} else {
		elem -> back -> next = elem -> next;
		if(elem -> next == NULL){
			lista -> tail = elem-> back;
		}
		else{
			elem -> next -> back = elem -> back;
		}
	}

	printf("Elemento %i excluido da lista\n", elem -> dado);

	free (elem);
	lista -> size --;

	return;
}


void limpaLista(Lista* lista){
	while(lista -> head != NULL){
		removeElementoDaLista(lista, 1);
	}
	
	free(lista);									//Limpa e a desaloca;
	printf("Lista desalocada\n");
}


int main(){
	int dado;
	Node* pivo;
	Lista* list = criaLista(LIM);

	if (list == NULL){
		printf("Impossivel alocar memoria para a lista.\n");
		return -1;
	}

	insereElementoNaLista(list, 1, 5);
	percorreLista(list, 1);
	insereElementoNaLista(list, 2, 4);
	percorreLista(list, 1);
	insereElementoNaLista(list, 3, 3);
	percorreLista(list, 1);
	insereElementoNaLista(list, 4, 2);
	percorreLista(list, 1);
	insereElementoNaLista(list, 5, 1);
	percorreLista(list, 1);
	removeElementoDaLista(list, -1);
	percorreLista(list, 1);
	removeElementoDaLista(list, -1);
	percorreLista(list, 1);
	removeElementoDaLista(list, -1);
	percorreLista(list, 1);
	removeElementoDaLista(list, 1);
	percorreLista(list, 1);
	removeElementoDaLista(list, 1);
	percorreLista(list, 1);


	limpaLista(list);
	return 0;
}
