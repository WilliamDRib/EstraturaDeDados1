//Aluno: William Dutra Ribeiro;

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node{
	struct node *next;     //Item da pilha;
	struct node *back;
	char dado; 
} Node;

typedef struct {
	Node *topo;						 //Pilha;
	int size;
} Pilha;

Pilha* criaPilha();
Node* criaElemento(char);
void InsereNaPilha(Pilha*, char);
void RemoverDaPilha(Pilha*);					//Prototipação;
void percorrePilha(Pilha*);
bool empty(Pilha*);
bool analizarExpresao(char*);
void delPilha(Pilha*);
	

Pilha* criaPilha(){
	Pilha* pilha;
	pilha = (Pilha*) malloc(sizeof(Pilha));
	if (pilha == NULL){
		return NULL;
	} else {
		pilha -> topo = NULL;						//Alocar pilha;
		pilha -> size = 0;
	}
	
	return pilha;
}

Node* criaElemento(char dado){
	Node* nodo;
	nodo = (Node*) malloc(sizeof(Node));
	if (nodo == NULL){
		return NULL;
	} else {						//Aloca elemento;
		nodo -> next = NULL;
		nodo -> back = NULL;
		nodo -> dado = dado;
	}
	
	return nodo;
}

void InsereNaPilha(Pilha* pilha, char dado){
	Node* novo = criaElemento(dado);

	if (novo == NULL){
		printf("\nErro ao alocar o elemento\n\n");
		return;
	}
	
	if(empty(pilha)){
		pilha -> topo = novo;					//Coloca elemento no topo;				
	} else {
		novo -> back = pilha -> topo;
		pilha -> topo -> next = novo;
		pilha -> topo = novo;
	}

	printf("\nValor '%c' inserido com sucesso\n", novo -> dado);
	pilha -> size++;
	return;
}

void RemoverDaPilha(Pilha* pilha){
	if(empty(pilha)){
		printf("\nPilha Vazia!\n");
		return;
	}

	Node * elem = pilha -> topo;
	pilha -> topo = elem -> back;				//Remove elemento do topo;
	
	free (elem);
	pilha -> size --;
	
	if(!empty(pilha)){
		pilha -> topo -> next = NULL;
	}
	
	printf("\nElemento '%c' excluido da pilha\n", elem -> dado);
	return;
}

void percorrePilha(Pilha* pilha){
	Node* aux;

	if(pilha -> size == 0){
		printf("\nPilha vazia!\n");
		return;
	}

	aux = pilha->topo;
	printf("\nPilha:\n");
	
	while(aux != NULL){									//Percore a pilha comeco -> fim
		printf("'%c'\n", aux -> dado);
		aux = aux -> back;
	}
	printf("\n\n");
}

bool compareCarac(char pilha, char expre){
	
	switch(pilha){
		case '{':
			if(expre == '}'){
				return true;
			}
			break;
		case '(':
			if(expre == ')'){
				return true;
			}
			break;
		case '[':
			if(expre == ']'){
				return true;
			}
		break;
	}
	return false;
}

bool analizarExpresao(char* expre){
	char caracAber[3] = {'[','(','{'};
	char caracFech[3] = {']',')','}'};

	Pilha* pilha = criaPilha();

	if (pilha == NULL){
		return false;			//Erro ao alocar pilha;
	}

	for(int letras = 0; letras < sizeof(expre); letras++){
		for(int i = 0; i < sizeof(caracAber); i++){
			
			if(expre[letras] == caracAber[i]){
				InsereNaPilha(pilha, expre[letras]);
				
			} else if (expre[letras] == caracFech[i]){
				if(empty(pilha)){
					printf("\nFormatação invalida\n");
					return false;
				}else if(compareCarac(pilha -> topo -> dado, expre[letras])){
					RemoverDaPilha(pilha);
				} else {
					printf("\nFormatação invalida\n");
					delPilha(pilha);
					return false;
				}
			}
			
		}
	}
	
	if(empty(pilha)){
		delPilha(pilha);
		return true;
	}else{
		delPilha(pilha);
		return false;
	}
	
}

bool empty(Pilha* pilha){
	if(pilha -> size == 0){
		return true;
	} else {
		return false;
	}
}

void delPilha(Pilha* pilha){
	while(pilha -> topo != NULL){
		RemoverDaPilha(pilha);
	}																//Limpa a pilha e desaloca ela;
	
	free(pilha);
	printf("\nPilha desalocada\n");
}


int main(void) {
	
	int decisao;

	while(true){
		printf("\n1 - Expressao\n2 - Sair\n");
		scanf("%i",&decisao);

		if(decisao == 1){
			char expressao[100];
			
			printf("\nDigite a expressao!\n");
			scanf("%s", expressao);
			
			printf("\n%s\n", analizarExpresao(expressao) ? "Expressao valida" : "Expressao invalida" );
				
		}else if(decisao == 2){
			break;
		
		}else{
			printf("\nValor invalido\n");
		}
	}

	return 0;	
}