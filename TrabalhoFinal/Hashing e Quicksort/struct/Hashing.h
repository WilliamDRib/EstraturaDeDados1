#ifndef HASHING_H_INCLUDED
#define HASHING_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lista.h"
#include "ListaArr.h"

#define TAM 53

//Funcoes relacionadas a hashing e histograma

void troca(Lista * lista, Node * A, Node * B){		//Funcao para alternar dois numeros em um array;

	//printf("A = %s| B = %s\n", A -> dado, B -> dado);

	char bkp[30];
	strcpy(bkp, A -> dado);
	strcpy(A -> dado, B -> dado);
	strcpy(B -> dado, bkp);

	// if(A == NULL || B == NULL || A == B){
	// 	printf("A = %s| B = %s\n", A -> dado, B -> dado);
	// 	return;
	// }

	// if(lista -> head == A){
	// 	lista -> head = B;
	// }else if(lista -> head == B){
	// 	lista -> head = A;
	// }

	// if(lista -> tail == A){
	// 	lista -> tail = B;
	// }else if(lista -> tail == B){
	// 	lista -> tail = A;
	// }


	// if(A -> next != NULL){
	// 	A -> next -> back = B;
	// }
	// if(B -> next != NULL){
	// 	B -> next -> back = A;
	// }
	
	// Node * depois = A -> next;
	// A -> next = B -> next;
	// B -> next = depois;
	
	// if(A -> back != NULL){
	// 	A -> back -> next = B;
	// }
	// if(B -> back != NULL){
	// 	B -> back -> next = A;
	// }

	// Node * antes = A -> back;
	// A -> back = B -> back;
	// B -> back = antes;	

}

Node* partition(Lista * lista, Node * left, Node * pivo){ // Funcao responsavel por separar os numeros baseado em um pivo
    Node* aux = left -> back;
 
    for (Node *i = left; i != pivo; i = i -> next){
        if (strcmp(i -> dado, pivo -> dado) < 0){

			if(aux == NULL){
				aux = left;
			} else {
				aux = aux -> next;
			}
			
			troca(lista, aux, i);
        }
    }
	
    if(aux == NULL){
		aux = left;
	} else {
		aux = aux -> next;
	}
    troca(lista, aux, pivo);
    return aux;
}

void _quickSort(Lista * lista, Node* left, Node * right){
    if (right != NULL && left != NULL && left != right && left != right -> next){
		
		Node *pivo = partition(lista, left, right);
		_quickSort(lista, left , pivo -> back);
		_quickSort(lista, pivo -> next, right);
    }
}

void quickSort(Lista ** lista, int size){
	for(int i = 0; i < size; i++){
		_quickSort(lista[i], lista[i] -> head, lista[i] -> tail);
	}
	
}

int indexHashing(char * palavra){
	int soma = 0;
	
	for(int i = 0; i < strlen(palavra); i++){
		soma += palavra[i] * (i+1);
	}

	soma %= TAM;
	
	return soma;
}

int * somaMedia(Lista ** lista, int size, int * valores){

	int media = 0;
	for(int i = 0; i < size; i++){
		media += lista[i] -> size;
	}
	media /= size;

	int menorValor = media;
	int maiorValor = 0;
	
	for(int i = 0; i < size; i++){
		if(lista[i] -> size < menorValor){
			menorValor = lista[i] -> size;
		}

		if(lista[i] -> size > maiorValor){
			maiorValor = lista[i] -> size;
		}
	}

	valores[0] = media;
	valores[1] = maiorValor;
	valores[2] = menorValor;

	return valores;
}

void histograma(Lista ** lista, int size){
	int temp[3];
	int * valores = somaMedia(lista, size, temp);

	int media = valores[0];
	int maiorValor = valores[1];
	int menorValor = valores[2];
	
	
	for(int i = maiorValor/20 + 6; i >= menorValor/20 - 10; i--){

		if(i == media / 20){
			printf("%4i ", media);
		} else {
			printf("%4i ", media + (i - (media / 20)) * 20);
		}
		
		
		for(int j = 0; j < size; j++){

			if(i == media / 20 && i == lista[j] -> size / 20){
				printf("━┳━");
			}else if(i == media / 20 && i <= lista[j] -> size / 20){
				printf("━╋━");
			}else if(i == media / 20){
				printf("━━━");
			}else if(i <= lista[j] -> size / 20){
				printf(" ┃ ");
			}else{
				printf(" · ");
			}
			
		}
		
		printf("\n");
	}

	printf("     ");

	for(int i = 1; i <= size; i ++){
		if(i <= 9){
			printf("0%i ",i);
		}else{
			printf("%i ",i);
		}
	}

	printf("\nHistograma:\nMedia = %i\nMaior Array = %i\nMenor Array = %i\n", media, maiorValor, menorValor);
}

#endif