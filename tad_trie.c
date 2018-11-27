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

struct node_trie_{
    struct node_trie_ *prox[ALPHABET];
    struct lista_ *lista;
    int end; //indicates this is the end cahracter
};


node_trie *creat_node_trie (void){

    node_trie *trie = (node_trie *) malloc(sizeof(node_trie));
    trie->end = FALSE;
    trie->lista = lista_inicia();
    int i;
    for(i=0;i<ALPHABET;i++){
        trie->prox[i] = NULL;
    }
    return trie;
}

void insert_key_word(node_trie *trie, char *key, int begin,int id, char *link, char *nome, int rel){
        node_trie *p = trie;
        int i;
        for(i=begin;key[i]!='\0' && key[i]!='\n';i++){  
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
	// NOVO
	i=insere_lista_pc(p->lista, id, key);
	//INSERT ON THE END OF THE LIST
        return;
}

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
		//HERE WE NEED TO RETURN THE LIST THAT IS IN THE NODE P
        return p->lista;
    }else{
        return NULL;
    }

}

int ler_dados(LISTA *lista, node_trie *trie){

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
        fgets(line, 520, fp);                     //ler ate o final da linha
        length = strlen(line);
        for(i=0,j=0;i<=length+2;i++,j++){
            if(line[i] == ',' || i==length || line[i]=='\n' || line[i]=='\r' || line[i]=='\0'){         // se for final da linha ou encontrar uma virgula fim de uma palavra
                word[j] = '\0';
                insere_lista_pc(lista, id, word);     //insere palavra na lista
                //parte da trie
                insert_key_word(trie, word, 0, id, link, nome, rel);
                j=-1;
            }else{
                word[j]=line[i];             //copia caractere valido para a palavra
            }
        }
    }
    return 1;
}

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

void imprime_sites(node_trie *trie, char *key){
	LISTA *aux = search_node_trie(trie, key);
	if(aux!=NULL){
		imprime_toda_lista(aux);
		return;
	}
	return;
}

void sugestao(LISTA *lista, node_trie *trie, char *key){
	NODE *p, *aux1;
	int i, id,qtd;
	char *pc;
	LISTA *aux=search_node_trie(trie, key);
	if(aux!=NULL){
		p=retorna_topo(aux);
		while(p!=NULL){
			id = node_retorna_id(p);			/*PEGA O ID DO NO*/
			aux1=busca_id(lista,id);			/*BUSCA ELE NA LISTA ORDENADA POR ID*/
			qtd= node_retorna_qtd_pc(aux1);			/*PEGA A QUANTIDADE DE PALAVRAS CHAVE DESSE NO*/
			printf("\n %d e %d \n",qtd, node_retorna_rel(aux1)); // TESTE 
			for(i=0;i < qtd;i++){
				pc=node_retorna_pc(aux1,i);		/*GUARDA A i-ESIMA PALAVRA CHAVE*/
				//printf("\n %s", pc);
				imprime_sites(trie, pc);		/*FAZ UMA BUSCA COM A i-ESIMA CHAVE E IMPRIME TODOS SITES ENCONTRADOS*/
			}
			p=retorna_prox(p);
		}
	}
	return;
}
