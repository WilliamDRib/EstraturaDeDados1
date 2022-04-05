//Aluno: William Dutra Ribeiro

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	struct node *next;     //Item da lista
	int dado; 
} Node;

typedef struct {
	Node *head;
	Node *tail;						 //Lista
	int size;
} Lista;



Lista* criaLista(){
	Lista* lista;
	lista = (Lista*) malloc(sizeof(Lista));
	
	if (lista == NULL){
		return NULL;
	} else {
		lista->head = NULL;						//Alocar lista
		lista->tail = NULL;
		lista->size = 0;
	}
	
	return lista;
}



Node* criaElemento(int dado){
	Node* nodo;
	nodo = (Node*) malloc(sizeof(Node));
	if (nodo == NULL){
		return NULL;								//Aloca elemento
	} else {
		nodo->next = NULL;
		nodo->dado = dado;
	}
	
	return nodo;
}


int insereElementoNaLista(Lista* lista, Node* pivo, int dado){
	Node* novo = criaElemento(dado);
	if (novo == NULL)
		return -1;

	if (pivo == NULL){
		if (lista->size == 0){
			lista->tail = novo;
		}
		novo->next = lista->head;
		lista->head = novo;											//Insere elemento na lista
	} else {
		if (pivo->next == NULL){
			lista->tail = novo;
		}
		novo->next = pivo->next;
		pivo->next = novo;
	}
	lista->size++;
	return 0;
}


void percorreLista(Lista* lista){
	Node* aux;
	aux = lista->head;
	
	while(aux != NULL){									//Percore a lista
		printf("%i, ", aux->dado);
		aux = aux->next;
	}
}


int removeElementoDaLista(Lista* lista, Node* pivo){
	Node* antigo;
	int dado;
	
	if (lista->size == 0){
		return -1;							//lista vazia
	}
	
	if (pivo == NULL){
			antigo = lista->head;
			lista->head = lista->head->next;

			if (lista->head == NULL){  //excluido era ultimo elemento
				lista->tail = NULL;
			}
	} else {
			if (pivo->next == NULL){
				return -2; 								//pivo é p ultimo elemento da lista
			}
			antigo = pivo->next;
			pivo->next = pivo->next->next;

			if (pivo->next == NULL){
				lista->tail = pivo; 		//atualiza o tail caso o pivo seja o ultimo elemento
			}
		}
	
	dado = antigo->dado;
	free(antigo);

	lista->size--;
	
	return dado;
}



Node* pesquisaNaLista(Lista* lista, int dado){
	Node* aux;
	aux = lista->head;
	
	while(aux != NULL){
		if (aux->dado == dado){
			return aux;
		}
		aux = aux->next;
	}
	return NULL;
}



void limpaLista(Lista* lista){
	while(lista->head != NULL){
		removeElementoDaLista(lista, NULL);
	}
	
	free(lista);
}





int main(){
	int dado;
	Node* pivo;
	Lista* lista = criaLista();

	if (lista == NULL){
		printf("Impossivel alocar memoria para a lista.\n");
		return -1;
	}

	insereElementoNaLista(lista, lista->tail, 10);
	insereElementoNaLista(lista, lista->tail, 15);
	insereElementoNaLista(lista, lista->tail, 25);
	insereElementoNaLista(lista, NULL, 35);
	percorreLista(lista);
	
	dado = removeElementoDaLista(lista, NULL);
	printf("\nExcluido o valor %i da lista\n", dado);
	
	pivo = pesquisaNaLista(lista, 15);
	dado = removeElementoDaLista(lista, pivo);
	printf("\nExcluido o valor %i da lista\n", dado);
	
	limpaLista(lista);
	return 0;
}