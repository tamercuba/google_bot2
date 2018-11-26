#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tad_item.h"
#include "tad_lista.h"
#define ERRO -32
#define REL_MAX 1000



struct node_{
	ITEM *item;
	NODE *prox;
};

struct lista_{
	NODE *sup, *inf;
	int tam; 
}; 

LISTA *lista_inicia(void){
	LISTA *aux = (LISTA *) malloc(sizeof(LISTA));
	if(aux!=NULL){
		aux->sup = NULL;
		aux->inf = NULL;
		aux->tam=0;	
		return(aux);
	}else{
		return NULL;
	}
}

int lista_vazia(LISTA *lista){
	if(aux->tam==0) return 1;
	else return 0;
}

NODE *busca_id(LISTA *lista, int id){
	NODE *aux;
	aux=lista->sup;
	if(id==0 || lista_vazia(lista) ) {
		return NULL;
	}
	while(aux->prox!=NULL){
		if(retorna_id(aux->item)!=id){
			aux=aux->prox;
		}
		else{
			return aux;
		}
	}
	if(aux!=NULL && retorna_id(aux->item) == id){
		return aux;
	}
	else{
		return NULL;
	}
}

int lista_insere_site(LISTA *lista, int id, char *site, char *nome){   // como a inserção sera feita
  				   	       		   // em dois passos, primeiro pela funçao que le o arquivo
							   // e depois pela função de adicionar manualmente, preferi fazer essa separada
	NODE *no;
	NODE *aux;
	if(id==0){
		return ERRO;
	}
	
	no=(NODE*) malloc(sizeof(NODE));
	no->item=inicia_item();
	if( insere_id((no->item),id)==ERRO){
		return ERRO;
	}
	insere_nome( (no->item) ,nome);
	insere_link( (no->item) ,site);
	aux=lista->sup;
	if(lista_vazia(lista)){// a lista esta vazia
		lista->sup=no;
		lista->inf=no;
		lista->tam++;
		return 1;
	}
	if( retorna_id( (aux->item) ) < id ){ //o site esta no inicio da lista
		no->prox=lista->sup;
		lista->sup=no;
		lista->tam++;
		return 1;
	}
	do{
		if(aux->prox==NULL){ //o site esta no final da lista
			lista->inf=no;
			no->prox=NULL;
			aux->prox=no;
			lista->tam++;
			return 1;
		}
		
		if(retorna_id(aux->prox->item) < id){ //o id do site inserido esta no meio da lsita
			no->prox = aux->prox;
			aux->prox = no;
			lista->tam++;
			return 1;
		}else{
			aux=aux->prox; //verifica proximo item na lista
		}						
	}while(1);
} 

int lista_insere_site_rel(LISTA *lista, int id, char *site, char *nome, int rel){   // como a inserção sera feita
  				   	       		   // em dois passos, primeiro pela funçao que le o arquivo
							   // e depois pela função de adicionar manualmente, preferi fazer essa separada
	NODE *no;
	NODE *aux;
	if(id==0){
		return ERRO;
	}
	no=(NODE*) malloc(sizeof(NODE));
	no->item=inicia_item();
	if( insere_id((no->item),id)==ERRO){
		return ERRO;
	}
	insere_nome( (no->item),nome);
	insere_link( (no->item),site);
	if(insere_rel( (no->item), rel) !=1) return ERRO;
	aux=lista->sup;
	if(lista_vazia(lista)){// a lista esta vazia
		lista->sup=no;
		lista->inf=no;
		lista->tam++;
		return 1;
	}
	if( retorna_rel( (aux->item) ) <= rel ){ //o site esta no inicio da lista
		no->prox=lista->sup;
		lista->sup=no;
		lista->tam++;
		return 1;
	}
	do{
		if(aux->prox==NULL){ //o site esta no final da lista
			lista->inf=no;
			no->prox=NULL;
			aux->prox=no;
			lista->tam++;
			return 1;
		}
		
		if(retorna_rel(aux->prox->item) <= id){ //o id do site inserido esta no meio da lsita
			no->prox = aux->prox;
			aux->prox = no;
			lista->tam++;
			return 1;
		}else{
			aux=aux->prox; //verifica proximo item na lista
		}						
	}while(1);
} 


int remove_site(LISTA *lista, int id){ //remove site
	NODE *aux, *aux1;
	aux1=lista->sup;
	aux=busca_id(lista,id);
	
	if(aux==NULL){           //se o site nao existe reorna 0
		return 0;		
	}
	else{
		while( retorna_id(aux1->prox->item) != retorna_id(aux->item) ){// encontra o anterior, necessario pois nossa lista nao é duplamente encadeada
			aux1=aux1->prox;
		}
		aux1->prox=aux->prox;
		libera_node(aux);
		if(aux!=NULL) {
			lista->tam--;
			return 1;
		}
		else{
			return ERRO; //erro ao desalocar a memoria alocada para o site que desejase remover
		}
	}
}


int insere_lista_pc(LISTA *lista, int id, char *pc){			// funcao que insere palavra chave a um certo site pelo id 
	NODE *aux;
	int i;
	aux=busca_id(lista, id); //busca pelo id da palavra chave em questap
	if(aux==NULL){
		return 0;
	}
	else{
		i=insere_pc(aux->item, pc); //insere a palavra chave no id
		if( i != ERRO){
			// insercao na trie
			return 1;
		}
		return ERRO;
	}
}

int atualiza_rel(LISTA *lista, int id, int rel){ 		//tualiza a relevancia da lista
	NODE *aux;						 
	aux = busca_id(lista, id);						//busca a lista que desejase atualizar a relevancia
	if(aux==NULL){
		return 0;							//lista nao existente
	}
	else{
		
		if(rel>=0 && rel<=REL_MAX){
			insere_rel(aux->item, rel);
		}
		return ERRO;							//erro ao atualizar relevancia
	}
}

int finaliza_lista(LISTA **a){//finaliza a lista
	LISTA *lista;
	NODE *aux, *aux1;

	aux=lista->sup;
	do{
		aux1=aux->prox;
		libera_node(aux);
		aux=aux1;
	}while(aux!=NULL);//desaloca todos os nos
	lista->sup=NULL;
	lista->inf=NULL;
	libera_node(aux1);
	free(lista);
	return 1;
}

int ler_dados(LISTA *lista){
	
	FILE *fp;
	//char c;
	int id, rel, i, j, tmp;
	int length;
	char nome[50];
	char link[100];
	char line[802];
	char word[50];
	tmp=1;
	
	fp = fopen("googlebot.txt", "r");//ponteiro para o aqruivo
	
	if(fp==NULL ){
		printf("fp error"); return 0;
	}

	while(!feof(fp)){//ler ate o final do arquivo txt
		fscanf(fp, "%d%*c%[^,]%*c%d%*c%[^,]%*c", &id, nome, &rel, link);
		tmp = lista_insere_site(lista, id, link, nome);
		if(tmp==0){
				return 0;
		}
		atualiza_rel(lista, id, rel);
		if(tmp==0){
				return 0;
		}
		
		fgets(line, 520, fp); 					//ler ate o final da linha
		length = strlen(line);
		
		for(i=0,j=0;i<=length;i++,j++){
			
			if(line[i] == ',' || i==length){ 		// se for final da linha ou encontrar uma virgula fim de uma palavra
				word[j] = '\0';
				insere_lista_pc(lista, id, word); 	//insere palavra na lista
				j=-1;
			}else{
				word[j]=line[i]; 			//copia caractere valido para a palavra
			}
		}
	}
	return 1;
} 

int busca(NODE *no){
	if(no!=NULL) return(1);
	else return(0);
}

void libera_node(NODE *no){ 				//desaloca memoria de no
	libera_item(no->item);
	no->prox=NULL;
	free(no);
	return;
}

void imprime_id_lista(LISTA *lista){
	NODE *aux;
	aux=lista->sup;
	while(aux->prox!=NULL){
		printf("%d",retorna_id(aux->item) );
		aux=aux->prox;
	}
}
