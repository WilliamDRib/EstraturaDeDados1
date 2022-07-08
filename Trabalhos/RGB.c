#include <stdio.h>
#include <stdlib.h>
	
typedef struct{
	int r,g,b;
}RGB;

void preencherRGB (int x, int y, RGB **matriz){
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			matriz[i][j].r = rand() % 256;
			matriz[i][j].g = rand() % 256;
			matriz[i][j].b = rand() % 256;
		}
	}
}

void converter_rgb_gray (int x, int y, RGB **matriz_rgb, RGB **matriz_gray){
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			matriz_gray[i][j].r = (0.3 * matriz_rgb[i][j].r);
			matriz_gray[i][j].g = (0.59 * matriz_rgb[i][j].g);
			matriz_gray[i][j].b = (0.11 * matriz_rgb[i][j].b);
		}
	}
}

void printar (int x, int y, RGB **matriz){
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			printf("%i ",matriz[i][j].r);
			printf("%i ",matriz[i][j].g);
			printf("%i ",matriz[i][j].b);
			printf("   ");
		}
		printf("\n");
	}
}

RGB **loadMatriz(){
	RGB **mat;
	mat = (RGB **) malloc(10 * sizeof (RGB*));

	for(int i = 0; i < 10; i++){
		mat[i] = (RGB *) malloc (15 * sizeof (RGB));
	}
	return mat;
}

void freeMatriz(RGB **mat){
	for(int i = 0; i < 10; i++){
		free(mat[i]);
	}
	
	free(mat);
}
	
int main(void) {	
	RGB **cores;
	cores = loadMatriz();

	preencherRGB(10,15,cores);
	printar(10,15,cores);
	
	RGB **cinza;
	cinza = loadMatriz();

	converter_rgb_gray(10,15,cores,cinza);
	printar(10,15,cinza);
	
	freeMatriz(cores);
	freeMatriz(cinza);
}
