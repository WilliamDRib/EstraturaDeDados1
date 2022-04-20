//Aluno: William Dutra Ribeiro

#include <stdio.h>
#include <stdlib.h>

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


Lista* criaLista(){
	Lista* lista;
	lista = (Lista*) malloc(sizeof(Lista));
	if (lista == NULL)
		return NULL;
	else {
		lista->head = NULL;						//Alocar lista
		lista->tail = NULL;
		lista->size = 0;
	}
	
	return lista;
}


Node* criaElemento(int dado){
	Node* nodo;
	nodo = (Node*) malloc(sizeof(Node));
	if (nodo == NULL)
		return NULL;								//Aloca elemento
	else {
		nodo -> next = NULL;
		nodo -> back = NULL;
		nodo -> dado = dado;
	}
	
	return nodo;
}


void insereElementoNaLista(Lista* lista, Node* pivo, int dado){
	Node* novo = criaElemento(dado);

	if (novo == NULL){
		printf("Erro ao alocar o elemento\n\n");
		return;
	}

	if(pivo == NULL && lista -> size != 0){
		printf("Pivo é nulo, mas a lista não é vazia\n\n");
		return;
	}
	
	if( lista -> size == 0 ){
		lista -> head = novo;
		lista -> tail = novo;
	} else {
		novo -> next = pivo -> next;
		novo -> back = pivo;

		if(pivo -> next == NULL){
			lista -> tail = novo;
		} else {
			pivo -> next -> back = novo;
		}

		pivo -> next = novo;
	}

	printf("Valor %i inserido com sucesso\n", novo -> dado);
	lista -> size++;
	return;
}


void percorreLista(Lista* lista, int decisao){
	Node* aux;

	if(lista -> size == 0){
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


void removeElementoDaLista(Lista* lista, Node* elem){

	if(elem != NULL && lista -> size != 0){
		if(elem == lista ->head){
			lista -> head = elem -> next;
			if(lista -> head == NULL){
				lista -> tail = NULL;
			}
			else {
				elem -> next -> back = NULL;
			}
		}
		else{
			elem -> back -> next = elem -> next;
			if(elem -> next == NULL){
				lista -> tail = elem-> back;
			}
			else{
				elem -> next -> back = elem -> back;
			}
		}
	} else {
		return;
	}

	printf("Elemento %i excluido da lista\n", elem -> dado);

	free (elem);
	lista -> size --;

	return;
}


Node* pesquisaNaLista(Lista* lista, int dado){
	Node* aux;
	aux = lista -> head;
	
	while(aux != NULL){
		if (aux -> dado == dado){
			return aux;
		}
		aux = aux -> next;
	}
	return NULL;
}


void limpaLista(Lista* lista){
	while(lista -> head != NULL){
		removeElementoDaLista(lista, lista->head);
	}
	
	free(lista);
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

	percorreLista(list,1);

	insereElementoNaLista(list, list->tail, 15);

	percorreLista(list,1);

	insereElementoNaLista(list, list->tail, 25);

	percorreLista(list,1);

	insereElementoNaLista(list, list->head, 10);

	percorreLista(list,1);

	insereElementoNaLista(list, NULL, 35);

	percorreLista(list,1);

	insereElementoNaLista(list, list->head, 35);

	percorreLista(list,1);

	pivo = pesquisaNaLista(list, 10);
	insereElementoNaLista(list, pivo, 27);

	percorreLista(list,1);		

	insereElementoNaLista(list, list->tail, 29);

	percorreLista(list,1);

	insereElementoNaLista(list, NULL, 45);

	percorreLista(list,1);
	percorreLista(list,-1);
	
	removeElementoDaLista(list, list -> tail);

	percorreLista(list,1);

	removeElementoDaLista(list, list -> head);

	percorreLista(list,1);

	removeElementoDaLista(list, NULL);

	percorreLista(list,1);

	pivo = pesquisaNaLista(list, 55);
	removeElementoDaLista(list, pivo);

	percorreLista(list,1);

	pivo = pesquisaNaLista(list, 27);
	removeElementoDaLista(list, pivo);

	percorreLista(list,1);

	removeElementoDaLista(list, list -> head);

	percorreLista(list,1);

	pivo = pesquisaNaLista(list, 10);
	removeElementoDaLista(list, pivo);

	percorreLista(list,-1);
	percorreLista(list,1);
	
	limpaLista(list);
	return 0;
}
