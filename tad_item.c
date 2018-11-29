#ifndef libs
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "tad_item.h"
	#define ERRO -32
	#define REL_MAX 1000
#endif

#define MAX_ID 9999
#define ID_NULL 0


struct item_g{
	int id;                       /*id de 4 digitos*/
	char nome[50];
	int rel;                      /*relevancia, vai de 0 a 1000*/
	char link[100];
	int qtd_pc;                  /* quantidade de palavras chave*/
	char palavra_chave[10][50];
};

ITEM *inicia_item(void){					/* FUNCAO INICIA ITEM*/
	ITEM *aux=(ITEM *) malloc(sizeof(ITEM));
	aux->rel=0;
	aux->qtd_pc=0;
	return aux;
}

void libera_item(ITEM *item){					/* LIBERA ITEM*/
	free(item);
	item=NULL;
	return;
}

int insere_id(ITEM *item, int valor){   			/* INSERE ID*/
	if (valor > MAX_ID){
	 	return ERRO;   /* no enunciado esta explicito*/
	}                        /*que o numero maximo de*/
	else {                /* caracteres pro id é 4*/
		item->id = valor;
		return 1;
	}
}

void insere_nome(ITEM *item, char nome[]){			/* FUNCAO INSERE NOME*/
	strcpy(item->nome,nome);
}

int insere_rel(ITEM *item, int rel){ 				/* FUNCAO INSERE RELEVANCIA*/
	if(rel > REL_MAX){
	 	return ERRO;
	}
	else{
		item->rel = rel;
		return 1;
	}
}

void insere_link(ITEM *item, char link[]){			/* FUNCAO INSERE LINK*/
	strcpy(item->link,link);
}

int insere_pc(ITEM *item, char palavra[]){				/*FUNCAO INSERE PALAVRA CHAVE*/
	if(item->qtd_pc < 10){
		strcpy(item->palavra_chave[item->qtd_pc],palavra);
		item->qtd_pc++;
		return 1;
	}
	else{
		return ERRO;
	}
}


int retorna_id(ITEM *item){					/* FUNCAO RETORNA ID, necessaria pois do arquivo .c nao temos acesso a node->item->id por exemplo*/
	if(item!=NULL) return(item->id);
	else return ERRO;
}

int retorna_rel(ITEM *item){
	if(item!=NULL) return(item->rel);
	else return ERRO;
}

char *retorna_nome(ITEM *item){
	if(item!=NULL) return(item->nome);
	else return NULL;
}

char *retorna_link(ITEM *item){
	if(item!=NULL) return(item->link);
	else return NULL;
}

int retorna_qtd_pc (ITEM *item){
	if(item!=NULL){
		return(item->qtd_pc);
	}
	else return ERRO;
}

char *retorna_pc(ITEM *item, int i){
	if(i < item->qtd_pc ){
		return( item->palavra_chave[i] );
	}
	return NULL;
}
