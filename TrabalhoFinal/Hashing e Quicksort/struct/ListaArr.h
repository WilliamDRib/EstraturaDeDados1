#ifndef LISTAARR_H_INCLUDED
#define LISTAARR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lista.h"

Lista ** CriaListaArr(int size){
	Lista ** lista = (Lista **) malloc(sizeof(Lista *) * size);

	if(lista == NULL){
		printf("Erro ao alocar");
		return NULL;
	}

	for(int i = 0; i < size; i++){
		lista[i] = criaLista();
	}
	
	return lista;
}

void mostrarListaArr(Lista ** lista, int size){
	for(int i = 0; i < size; i++){
		printf("Lista %i\n", i);
		percorreLista(lista[i], 1);
		printf("\n\n");
	}
}

void limpaListaArr(Lista ** lista, int size){
	for(int i = 0; i < size; i++){
		limpaLista(lista[i]);
	}

	free(lista);
}

#endif