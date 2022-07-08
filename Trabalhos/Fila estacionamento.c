//Aluno: William Dutra Ribeiro

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LIM 3
#define NOLIM -1

typedef struct node{
	struct node *next;     //Item da lista;
	struct node *back;
	int dado; 
} Node;

typedef struct {
	Node *head;
	Node *tail;						 //Lista;
	int size;
	int lim;
} Lista;


bool empty(Lista *);
Lista* criaLista();
Node* criaElemento(int);
Node* pesquisaNaLista(Lista*, int);
void insereElementoNaLista(Lista* , Lista*, Node *);
void percorreLista(Lista* , int);						//Prototipação;
void removeElementoDaLista(Lista*, Lista*, Node *);
void limpaLista(Lista*, Lista*);

	
bool empty(Lista * lista){
	if(lista -> size == 0){
		return true;
	} else {											//Verificador de lista vazia;
		return false;
	}
}

Lista* criaLista(int lim){
	Lista* lista;
	lista = (Lista*) malloc(sizeof(Lista));
	if (lista == NULL)
		return NULL;
	else {
		lista -> head = NULL;						//Alocar lista;
		lista -> tail = NULL;
		lista -> size = 0;
		lista -> lim = lim;
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

void insereElementoNaLista(Lista* lista, Lista* espera, Node* elem){
	Node* novo = elem;

	if(lista -> size == lista -> lim){
		printf("\nLista Cheia! Inserindo na lista de espera!\n");
		insereElementoNaLista(espera, NULL, elem);
		return;
	}
	
	if(empty(lista)){
		lista -> head = novo;
		lista -> tail = novo;								//Inserir elemento na lista, na primeira pos;
	} else {
		novo -> back = lista -> tail;		
		lista -> tail -> next = novo;
		lista -> tail = novo;
		lista -> tail -> next = NULL;
	}

	printf("\nValor %i inserido com sucesso\n", novo -> dado);
	lista -> size++;
	return;
}

void percorreLista(Lista* lista, int decisao){
	Node* aux;

	if(empty(lista)){
		printf("\nLista vazia!\n");
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

Node* pesquisaNaLista(Lista* lista, int dado){
	Node* aux;
	aux = lista -> head;
	
	while(aux != NULL){
		if (aux -> dado == dado){
			return aux;												//Busca pelo elemento na fila;
		}
		aux = aux -> next;
	}
	
	return NULL;
}

void removeElementoDaLista(Lista* lista, Lista* espera, Node * pivo){
	Node * elem = lista -> head;

	if(empty(lista)){
		printf("\nLista Vazia\n");
		return;
	}
	
	if(pivo == NULL || pivo == lista -> head){
		lista -> head = elem -> next;
		
		if(lista -> head == NULL){
			lista -> tail = NULL;
		} else {															//Removendo o primeiro elemento;
			elem -> next -> back = NULL;
		}

		lista -> size --;
	
		free(elem);

		printf("\nElemento %i excluido da lista\n", elem -> dado);  
	} else {
		
		for(int i = 0; i < lista -> size + 1; i++){
			if(pivo != lista -> head){
				lista -> head -> back = lista -> tail;
				lista -> tail -> next = lista -> head;
				
				lista -> tail = lista -> tail -> next;
				lista -> head = lista -> head -> next;		//Ciclando a fila;
																										
				lista -> head -> back = NULL;
				lista -> tail -> next = NULL;

			} else {
				removeElementoDaLista(lista, NULL, NULL);				//Achou o elemento, remove ele;
			}
			
			elem = elem -> next;
		}
	}

	if(!empty(espera) && espera != NULL){
		insereElementoNaLista(lista, NULL, criaElemento(espera -> head -> dado));
		removeElementoDaLista(espera, NULL, NULL);				//Apos remover, se tiver elem na espera adiciona na principal;
	} 

	return;
}

void limpaLista(Lista* lista, Lista* espera){
	while(lista -> head != NULL){
		removeElementoDaLista(lista, espera, NULL);
	}																								//Limpa a lista e desaloca ela;
	
	free(lista);
	printf("\nLista desalocada\n");
}


int main(){
	int dado;
	Node* pivo;
	
	Lista* lista = criaLista(LIM);
	Lista* espera = criaLista(NOLIM);

	if (lista == NULL || espera == NULL){
		printf("\nImpossivel alocar memoria para a lista.\n");
		return -1;
	}

	int decisao;
	int num;

	while(true){
		printf("\nAção que deseja tomar!\n1 - Inserir\n2 - Remover\n3 - Mostrar Listas\n4 - Sair\n");
		scanf("%i",&decisao);

		if(decisao == 1){
			printf("\nQual valor deseja inserir?\n");
			scanf("%i",&num);
			
			pivo = criaElemento(num);
			insereElementoNaLista(lista, espera, pivo);
			
		} else if(decisao == 2){													//Menu de interação;
			printf("\nQual valor deseja excluir?\n");
			scanf("%i",&num);

			pivo = pesquisaNaLista(lista, num);
			removeElementoDaLista(lista, espera, pivo);
			
		}else if(decisao == 3){
			percorreLista(lista, 1);
			percorreLista(espera, 1);
		}else if(decisao == 4){
			break;
		}else{
			printf("\nValor invalido\n");
		}
	}

	limpaLista(lista, espera);
	return 0;
}
