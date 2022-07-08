#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "struct/Hashing.h"
#include "struct/Lista.h"
#include "struct/ListaArr.h"

int main(void) {
	clock_t t;

	FILE *file;
	file = fopen("dados/nomes.txt", "r");
	if (file == NULL) {
		printf("Erro");
		return 0;
	}
	
	Lista **listaArr;
	listaArr = CriaListaArr(TAM);

	char c[50];
	
	while (fgets(c, 50, file) != NULL) {
		strcpy(c, strtok(c, "\n"));
		insereElementoNaLista(listaArr[indexHashing(c)], c); // Inserindo do nomes.txt;
	}

	int loop = 1;
	
	while(loop == 1){
		printf("\nMenu:\n1 - Inserir nome\n2 - Consultar nome\n3 - Quantidade de elementos por chave\n4 - Histograma\n5 - Remoção de nome\n6 - Ordernar listas\n7 - Mostrar lista\n8 - Sair\n");
		int aux;
		scanf("%i", &aux);
		char nome[50];
		int num;
		Node * node;
		bool result = false;
		
		switch (aux){
			case 1:
				printf("\nDigite o nome\n");
				scanf("%s", nome);

				result = insereElementoNaLista(listaArr[indexHashing(nome)], nome);
				printf(result ? "\nNome %s inserido\n" : "Nao foi possivel inserir" , nome);
				
				break;
			
			case 2:
				printf("\nDigite o nome\n");
				scanf("%s", nome);

				t = clock();
				node = pesquisaNaLista(listaArr[indexHashing(nome)], nome);
				t = clock() - t;

				printf("\nTempo para execução: %lf ms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));

				if(node != NULL){
					printf("\nNome: %s\nNo index do hashing: %i\n", node -> dado, indexHashing(nome));
				}else{
					printf("\nNome nao encontrado\n");
				}
				break;
			
			case 3:
				while(1){
					printf("\nQual lista ? (1 - %i)\n", TAM);
					scanf("%i", &num);

					if(num >= 1 && num <= TAM){
						printf("\nTamanho do Array selecionado é: %i\n",listaArr[num - 1] -> size);
						break;
					}
					printf("\nNumero invalido\n");
				}
				break;

			case 4:
				histograma(listaArr, TAM);
				break;
			
			case 5:
				printf("\nQual nome irá remover?\n");
				scanf("%s", nome);

				t = clock();
				node = pesquisaNaLista(listaArr[indexHashing(nome)], nome);
				result = removeElementoDaLista(listaArr[indexHashing(nome)], node);
				t = clock() - t;

				printf("\nTempo para execução: %lf ms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));

				printf(result ? "\nItem removido\n" : "\nItem não encontrado\n");
				break;
			
			case 6:
				
				t = clock();
				quickSort(listaArr, TAM);
				t = clock() - t;

				printf("\nTempo para execução: %lf ms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
				
				break;
			
			case 7:
				printf("\nQual lista ? (1 - %i)\n", TAM);
				scanf("%i", &num);

				percorreLista(listaArr[num], 1);
				break;
			
			case 8:
				loop = 0;
				printf("\nAdios!\n");
				break;
			
			default:
				printf("\nNumero Invalido\n");
				break;
		}
	}
	
	
	limpaListaArr(listaArr, TAM);
	return 0;
}