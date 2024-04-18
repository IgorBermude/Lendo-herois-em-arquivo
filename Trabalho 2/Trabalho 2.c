#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 100

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct Heroi{
	char nome[30];
	char nome_individualidade[50];
	int peso;
	float altura;
	int rank;
}Heroi;

typedef struct Vilao{
	char nome[30];
	char nome_individualidade[50];
	int peso;
	float altura;
	int nivel;
}Vilao;

typedef struct Pais{
	char nome[30];
	char arquivo_herois[30];
	char arquivo_viloes[30];
	Heroi herois[100];
	int qt_herois;
	Vilao viloes[100];
	int qt_viloes;
}Pais;

void lerHeroisArquivo(char *nome_arquivo, Pais *pais){
	int cont = 0;
	FILE *arquivo = fopen(nome_arquivo, "r");//Abro o arquivo da cidade.
	if(!arquivo){
		printf("\nErro na abertura do arquivo: %s", nome_arquivo);
	}else{
		while(!feof(arquivo)){//Guardo os respectivos dados:
			fscanf(arquivo, "%s", pais->herois[cont].nome);
			fscanf(arquivo, "%s", pais->herois[cont].nome_individualidade);
			fscanf(arquivo, "%d", &(pais->herois[cont].peso));
			fscanf(arquivo, "%f", &(pais->herois[cont].altura));
			fscanf(arquivo, "%d", &(pais->herois[cont].rank));
			cont++;
		}
		pais->qt_herois = cont;
		fclose(arquivo);
	}
}

void lerViloesArquivo(char *nome_arquivo, Pais *pais){
	int cont = 0;
	FILE *arquivo = fopen(nome_arquivo, "r");//Abro o arquivo da cidade.
	if(!arquivo){
		printf("\nErro na abertura do arquivo: %s", nome_arquivo);
	}else{
		while(!feof(arquivo)){//Guardo os respectivos dados:
			fscanf(arquivo, "%s", pais->viloes[cont].nome);
			fscanf(arquivo, "%s", pais->viloes[cont].nome_individualidade);
			fscanf(arquivo, "%d", &(pais->viloes[cont].peso));
			fscanf(arquivo, "%f", &(pais->viloes[cont].altura));
			fscanf(arquivo, "%d", &(pais->viloes[cont].nivel));
			cont++;
		}
		pais->qt_viloes = cont;
		fclose(arquivo);
	}
}

void lerPaisArquivo(char *nome_arquivo, Pais *pais, int *quant_Pais){
	int cont = 0;
	FILE *arquivo = fopen(nome_arquivo, "r");
	if(!arquivo){
		printf("\nErro na abertura do arquivo: %s", nome_arquivo);
	}else{
		while(!feof(arquivo)){//Leio os o nome e os respectivos arquivos, armazenando nos vetores.
			fscanf(arquivo, "%s", pais[cont].nome);
			fscanf(arquivo, "%s", pais[cont].arquivo_herois);
			fscanf(arquivo, "%s", pais[cont].arquivo_viloes);
			lerHeroisArquivo(pais[cont].arquivo_herois, &pais[cont]);//Passo como parametro o nome do arquivo, para abrir ele na função.
			lerViloesArquivo(pais[cont].arquivo_viloes, &pais[cont]);
			cont++;
		}
		*quant_Pais = cont;
		fclose(arquivo);
	}
}

void imprimirPaisesMaisHerois(Pais *pais, int quant_Paises){
	int i;
	printf("Os países com mais heróis que vilões são: ");
	for(i=0;i<quant_Paises;i++){
		if(pais[i].qt_herois > pais[i].qt_viloes){//Se a quantidade de herois for maior que de vilões imprimo o nome do pais.
			printf("%s - ", pais[i].nome);
		}
	}
}

int retornaMaiorRank(Pais pais){
	int i;
	int Rank = pais.herois[0].rank;
	int posicaoMaiorRank = 0;
	for(i=0;i<pais.qt_herois;i++){
		if(pais.herois[i].rank < Rank){//Se o rank do heroi for menor que o rank do heroi anterior guardo sua posição e seu rank.
			Rank = pais.herois[i].rank;
			posicaoMaiorRank = i;
		}
	}
	return posicaoMaiorRank;
}

void imprimirMaiorRankHerois(Pais *pais, int quant_Paises){
	int i, j;
	printf("\n\nOs países e seu héroi de maior rank em atividade:");
	for(i=0;i<quant_Paises;i++){
		printf("\n%s\t", pais[i].nome);
		j = retornaMaiorRank(pais[i]);//j é igual a localização do heroi de maior rank.	
		printf("%s\t", pais[i].herois[j].nome);
		printf("%d", pais[i].herois[j].rank);
	}
}

float retornaMenorIMC(Pais *pais, int quant_Paises){
	int i, j;
	float IMC = 0;
	float menorIMC = (pais[0].viloes[0].peso/(pais[0].viloes[0].altura * pais[0].viloes[0].altura));
	for(i=0;i<quant_Paises;i++){
		for(j=0;j<pais[i].qt_viloes;j++){
			IMC = (pais[i].viloes[j].peso/(pais[i].viloes[j].altura * pais[i].viloes[j].altura));
			if(IMC < menorIMC){ //Calculo o imc de cada vilão e comparo ele com o menor imc.
				menorIMC = IMC;//Se for menor eu seto ele como o menorIMC.
			}
		}
	}
	return menorIMC;
}

void imprimirMenorIMCViloes(Pais *pais, int quant_Paises){
	int i, j;
	float IMC = 0;
	float menorIMC = retornaMenorIMC(pais, quant_Paises);//Chamo a função que retorna o menor imc.
	printf("\n\nMenor IMC = %f", menorIMC);
	for(i=0;i<quant_Paises;i++){
		for(j=0;j<pais[i].qt_viloes;j++){//Percorro o vetor de Vilões.
			IMC = (pais[i].viloes[j].peso/(pais[i].viloes[j].altura * pais[i].viloes[j].altura));
			if(IMC == menorIMC){//Se o IMC do vilão for igual ao menorIMC sera imprimido.
				printf("\n%s\t%s\t%d\t%.2f\t%d",pais[i].viloes[j].nome, pais[i].viloes[j].nome_individualidade, 
				pais[i].viloes[j].peso, pais[i].viloes[j].altura, pais[i].viloes[j].nivel);
			}
		}
	}
}

int temLetraMRetorna1(char *nome_individualidade){
	int i;
	int tam_string = strlen(nome_individualidade);
	for(i=0;i<tam_string;i++){//O i percorre a string, se achar m ou M retorna 1, se não retorna 0.
		if(nome_individualidade[i] == 'm'){
			return 1;
		}
		else if(nome_individualidade[i] == 'M'){
			return 1;
		}
	}
	return 0;
}

void imprimirHeroisViloesComM(Pais *pais, int quant_Paises){
	int i, j;
	int aux;
	printf("\n\nHerois e Vilões com letra m em sua individualidade:");
	printf("\nHerois: ");
	for(i=0;i<quant_Paises;i++){
		for(j=0;j<pais[i].qt_herois;j++){//Percorro o vetor de Herois.
			aux = temLetraMRetorna1(pais[i].herois[j].nome_individualidade);
			if(aux == 1){//Se aux=1 imprimo o heroi.
				printf("\n%s\t\t%s\t%d\t%.2f\t%d",pais[i].herois[j].nome, pais[i].herois[j].nome_individualidade, 
				pais[i].herois[j].peso, pais[i].herois[j].altura, pais[i].herois[j].rank);
			}
		}
	}
	printf("\n\nVilões: ");
	for(i=0;i<quant_Paises;i++){
		for(j=0;j<pais[i].qt_viloes;j++){//Percorro o vetor de Vilões.
			aux = temLetraMRetorna1(pais[i].viloes[j].nome_individualidade);
			if(aux == 1){//Se aux=1 imprimo o vilão.
				printf("\n%s\t\t%s\t%d\t%.2f\t%d",pais[i].viloes[j].nome, pais[i].viloes[j].nome_individualidade, 
				pais[i].viloes[j].peso, pais[i].viloes[j].altura, pais[i].viloes[j].nivel);
			}
		}
	}
}

int main(int argc, char** argv) {
	setlocale(LC_ALL, "Portuguese");
	int quant_Paises = 0;
	Pais *pais;
	pais = (Pais *)malloc(TAM*sizeof(Pais));
	lerPaisArquivo("paises.txt", pais, &quant_Paises);
	imprimirPaisesMaisHerois(pais, quant_Paises);
	imprimirMaiorRankHerois(pais, quant_Paises);
	imprimirMenorIMCViloes(pais, quant_Paises);
	imprimirHeroisViloesComM(pais, quant_Paises);
	free(pais);
	return 0;
}
