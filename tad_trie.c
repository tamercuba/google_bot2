#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tad_item.h"
#include "tad_lista.h"
#include "tad_trie.h"

#define ALPHABET 26
#define TRUE 1
#define FALSE 0
#define max_letters 50
#define ERRO -32

/*NO TRIE*/
struct node_trie_{
    struct node_trie_ *prox[ALPHABET];
    struct lista_ *lista;
    int end; /*BOOLEANO QUE INDICA SE É FIM DE PALAVRA OU NAO*/
};

/*INICIA NO*/
node_trie *creat_node_trie (void){
    int i;
    node_trie *trie = (node_trie *) malloc(sizeof(node_trie));
    trie->end = FALSE;
    trie->lista = lista_inicia();
    for(i=0;i<ALPHABET;i++){
        trie->prox[i] = NULL;
    }
    return trie;
}

/*ÍNSERE PALAVRA NA TRIE*/
void insert_key_word(node_trie *trie, char *key, int begin,int id, char *link, char *nome, int rel){
        node_trie *p = trie;
        int i;
        for(i=begin;key[i]!='\0' && key[i]!='\n' && key[i]!='\r';i++){
                if(key[i]>='a' && key[i]<='z'){
                        if(p->prox[key[i]-'a'] == NULL){
                                p->prox[key[i] -'a'] = creat_node_trie();
                        }
                        p = p->prox[key[i]-'a'];
                }else if(key[i]>='A' && key[i]<='Z'){
                        if(p->prox[key[i]-'A'] == NULL){
                                p->prox[key[i] -'A'] = creat_node_trie();
                        }
                        p = p->prox[key[i]-'A'];
		}else{
                        insert_key_word(trie, key, i+1, id, link, nome, rel);
                        return;
                }
        }
        p->end=1;
        if(lista_vazia(p->lista) == 1){
                p->lista = lista_inicia();
	}
        lista_insere_site_rel(p->lista, id, link, nome, rel);
        return;
}

/*BUSCA PALAVRA NA TRIE*/
LISTA *search_node_trie (node_trie *trie, char *key){
    node_trie *p = trie;

    if(trie == NULL){
        return NULL;
    }

    while(*key) {
        p = p->prox[*key - 'a'];

        if(p == NULL){
            return NULL;
        }
        key++;
    }

    if(p->end == TRUE && p != NULL){
		/*RETORNA A LISTA QUE ESA NO NODE *P */
        return p->lista;
    }else{
        return NULL;
    }

}

/*FUNCAO QUE LE O ARQUIVO GOOGLEBOT.TXT E FAZ AS INSERCOES NECESSARIAS*/
int ler_dados(LISTA *lista, node_trie *trie){

    FILE *fp;
    char *pch;
    int id, rel, tmp;
    char nome[50];
    char link[100];
    char line[802];
    tmp=1;
    fp = fopen("googlebot.txt", "r");		/*ponteiro para o aqruivo*/
    if(fp==NULL ){
        printf("fp error"); return 0;
    }
    while(!feof(fp)){			/*ler ate o final do arquivo txt*/
        fscanf(fp, "%d%*c%[^,]%*c%d%*c%[^,]%*c", &id, nome, &rel, link);
        tmp = lista_insere_site(lista, id, link, nome);
        if(tmp==0){
                return 0;
        }
        atualiza_rel(lista, id, rel);
        if(tmp==0){
                return 0;
        }
        fgets(line, 520, fp);
        pch = strtok (line,",");
        while (pch != NULL){
            insere_lista_pc(lista,id,pch);
            insert_key_word(trie,pch,0,id,link,nome,rel);
            pch = strtok (NULL, ",");
        }
    }
    return 1;
}

/*REMOVE PALAVRA DA TRIE*/
void remove_pc_trie(node_trie *trie, NODE *no){
    char *pc;
    LISTA *lista;
    int i;
    for(i=0;i<node_retorna_qtd_pc(no);i++){
        pc = node_retorna_pc(no, i);
        lista = search_node_trie(trie, pc);
        remove_site(lista, no);
    }
    return;
}

/*IMPRIME SITES*/
void imprime_sites(node_trie *trie, char *key){
	LISTA *aux = search_node_trie(trie, key);
	if(aux!=NULL){
		imprime_toda_lista(aux);
		return;
	}
	return;
}

void imprime_sites2(node_trie *trie, char *key, int **check){
	int *temp;
	LISTA *aux = search_node_trie(trie, key);
	temp=*check;
	if(aux!=NULL){
		imprime_toda_lista2(aux, &temp);
		return;
	}
	return;
}

/*FUNÇÃO DE SUGESTAO*/
void sugestao(LISTA *lista, node_trie *trie, char *key){
	NODE *p, *aux1;
	int i, id,qtd,*check;
	char *pc;
	LISTA *aux=search_node_trie(trie, key);
	check=(int*)malloc(150*sizeof(int));
	if(check==NULL) return;
	for(i=0; i<150; i++){
		check[i]=0;
	}
	if(aux!=NULL){
		p=retorna_topo(aux);
		while(p!=NULL){
			id = node_retorna_id(p);			/*PEGA O ID DO NO*/
			aux1=busca_id(lista,id);			/*BUSCA ELE NA LISTA ORDENADA POR ID*/
			qtd= node_retorna_qtd_pc(aux1);			/*PEGA A QUANTIDADE DE PALAVRAS CHAVE DESSE NO*/
			for(i=0;i < qtd;i++){
				pc=node_retorna_pc(aux1,i);		/*GUARDA A i-ESIMA PALAVRA CHAVE*/
				imprime_sites2(trie, pc, &check);		/*FAZ UMA BUSCA COM A i-ESIMA CHAVE E IMPRIME TODOS SITES ENCONTRADOS*/
			}
			p=retorna_prox(p);
		}
	}
	free(check);
	return;
}

/*FINALIZA TRIE*/
int finaliza_trie(node_trie **trie){
	node_trie *aux;
	int i;
	aux= *trie;
	for(i=0;i<ALPHABET;i++){
		if(aux->prox[i] != NULL){
			if(finaliza_trie(&(aux->prox[i]))){
				free(aux->prox[i]);
			}
		}
	}
	finaliza_lista(&(aux->lista));
	free(aux);
	return 1;
}
