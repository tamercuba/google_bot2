#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tad_item.h"
#include "tad_lista.h"

#define ERRO -32
#define REL_MAX 1000


/*DECLARACAO NODE*/
struct node_{
	ITEM *item;
	NODE *prox;
};

/*DECLARACAO LISTA*/
struct lista_{
	NODE *sup, *inf;
	int tam;
};

/*INICIA LISTA*/
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

/*LISTA VAZIA*/
int lista_vazia(LISTA *lista){
	if(lista->tam== 0){
        	return 1;
    	}else{
        	return 0;
    	}
}

/*RETORNA NODE (ID) */
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

/*INSERE SITE ORDENADO ID*/
int lista_insere_site(LISTA *lista, int id, char *site, char *nome){   /* como a inserção sera feita
  				   	       		   		em dois passos, primeiro pela funçao que le o arquivo
							   	e depois pela função de adicionar manualmente, preferi fazer essa separada */
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

	if(lista_vazia(lista)){/* a lista esta vazia */
		lista->sup=no;
		lista->inf=no;
		lista->tam++;
		return 1;
	}

	aux=lista->sup;

	if(retorna_id((aux->item)) < id ){ /*o site esta no inicio da lista */
		no->prox=lista->sup;
		lista->sup=no;
		lista->tam++;
		return 1;
	}
	do{
		if(aux->prox==NULL){ /*o site esta no final da lista*/
			lista->inf=no;
			no->prox=NULL;
			aux->prox=no;
			lista->tam++;
			return 1;
		}

		if(retorna_id(aux->prox->item) < id){ /*o id do site inserido esta no meio da lsita*/
			no->prox = aux->prox;
			aux->prox = no;
			lista->tam++;
			return 1;
		}else{
			aux=aux->prox; /*verifica proximo item na lista*/
		}
	}while(1);
}

/*INSERE SITE ORDENADA RELEVANCIA*/
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
	if(lista_vazia(lista)){			/* a lista esta vazia*/
		lista->sup=no;
		lista->inf=no;
		lista->tam++;
		return 1;
	}
	aux = (lista->sup);
	if( retorna_rel((aux->item)) < rel ){ 			/* o site esta no inicio da lista*/
		no->prox=lista->sup;
		lista->sup=no;
		lista->tam++;
		return 1;
	}
	do{
		if(aux->prox==NULL){ 		/*o site esta no final da lista*/
			lista->inf=no;
			no->prox=NULL;
			aux->prox=no;
			lista->tam++;
			return 1;
		}
		if(retorna_rel(aux->prox->item) <= rel){ 		/*o id do site inserido esta no meio da lsita*/
			no->prox = aux->prox;
			aux->prox = no;
			lista->tam++;
			return 1;
		}else{
			aux=aux->prox; 			/*verifica proximo item na lista*/
		}
	}while(1);
}

/*REMOVE SITE*/
int remove_site(LISTA *lista, NODE *no) {
    int id;
    NODE *temp;
    NODE *prev;
    id= retorna_id(no->item);
    temp= lista->sup;
    /* If head node itself holds the key to be deleted*/
    if (temp != NULL && retorna_id(temp->item) == id){
        lista->sup = temp->prox;
        free(temp);
        return 1;
    }
    while (temp != NULL && retorna_id(temp->item) != id){
        prev = temp;
        temp = temp->prox;
    }
    /* If key was not present in linked list*/
    if (temp == NULL) return 0;
    /* Unlink the node from linked list*/
    prev->prox = temp->prox;
    free(temp);  /*Free memory*/
    return 1; /*Node successfully removed*/
}

/*INSERE PC NA LISTA*/
int insere_lista_pc(LISTA *lista, int id, char *pc){
	NODE *aux;
	int i;
	aux=busca_id(lista, id); 		/*busca pelo id da palavra chave em questap*/
	if(aux==NULL){
		return 0;
	}
	else{
		i=insere_pc(aux->item, pc); 			/*insere a palavra chave no id*/
		if( i != ERRO){
			return 1;
		}
		return ERRO;
	}
}

/*ATUALIZA RELEVANCIA*/
int atualiza_rel(LISTA *lista, int id, int rel){
	NODE *aux;
	aux = busca_id(lista, id);			/*busca a lista que desejase atualizar a relevancia*/
	if(aux==NULL){
		return 0;		/*lista nao existente*/
	}
	else{

		if(rel>=0 && rel<=REL_MAX){
			insere_rel(aux->item, rel);
			return 1;
		}
		return ERRO;		/*erro ao atualizar relevancia*/
	}
}

/*FINALIZA LISTA*/
int finaliza_lista(LISTA **a){
	NODE *aux;
	while(aux!=NULL){
		aux=retorna_topo(*a);
		(*a)->sup=aux->prox;
		libera_node(aux);
	}				/*desaloca todos os nos*/
	//(*a)->sup=NULL;
	//(*a)->inf=NULL;
	libera_node(aux);
	free(a);
	return 1;
}

/*BUSCA BOOL*/
int busca(NODE *no){
	if(no!=NULL) return(1);
	else return(0);
}

/*LIBERA NO*/
void libera_node(NODE *no){
    NODE *aux=no;
    if(aux==NULL) return;
	libera_item(aux->item);
	aux->prox=NULL;
	free(aux);
	aux=NULL;
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

/*PRINTA NOME E LINK DE TODOS SITES EM UMA DADA LISTA*/
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

void imprime_toda_lista2(LISTA *lista, int **check){
	NODE *aux;
	int *temp;
	int i=0;
	temp=*check;
	if(lista == NULL){
		return;
	}else{
        	aux = lista->sup;
		while(aux!=NULL){
			for(i=0;1;i++){
				if(temp[i]==0){
       		     			i=0;
       		     			break;
       		     			/*sai do while*/
       	     			}
            			if(retorna_id(aux->item) == temp[i]){
            				aux=aux->prox;
            				i=0;
            				break;
            				/*sai do while*/
            			}
			}
            		printf("%s, %s\n", retorna_nome(aux->item), retorna_link(aux->item));
            		i=0;
            		while(1){
            			if(temp[i]==0){
            				temp[i]=retorna_id(aux->item);
            				break;
            			}else{
            				i++;
            			}
            		}
            		aux=aux->prox;
        	}
	}
    return;
}

/*RETORNA O PROX NO*/
NODE *retorna_prox(NODE *no){
	if(no!=NULL) return(no->prox);
	else return NULL;
}

/*RETORNA TOPO*/
NODE *retorna_topo(LISTA *lista){
	NODE *aux;
	if(lista!=NULL){
		aux=lista->sup;
		return aux;
	}
	else return NULL;
}

/*RETORNA QUANTIDADE DE PALAVRAS CHAVE DE UM NO*/
int node_retorna_qtd_pc(NODE *no){
	ITEM *i;
	if(no!=NULL){
		i = no->item;
		return(retorna_qtd_pc(i));
	}
	else return ERRO;
}

/*RETORNA A i-ESIMA PALAVRA CHAVE DE UM NO*/
char *node_retorna_pc(NODE *no, int i){
	if(no!=NULL) return(retorna_pc(no->item, i) );
	else return NULL;
}

/*RETORNA ID*/
int node_retorna_id(NODE *no){
	NODE *aux = no;
	if(aux!=NULL){
		return(retorna_id(aux->item));
	}
	else return(ERRO);
}

/*RETORNA RELEVANCIA*/
int node_retorna_rel(NODE *no){
	NODE *aux = no;
	if(aux!=NULL){
		return(retorna_rel(aux->item));
	}
	else return(ERRO);
}

/*RETORNA LINK*/
char *node_retorna_link(NODE *no){
	NODE *aux = no;
	if(aux!=NULL){
		return(retorna_link(aux->item));
	}
	else return NULL;
}

/*RETORNA NOME*/
char *node_retorna_nome(NODE *no){
	NODE *aux = no;
	if(aux!=NULL){
		return(retorna_nome(aux->item));
	}
	else return NULL;
}

