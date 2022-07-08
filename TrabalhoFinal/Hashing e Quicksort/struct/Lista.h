#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	struct node *next;     //Item da lista
	struct node *back;
	char dado[50]; 
} Node;

typedef struct lista{
	Node *head;
	Node *tail;						 //Lista
	int size;
} Lista;

Lista* criaLista(){
	Lista* lista = (Lista*) malloc(sizeof(Lista));
	
	if (lista == NULL){
		return NULL;
	} else {
		lista -> head = NULL;						//Alocar lista
		lista -> tail = NULL;
		lista -> size = 0;
	}
	
	return lista;
}

Node* criaElemento(char* dado){
	Node* node = (Node*) malloc(sizeof(Node));
	
	if (node == NULL){
		return NULL;								//Aloca elemento
	} else {
		node -> next = NULL;
		node -> back = NULL;
		strcpy(node -> dado, dado);
	}
	
	return node;
}

bool insereElementoNaLista(Lista* lista, char* dado){
	Node* novo = criaElemento(dado);

	if (novo == NULL){
		return false;
	}
	
	if( lista -> size == 0 ){
		lista -> head = novo;
		lista -> tail = novo;
		
	} else {
		novo -> back = lista -> tail;
		lista -> tail -> next = novo;
		lista -> tail = novo;
	}

	lista -> size++;
	return true;
}

int percorreLista(Lista* lista, int decisao){
	Node* aux;

	if(lista -> size == 0){
		printf("Lista Vazia\n");
		
		return -1;
	}

	if(decisao == 1){
		aux = lista->head;
		
		while(aux != NULL){									//Percore a lista comeco -> fim
			printf("%s, ", aux -> dado);
			aux = aux -> next;
		}
	}	else if (decisao == -1){
		aux = lista -> tail;
		
		while(aux != NULL){									//Percore a lista fim -> comeco
			printf("%s, ", aux -> dado);
			aux = aux -> back;
		}
	}
	printf("\n\n");

	return 0;
}

bool removeElementoDaLista(Lista* lista, Node* elem){
	if (lista -> size != 0 && elem != NULL) {
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
		return false;
	}
	
	free (elem);
	lista -> size --;

	return false;
}

Node* pesquisaNaLista(Lista* lista, char* dado){
	Node* aux;
	aux = lista -> head;
	
	while(aux != NULL){
		if (strcmp(aux -> dado, dado) == 0){
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
}

#endif