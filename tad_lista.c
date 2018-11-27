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
	if(lista->tam== 0){
        	return 1;
    	}else{
        	return 0;
    	}
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
	if(id==0 || lista==NULL){
		return ERRO;
	}

	no=(NODE*) malloc(sizeof(NODE));
	no->item=inicia_item();
	if( insere_id((no->item),id)==ERRO){
		return ERRO;
	}
	insere_nome( (no->item), nome);
	insere_link( (no->item), site);

	if(lista_vazia(lista)){// a lista esta vazia
		lista->sup=no;
		lista->inf=no;
		lista->tam++;
		return 1;
	}

	aux=lista->sup;

	if(retorna_id((aux->item)) < id ){ //o site esta no inicio da lista
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

int lista_insere_site_rel(LISTA *lista, int id, char *site, char *nome, int rel){   /* ESSA FUNÇÃO INSERE O SITE NUMA LISTA ORDENADA PELA RELEVANCIA*/
	NODE *no;
	NODE *aux;
	if(id==0 || lista==NULL){
		return ERRO;
	}
	no=(NODE*) malloc(sizeof(NODE));
	no->item=inicia_item();
	if(insere_id((no->item),id)==ERRO){
		return ERRO;
	}
	insere_nome( (no->item),nome);
	insere_link( (no->item),site);
	if(insere_rel((no->item), rel) !=1 ){
        	return ERRO;
	}
	if(lista_vazia(lista)){// a lista esta vazia
		lista->sup=no;
		lista->inf=no;
		lista->tam++;
		return 1;
	}
	aux = (lista->sup);
	if( retorna_rel((aux->item)) < rel ){ /* o site esta no inicio da lista*/
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

int remove_site(LISTA *lista, NODE *no) {
    int id = retorna_id(no->item);
    NODE* temp = lista->sup;
    NODE *prev;
    // If head node itself holds the key to be deleted
    if (temp != NULL && retorna_id(temp->item) == id){
        lista->sup = temp->prox;
        free(temp);
        return 1;
    }
    while (temp != NULL && retorna_id(temp->item) != id){
        prev = temp;
        temp = temp->prox;
    }
    // If key was not present in linked list
    if (temp == NULL) return 0;
    // Unlink the node from linked list
    prev->prox = temp->prox;
    free(temp);  // Free memory
    return 1; // Node successfully removed
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
			return 1;
		}
		return ERRO;							//erro ao atualizar relevancia
	}
}

int finaliza_lista(LISTA **a){//finaliza a lista
	NODE *aux, *aux1;
	aux= (*a)->sup;	
	do{
		aux1=aux->prox;
		libera_node(aux);
		aux=aux1;
	}while(aux!=NULL);//desaloca todos os nos
	(*a)->sup=NULL;
	(*a)->inf=NULL;
	libera_node(aux1);
	free(a);
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

void imprime_toda_lista(LISTA *lista){
    NODE *aux;
    if(lista == NULL){
        return;
    }else{
        aux = lista->sup;
        while(aux!=NULL){
            printf("%s, %s\n", retorna_nome(aux->item), retorna_link(aux->item));
            aux=aux->prox;
        }
    }
    return;
}

NODE *retorna_prox(NODE *no){
	if(no!=NULL) return(no->prox);
	else return NULL;
}

NODE *retorna_topo(LISTA *lista){
	NODE *aux;
	if(lista!=NULL){
		aux=lista->sup;
		return aux;
	}
	else return NULL;
}
int node_retorna_qtd_pc (NODE *no){
	ITEM *i = (no->item);
	if(no!=NULL){
		return(retorna_qtd_pc(i));
	}
	else return ERRO;
}

char *node_retorna_pc(NODE *no, int i){
	if(no!=NULL) return(retorna_pc(no->item, i) );
	else return NULL;
}





